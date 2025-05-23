#https://github.com/meemknight/cmakeSetup

cmake_minimum_required(VERSION 3.16)

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>") #we want to use the static runtime
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Release>:Release>")

project(mygame)

#add_subdirectory(thirdparty/SDL2-2.30.11)         https://github.com/libsdl-org/SDL/releases/tag/release-2.30.11 download SDL2-devel-2.30.11-VC.zip
add_subdirectory(thirdparty/glad)				   #opengl loader
add_subdirectory(thirdparty/stb_image)			   #loading immaged
add_subdirectory(thirdparty/stb_truetype)		   #loading ttf files
add_subdirectory(thirdparty/glm)				   #math



# Define MY_SOURCES to be a list of all the source files for my game 
file(GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")


add_executable("${CMAKE_PROJECT_NAME}")

set_property(TARGET "${CMAKE_PROJECT_NAME}" PROPERTY CXX_STANDARD 17)

target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC RESOURCES_PATH="${CMAKE_CURRENT_SOURCE_DIR}/resources/") # This is useful to get an ASSETS_PATH in your IDE during development but you should comment this if you compile a release version and uncomment the next line
#target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC RESOURCES_PATH="./resources/") # Uncomment this line to setup the ASSETS_PATH macro to the final assets directory when you share the game


target_sources("${CMAKE_PROJECT_NAME}" PRIVATE ${MY_SOURCES}  "src/acts/mainTriangleTexture.cpp")


if(MSVC) # If using the VS compiler...

	target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC _CRT_SECURE_NO_WARNINGS)

	#remove console
	#set_target_properties("${CMAKE_PROJECT_NAME}" PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
	
	set_property(TARGET "${CMAKE_PROJECT_NAME}" PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreadedDebug<$<CONFIG:Debug>:Debug>")
	set_property(TARGET "${CMAKE_PROJECT_NAME}" PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Release>:Release>")

endif()

set(SDL2_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/SDL2-2.30.11/include/")

# Support both 32 and 64 bit builds
if (${CMAKE_SIZEOF_VOID_P} MATCHES 8)
  set(SDL2_LIBRARIES "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/SDL2-2.30.11/lib/x64/SDL2.lib;${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/SDL2-2.30.11/lib/x64/SDL2main.lib")
else ()
  set(SDL2_LIBRARIES "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/SDL2-2.30.11/lib/x86/SDL2.lib;${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/SDL2-2.30.11/lib/x86/SDL2main.lib")
endif ()


target_include_directories("${CMAKE_PROJECT_NAME}" PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/" "${SDL2_INCLUDE_DIRS}")


target_link_libraries("${CMAKE_PROJECT_NAME}" PRIVATE glm ${SDL2_LIBRARIES} glad stb_image stb_truetype)

#copy/replace resources folder to build directory
add_custom_command(TARGET mygame PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_CURRENT_SOURCE_DIR}/resources $<TARGET_FILE_DIR:mygame>/resources)