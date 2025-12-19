cmake_minimum_required(VERSION 4.1)

add_library(MiniMotor_compiler_flags INTERFACE)
target_compile_features(MiniMotor_compiler_flags INTERFACE cxx_std_20)

project(SunsetCraft)

add_subdirectory(Engine)
add_subdirectory(SunsetCraft)
