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
include_directories("${CMAKE_CURRENT_LIST_DIR}/submodule/glm/")
include_directories("${CMAKE_CURRENT_LIST_DIR}/submodule/stb/")

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
  # filesystem
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
foreach(component ${Boost_COMPONENTS} Boost)
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
sweet_target_add(a CONFIGS Boost)
sweet_target_add(a CONFIGS fmt)
sweet_target_add(a CONFIGS OpenCV)
sweet_target_add(a CONFIGS glbinding)
sweet_target_add(a CONFIGS glfw3)

add_executable(b spike/glbinding-example.cpp)
sweet_target_add(b CONFIGS Boost)
sweet_target_add(b CONFIGS fmt)
sweet_target_add(b CONFIGS OpenCV)
sweet_target_add(b CONFIGS glbinding)
sweet_target_add(b CONFIGS glfw3)

add_executable(imgui spike/imgui.cpp)
sweet_target_add(imgui CONFIGS Boost)
sweet_target_add(imgui CONFIGS fmt)
sweet_target_add(imgui CONFIGS OpenCV)
sweet_target_add(imgui CONFIGS glbinding)
sweet_target_add(imgui CONFIGS glfw3)
sweet_target_add(imgui CONFIGS imgui)
# sweet_target_add(imgui CONFIGS imgui_impl)

add_executable(tut1 src/tut1.cpp)
sweet_target_add(tut1 CONFIGS Boost)
sweet_target_add(tut1 CONFIGS fmt)
sweet_target_add(tut1 CONFIGS OpenCV)
sweet_target_add(tut1 CONFIGS glbinding)
sweet_target_add(tut1 CONFIGS glfw3)
# sweet_target_add(tut1 CONFIGS imgui)

add_executable(tut2 src/tut2.cpp)
sweet_target_add(tut2 CONFIGS Boost)
sweet_target_add(tut2 CONFIGS fmt)
sweet_target_add(tut2 CONFIGS OpenCV)
sweet_target_add(tut2 CONFIGS glbinding)
sweet_target_add(tut2 CONFIGS glfw3)

add_library(1.3.shader src/1.3.shader.cpp)
sweet_target_add(1.3.shader CONFIGS glbinding)
sweet_target_add(1.3.shader CONFIGS glfw3)

set(executables
  1.1.hello_window
  1.2.hello_triangle
  1.2.hello_rectangle
  1.2.hello_polygon
  1.3.red_triangle
  1.3.breath_triangle
  1.3.mix_color_triangle
  1.3.our_own_shader_class
  1.4.texture
  1.4.texture2
  1.5.transformation
  1.6.coordinate_system
  1.6.coordinate_system2
  1.6.coordinate_system3
  sensor_emitter_server
  )

foreach(exe IN LISTS executables)
  add_executable(${exe} src/${exe}.cpp)
  sweet_target_add(${exe} CONFIGS Boost)
  sweet_target_add(${exe} CONFIGS fmt)
  sweet_target_add(${exe} CONFIGS OpenCV)
  sweet_target_add(${exe} CONFIGS glbinding)
  sweet_target_add(${exe} CONFIGS glfw3)
endforeach()
# target_link_directories(  sensor_emitter_server PRIVATE /home/cy20lin/pj/cpp_module/module/boost/install/lib )
message(${Boost_LIBRARIES})
target_link_libraries(  sensor_emitter_server PRIVATE ${Boost_LIBRARIES})
  # /home/cy20lin/pj/cpp_module/module/boost/install/lib/libboost_system.so
  # libboost_system
  # )

sweet_target_add(1.3.our_own_shader_class LIBRARIES PRIVATE 1.3.shader)
configure_file(src/1.3.our_own_shader_class-vertex_shader.glsl
  1.3.our_own_shader_class-vertex_shader.glsl
  COPYONLY
  )
configure_file(src/1.3.our_own_shader_class-fragment_shader.glsl
  1.3.our_own_shader_class-fragment_shader.glsl
  COPYONLY
  )

sweet_target_add(1.4.texture LIBRARIES PRIVATE 1.3.shader)
configure_file(src/1.4.texture-vertex.glsl 1.4.texture-vertex.glsl COPYONLY)
configure_file(src/1.4.texture-fragment.glsl 1.4.texture-fragment.glsl COPYONLY)
configure_file(resource/wall.jpg wall.jpg COPYONLY)
configure_file(resource/awesomeface.png awesomeface.png COPYONLY)
configure_file(resource/container.jpg container.jpg COPYONLY)
configure_file(resource/grass_side.png grass_side.png COPYONLY)
configure_file(resource/grass_top.png grass_top.png COPYONLY)
configure_file(resource/grass_path_top.png grass_path_top.png COPYONLY)
configure_file(resource/dirt.png dirt.png COPYONLY)

sweet_target_add(1.4.texture2 LIBRARIES PRIVATE 1.3.shader)
configure_file(src/1.4.texture2-vertex.glsl 1.4.texture2-vertex.glsl COPYONLY)
configure_file(src/1.4.texture2-fragment.glsl 1.4.texture2-fragment.glsl COPYONLY)

sweet_target_add(1.5.transformation LIBRARIES PRIVATE 1.3.shader)
configure_file(src/1.5.transformation-vertex.glsl 1.5.transformation-vertex.glsl COPYONLY)
configure_file(src/1.5.transformation-fragment.glsl 1.5.transformation-fragment.glsl COPYONLY)

sweet_target_add(1.6.coordinate_system LIBRARIES PRIVATE 1.3.shader)
configure_file(src/1.6.coordinate_system-vertex.glsl 1.6.coordinate_system-vertex.glsl COPYONLY)
configure_file(src/1.6.coordinate_system-fragment.glsl 1.6.coordinate_system-fragment.glsl COPYONLY)


sweet_target_add(1.6.coordinate_system2 LIBRARIES PRIVATE 1.3.shader)
sweet_target_add(1.6.coordinate_system3 LIBRARIES PRIVATE 1.3.shader)
configure_file(src/1.6.coordinate_system2-vertex.glsl 1.6.coordinate_system2-vertex.glsl COPYONLY)
configure_file(src/1.6.coordinate_system2-fragment.glsl 1.6.coordinate_system2-fragment.glsl COPYONLY)

