project(SunsetCraft)

file(GLOB_RECURSE SOURCES "*.h" "*.cpp" "*.txt" "*.vert" "*.frag")

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} PUBLIC
        SunsetEngine
)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/Sources)
