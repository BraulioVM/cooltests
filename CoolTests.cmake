include_guard()

set(cooltestslib_dir "${CMAKE_CURRENT_LIST_DIR}/cooltestslib")
set(cooltests_dir "${CMAKE_CURRENT_LIST_DIR}")

find_program(PYTHON python3.8 REQUIRED)

function(configure_cool_tests target)
  set(output_object "${PROJECT_BINARY_DIR}/cooltests_main_${target}.o")

  # it will get overwritten later, but I want to make CMake happy about
  # linking to an actual file
  file(TOUCH "${output_object}")

  # we link both the library that contains the 'main' function
  # and the object file that we will generate
  target_link_libraries(
    "${target}"
    cooltestslib
    "${output_object}"
  )

  # we schedule cooltests.py to be run right before the
  # target is linked. This gives us time to generate the
  # right object file.
  add_custom_command(TARGET "${target}"
    COMMAND
    ${PYTHON} "${cooltests_dir}/cooltests.py"
              "${output_object}"
              "'$<TARGET_OBJECTS:${target}>'"
	      "${cooltestslib_dir}"
	      "${CMAKE_CXX_COMPILER}"
	      # we are using the current build's compiler to build the
	      # object file. We are still probably missing ways in which the
	      # resulting object file can be ABI incompatible with the user's
	      # code, but this is just a prototype anyway.
    PRE_LINK
    WORKING_DIRECTORY "${cooltests_dir}"
    )

  # we also register the executable as a test
  add_test(NAME "${target}"
    COMMAND $<TARGET_FILE_NAME:${target}>
    )

endfunction()
