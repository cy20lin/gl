include(sweet)

function(show_variables)
  foreach(var ${ARGV})
    message(STATUS "${var}=${${var}}")
  endforeach()
endfunction()

function(show_package_info package)
  message(STATUS "package=${package}")
  show_variables(
    ${package}_FOUND
    ${package}_LIBRARIES
    ${package}_LIBRARY
    ${package}_LIBS
    ${package}_INCLUDES
    ${package}_INCLUDE_DIR
    ${package}_INCLUDE_DIRS
    ${package}_DEFINITIONS
    )
endfunction()

macro(config_from_generic_package config package)
  message(STATUS "package=${package}")
  if(NOT "${package}" STREQUAL "")
    foreach(suffix LIBRARIES LIBRARY LIBS)
      if(NOT "${${package}_${suffix}}" STREQUAL "")
        # [NOTE] CMP0023
        #
        # target_link_libraries(mylib A)
        # target_link_libraries(mylib PRIVATE B)
        #
        # The OLD behavior for this policy is to allow keyword and plain
        # target_link_libraries signatures to be mixed. The NEW behavior for
        # this policy is to not to allow mixing of the keyword and plain
        # signatures.
        #
        # reference https://github.com/haka-security/haka/issues/22
        sweet_config(${config} ADD LIBRARIES PRIVATE ${${package}_${suffix}})
        break()
      endif()
    endforeach()
    foreach(suffix INCLUDES INCLUDE_DIR INCLUDE_DIRS)
      if (NOT "${${package}_${suffix}}" STREQUAL "")
        sweet_config(${config} ADD INCLUDES PRIVATE ${${package}_${suffix}})
        break()
      endif()
    endforeach()
    foreach(suffix DEFINITIONS)
      if (NOT "${${package}_${suffix}}" STREQUAL "")
        sweet_config(${config} ADD DEFINITIONS ${${package}_${suffix}})
        break()
      endif()
    endforeach()
  endif()
endmacro()
