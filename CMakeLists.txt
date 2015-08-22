cmake_minimum_required(VERSION 3.2)
project( GeniEngine2_Framework )

set(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/src)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/allegro/include)

link_directories(${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/allegro/lib/)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)


file(GLOB_RECURSE all_files 
	${DIRECTORY}/*.cpp
	${DIRECTORY}/*.h
)

add_executable( GeniEngine2_Framework
	${all_files}
)

foreach(f ${all_files})
    file(RELATIVE_PATH SRCGR ${DIRECTORY} ${f})
    set(SRCGR "src/${SRCGR}")
    string(REGEX REPLACE "(.*)(/[^/]*)$" "\\1" SRCGR ${SRCGR})
    string(REPLACE / \\ SRCGR ${SRCGR})
    source_group("${SRCGR}" FILES ${f})
endforeach()

add_definitions(-DALLEGRO_STATICLINK)
target_link_libraries (GeniEngine2_Framework allegro-5.0.10-monolith-static-md.lib)
target_link_libraries (GeniEngine2_Framework winmm.lib)
target_link_libraries (GeniEngine2_Framework psapi.lib)
target_link_libraries (GeniEngine2_Framework shlwapi.lib)
target_link_libraries (GeniEngine2_Framework "C:/Program Files (x86)/Windows Kits/8.1/Lib/winv6.3/um/x86/dinput8.lib")
target_link_libraries (GeniEngine2_Framework "C:/Program Files (x86)/Windows Kits/8.1/Lib/winv6.3/um/x86/Xinput.lib")
target_link_libraries (GeniEngine2_Framework glu32.lib)
target_link_libraries (GeniEngine2_Framework opengl32.lib)