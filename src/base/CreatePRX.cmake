# File defining macro outputting PSP-specific PRX module out of passed executable target.
cmake_minimum_required(VERSION 3.10)

macro(add_prx_module)
  
  set(OPTIONS_ARGS)
  set(ONE_VALUE_ARGS
    TARGET # CMake target for the prx module that is being output
  )
  set(MULTI_VALUE_ARGS
    SRC_FILES # Source files for the module
    EXP_FILES # Export files for the module
  )

  cmake_parse_arguments("ARG" "${OPTIONS_ARGS}" "${ONE_VALUE_ARGS}" "${MULTI_VALUE_ARGS}" ${ARGN} )

  # Initialize a list to store generated .c files
  set(GENERATED_C_FILES)

  # Loop over each .exp file to set up a rule to generate a corresponding .c file
  foreach(EXP_FILE ${ARG_EXP_FILES})
    # Get the filename without extension
    get_filename_component(EXP_FILE_NAME ${EXP_FILE} NAME_WE)

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
    list(APPEND GENERATED_C_FILES ${GENERATED_C_FILE})
  endforeach()

  add_executable(${ARG_TARGET} ${ARG_SRC_FILES} ${GENERATED_C_FILES})
  target_link_options(${ARG_TARGET} PRIVATE -Wl,-q,-T${PSPDEV}/psp/sdk/lib/linkfile.prx -nostartfiles -Wl,-zmax-page-size=128)

  add_custom_command(
    TARGET ${ARG_TARGET}
    POST_BUILD COMMAND
    "$ENV{PSPDEV}/bin/psp-fixup-imports" "$<TARGET_FILE:${ARG_TARGET}>"
    COMMENT "Calling psp-fixup-imports"
  )

  add_custom_command(
    TARGET ${ARG_TARGET}
    POST_BUILD COMMAND
    "${PSPDEV}/bin/psp-prxgen" "$<TARGET_FILE:${ARG_TARGET}>"
    "$<TARGET_FILE:${ARG_TARGET}>.prx"
    COMMENT "Calling prxgen"
  )
endmacro(add_prx_module)
