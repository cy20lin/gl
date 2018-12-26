cmake_minimum_required (VERSION 3.1)											#	set cmake minimum version

list(INSERT CMAKE_MODULE_PATH 0 "${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules")
list(INSERT CMAKE_MODULE_PATH 0 "${CMAKE_CURRENT_SOURCE_DIR}/submodule/sweet")
include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/utility.cmake")

# Q. can 'project(projname)' command used before 'include("cmake/HunterGate")' ??
project(2018_fall_image_processing_final)
show_variables(CMAKE_SYSTEM_PREFIX_PATH)
show_variables(CMAKE_PREFIX_PATH)

# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/export/bin")
# set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/export/lib")
# set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/export/lib")

set(CMAKE_C_STANDARD              90)
set(CMAKE_C_STANDARD_REQUIRED     ON)
set(CMAKE_CXX_STANDARD            14)
set(CMAKE_CXX_STANDARD_REQUIRED   ON)

include_directories("${CMAKE_CURRENT_LIST_DIR}/include")

set(Boost_USE_STATIC_LIBS        ON) # only find static libs
set(Boost_COMPONENTS
  # atomic
  # chrono
  # container
  # context
  # coroutine
  # date_time
  # exception
  # fiber
  filesystem
  # iostreams
  # locale
  # random
  # regex
  # serialization
  system
  # thread
  )

find_package(Boost REQUIRED COMPONENTS ${Boost_COMPONENTS})
find_package(fmt CONFIG)
find_package(date CONFIG)
find_package(OpenCV REQUIRED)
find_package(glbinding)
find_package(glfw3)

set(packages
  Boost
  fmt
  OpenCV
  date
  glbinding
  glfw3
  )
foreach(component ${Boost_COMPONENTS} boost)
  if(TARGET Boost::${component})
    sweet_config_add(Boost LIBRARIES PRIVATE Boost::${component})
  endif()
endforeach()

if(WIN32)
  # boost.asio dependency
  sweet_config_add(Boost LIBRARIES PRIVATE wsock32 ws2_32)
endif()

sweet_config_add(imgui INCLUDES PRIVATE
  ./submodule
  ./submodule/imgui
  )
sweet_config_add(imgui SOURCES PRIVATE
  ./submodule/imgui/imgui.cpp
  ./submodule/imgui/imgui_demo.cpp
  ./submodule/imgui/imgui_draw.cpp
  ./submodule/imgui/imgui_widgets.cpp
  )

sweet_config_add(imgui_impl SOURCES PRIVATE
  ./submodule/imgui/examples/imgui_impl_opengl3.cpp
  ./submodule/imgui/examples/imgui_impl_glfw.cpp
  )

sweet_config_add(fmt LIBRARIES PRIVATE fmt)
sweet_config_add(date LIBRARIES PRIVATE date_interface)
sweet_config_add(glbinding LIBRARIES PRIVATE glbinding::glbinding glbinding::glbinding-aux)
sweet_config_add(glfw3 LIBRARIES PRIVATE glfw)

show_variables(glbinding_FOUND)
show_variables(glfw3_FOUND)
show_variables(date_FOUND)
foreach(package ${packages})
  config_from_generic_package("${package}" "${package}")
  message(STATUS " config: ${package}=${${package}_CONFIG_SETTINGS}")
endforeach()

add_executable(a spike/glbinding-example.cpp)
sweet_target_add(a CONFIGS boost)
sweet_target_add(a CONFIGS fmt)
sweet_target_add(a CONFIGS OpenCV)
sweet_target_add(a CONFIGS glbinding)
sweet_target_add(a CONFIGS glfw3)

add_executable(b spike/glbinding-example.cpp)
sweet_target_add(b CONFIGS boost)
sweet_target_add(b CONFIGS fmt)
sweet_target_add(b CONFIGS OpenCV)
sweet_target_add(b CONFIGS glbinding)
sweet_target_add(b CONFIGS glfw3)

add_executable(imgui spike/imgui.cpp)
sweet_target_add(imgui CONFIGS boost)
sweet_target_add(imgui CONFIGS fmt)
sweet_target_add(imgui CONFIGS OpenCV)
sweet_target_add(imgui CONFIGS glbinding)
sweet_target_add(imgui CONFIGS glfw3)
sweet_target_add(imgui CONFIGS imgui)
# sweet_target_add(imgui CONFIGS imgui_impl)

add_executable(tut1 src/tut1.cpp)
sweet_target_add(tut1 CONFIGS boost)
sweet_target_add(tut1 CONFIGS fmt)
sweet_target_add(tut1 CONFIGS OpenCV)
sweet_target_add(tut1 CONFIGS glbinding)
sweet_target_add(tut1 CONFIGS glfw3)
# sweet_target_add(tut1 CONFIGS imgui)

add_executable(tut2 src/tut2.cpp)
sweet_target_add(tut2 CONFIGS boost)
sweet_target_add(tut2 CONFIGS fmt)
sweet_target_add(tut2 CONFIGS OpenCV)
sweet_target_add(tut2 CONFIGS glbinding)
sweet_target_add(tut2 CONFIGS glfw3)
