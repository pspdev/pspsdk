# File defining macro outputting PSP-specific EBOOT.PBP out of passed executable target.
#
# Copyright 2020 - Daniel 'dbeef' Zalega
# Copyright 2021 - max_ishere

cmake_minimum_required(VERSION 3.10)

option(BUILD_PRX "Build a PRX for use with PSPLink" OFF)
option(ENC_PRX "Encrypt the PRX to allow running on official firmware" OFF)

macro(create_pbp_file)

  set(oneValueArgs
    TARGET          # defined by an add_executable call before calling create_pbp_file
    TITLE           # optional, string, target's name in PSP menu
    ICON_PATH       # optional, absolute path to .png file, 144x82
    BACKGROUND_PATH # optional, absolute path to .png file, 480x272
    PREVIEW_PATH    # optional, absolute path to .png file, 480x272
    MUSIC_PATH      # optional, absolute path to .at3 file   
    VERSION         # optional, adds version information to PARAM.SFO
    OUTPUT_DIR      # optional, set the output directory for the EBOOT.PBP
    )
  set(options
    BUILD_PRX # optional, generates and uses PRX file instead of ELF in EBOOT.PBP
    ENC_PRX   # optional, replaces PRX file with encrypted version.
    )
  cmake_parse_arguments("ARG" "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

  # set mksfoex parameter if VERSION was not defined
  if (NOT DEFINED ARG_VERSION)
    set(ARG_VERSION "")
  endif()

  # set output directory to where the target is build if not set
  if (NOT DEFINED ARG_OUTPUT_DIR)
    set(ARG_OUTPUT_DIR $<TARGET_FILE_DIR:${ARG_TARGET}>)
  else()
    # Make sure the output directory exists
    if(NOT IS_DIRECTORY ${ARG_OUTPUT_DIR})
      add_custom_command(
        TARGET ${ARG_TARGET}
        POST_BUILD COMMAND
        ${CMAKE_COMMAND} -E make_directory
        ${ARG_OUTPUT_DIR}
      )
    endif()
  endif()

  # As pack-pbp takes undefined arguments in form of "NULL" string,
  # set each undefined macro variable to such value:
  foreach(arg ${oneValueArgs})
    if (NOT DEFINED ARG_${arg})
      set(ARG_${arg} "NULL")
    endif()
  endforeach()

  # Build a PRX anyway if the -DBUILD_PRX=ON was set
  if(${BUILD_PRX})
    set(ARG_BUILD_PRX ${BUILD_PRX})
  endif()

  # Encrypt the PRX anyway if the -DENC_PRX=ON was set
  if(${ENC_PRX})
	  set(ARG_ENC_PRX ${ENC_PRX})
  endif()

  if(NOT ${ARG_BUILD_PRX} AND ${ARG_ENC_PRX})
    message(WARNING "Encrypting PRX requires BUILD_PRX to be set, otherwise there is nothing to encrypt.\n"
      "ENC_PRX flag for target '${ARG_TARGET}' will be ignored.")
  endif()

  if(${ARG_BUILD_PRX})
    target_link_options(${ARG_TARGET}
      PUBLIC -specs=${PSPDEV}/psp/sdk/lib/prxspecs
      PUBLIC -Wl,-q,-T${PSPDEV}/psp/sdk/lib/linkfile.prx
      PUBLIC ${PSPDEV}/psp/sdk/lib/prxexports.o)
  endif()

  if("${CMAKE_BUILD_TYPE}" STREQUAL "Release" AND NOT ${ARG_BUILD_PRX})
    add_custom_command(
      TARGET ${ARG_TARGET}
      POST_BUILD COMMAND
      "${PSPDEV}/bin/psp-strip" "$<TARGET_FILE:${ARG_TARGET}>"
      COMMENT "Stripping binary for target ${ARG_TARGET}"
      )
  elseif(${ARG_BUILD_PRX})
    add_custom_command(
      TARGET ${ARG_TARGET}
      POST_BUILD COMMAND
      ${CMAKE_COMMAND} -E cmake_echo_color --cyan "Not stripping binary for target ${ARG_TARGET} because building PRX."
      )
  else()
    add_custom_command(
      TARGET ${ARG_TARGET}
      POST_BUILD COMMAND
      ${CMAKE_COMMAND} -E cmake_echo_color --cyan "Not stripping binary for target ${ARG_TARGET}, build type is ${CMAKE_BUILD_TYPE}."
      )
  endif()

  add_custom_command(
    TARGET ${ARG_TARGET}
    POST_BUILD COMMAND
    "$ENV{PSPDEV}/bin/psp-fixup-imports" "$<TARGET_FILE:${ARG_TARGET}>"
    COMMENT "Calling psp-fixup-imports for target ${ARG_TARGET}"
    )

  if (${ARG_BUILD_PRX})
    add_custom_command(
      TARGET ${ARG_TARGET}
      POST_BUILD COMMAND
      "${PSPDEV}/bin/psp-prxgen" "$<TARGET_FILE:${ARG_TARGET}>"
      "$<TARGET_FILE:${ARG_TARGET}>.prx"
      COMMENT "Calling prxgen for target ${ARG_TARGET}"
      )

    if(${ARG_ENC_PRX})
      add_custom_command(
	TARGET ${ARG_TARGET}
	POST_BUILD COMMAND
	"${PSPDEV}/bin/PrxEncrypter" "$<TARGET_FILE_DIR:${ARG_TARGET}>/$<TARGET_FILE_NAME:${ARG_TARGET}>.prx"
	"$<TARGET_FILE:${ARG_TARGET}>.prx"
	COMMENT "Calling PrxEncrypter for target ${ARG_TARGET}"
	)
    else()
      add_custom_command(
	TARGET ${ARG_TARGET}
	POST_BUILD COMMAND
	${CMAKE_COMMAND} -E cmake_echo_color --cyan "Not encrypting PRX for target ${ARG_TARGET}, use ENC_PRX flag if you need to."
	)
    endif()
    
  else()
    add_custom_command(
      TARGET ${ARG_TARGET}
      POST_BUILD COMMAND
      ${CMAKE_COMMAND} -E cmake_echo_color --cyan "Not building PRX for target ${ARG_TARGET}"
      )
  endif()
  
  add_custom_command(
    TARGET ${ARG_TARGET}
    POST_BUILD COMMAND
    "${PSPDEV}/bin/mksfoex" "-d" "MEMSIZE=1" "-s" "APP_VER=${ARG_VERSION}" "${ARG_TITLE}" "${ARG_OUTPUT_DIR}/PARAM.SFO"
    COMMENT "Calling mksfoex for target ${ARG_TARGET}"
    )

  if(${ARG_BUILD_PRX})
    add_custom_command(
      TARGET ${ARG_TARGET}
      POST_BUILD COMMAND
      "${PSPDEV}/bin/pack-pbp" "${ARG_OUTPUT_DIR}/EBOOT.PBP" "${ARG_OUTPUT_DIR}/PARAM.SFO" "${ARG_ICON_PATH}" "NULL" "${ARG_PREVIEW_PATH}"
      "${ARG_BACKGROUND_PATH}" "${ARG_MUSIC_PATH}" "$<TARGET_FILE:${ARG_TARGET}>.prx" "NULL"
      COMMENT "Calling pack-pbp with PRX file for target ${ARG_TARGET}"
      )
  else()
    add_custom_command(
      TARGET ${ARG_TARGET}
      POST_BUILD COMMAND
      "${PSPDEV}/bin/pack-pbp" "${ARG_OUTPUT_DIR}/EBOOT.PBP" "${ARG_OUTPUT_DIR}/PARAM.SFO" "${ARG_ICON_PATH}" "NULL" "${ARG_PREVIEW_PATH}"
      "${ARG_BACKGROUND_PATH}" "${ARG_MUSIC_PATH}" "$<TARGET_FILE:${ARG_TARGET}>" "NULL"
      COMMENT "Calling pack-pbp with ELF file for target ${ARG_TARGET}"
      )
  endif()

  add_custom_command(
    TARGET ${APP} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E remove
    ${ARG_OUTPUT_DIR}/PARAM.SFO
    COMMENT "Cleaning up PARAM.SFO for target ${ARG_TARGET}"
  )

  add_custom_command(
    TARGET ${ARG_TARGET}
    POST_BUILD COMMAND
    ${CMAKE_COMMAND} -E cmake_echo_color --cyan "EBOOT.PBP file created for target ${ARG_TARGET}."
  )
  
endmacro()
