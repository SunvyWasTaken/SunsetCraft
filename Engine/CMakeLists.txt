project(SunsetEngine)

file(GLOB_RECURSE SOURCES "*.h" "*.cpp" "*.txt")

find_package(OpenGL REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(Stb REQUIRED)

add_library(${PROJECT_NAME} STATIC
        ${SOURCES}
)

target_include_directories(${PROJECT_NAME} PRIVATE
        ${Stb_INCLUDE_DIR}
)

target_link_libraries(${PROJECT_NAME} PRIVATE
        glad::glad
        OpenGL::GL
        glfw
)

target_include_directories(${PROJECT_NAME} PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME} PUBLIC
        MiniMotor_compiler_flags
        glm::glm
)

target_precompile_headers(${PROJECT_NAME} PUBLIC
        SunsetPCH.h
)
