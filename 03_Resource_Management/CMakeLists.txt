include_directories(${CMAKE_CURRENT_LIST_DIR})
file(GLOB SOURCES_FILES ABSOLUTE ${CMAKE_CURRENT_LIST_DIR}/*.cpp)
foreach(SOURCES_FILE ${SOURCES_FILES})
    get_filename_component(SOURCES_FILE_NAME ${SOURCES_FILE} NAME_WE)
    add_executable(${SOURCES_FILE_NAME} "${SOURCES_FILE}")
endforeach()
