project(SunsetCraft)

file(GLOB_RECURSE SOURCES "*.h" "*.cpp" "*.txt" "*.vert" "*.frag")

find_package(nlohmann_json CONFIG REQUIRED)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} PUBLIC
        SunsetEngine
        nlohmann_json::nlohmann_json
)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/Sources)
