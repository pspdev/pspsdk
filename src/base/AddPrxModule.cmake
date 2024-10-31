# File defining macro outputting PSP-specific PRX module out of passed executable target.
cmake_minimum_required(VERSION 3.10)

function(add_prx_module name)
  # Initialize list for existing and generated source files
  set(SRC_FILES)

  # Loop over each source file
  foreach(FILE ${ARGN})
    # Get the extension of the file
    get_filename_component(FILE_EXTENSION ${FILE} EXT)

    # Generate a .c file from .exp files
    if (${FILE_EXTENSION} EQUAL ".exp")
      # Get the filename without extension
      get_filename_component(EXP_FILE_NAME ${FILE} NAME_WE)

      # Define the output .c file path
      set(GENERATED_C_FILE ${CMAKE_BINARY_DIR}/${EXP_FILE_NAME}.c)

      # Add a custom command for each .exp file to generate a .c file
      add_custom_command(
          OUTPUT ${GENERATED_C_FILE}
          COMMAND psp-build-exports -b ${EXP_FILE} > ${GENERATED_C_FILE}
          DEPENDS ${EXP_FILE}
          COMMENT "Generating ${EXP_FILE_NAME}.c from ${EXP_FILE_NAME}.exp"
      )

      # Add the generated .c file to the list
      list(APPEND SRC_FILES ${GENERATED_C_FILE})
    else()
      # Simply add other files to the list
      list(APPEND SRC_FILES ${FILE})
    endif()
  endforeach()

  add_executable(${name} ${SRC_FILES})
  target_link_options(${name} PRIVATE -Wl,-q,-T${PSPDEV}/psp/sdk/lib/linkfile.prx -nostartfiles -Wl,-zmax-page-size=128)

  add_custom_command(
    TARGET ${name}
    POST_BUILD COMMAND
    "$ENV{PSPDEV}/bin/psp-fixup-imports" "$<TARGET_FILE:${name}>"
    COMMENT "Calling psp-fixup-imports for target ${name}"
  )

  # Generate the .prx module from executable target
  add_custom_command(
    TARGET ${name}
    POST_BUILD COMMAND
    "${PSPDEV}/bin/psp-prxgen" "$<TARGET_FILE:${name}>"
    "$<TARGET_FILE:${name}>.prx"
    COMMENT "Calling prxgen for target ${name}"
  )
endfunction()
