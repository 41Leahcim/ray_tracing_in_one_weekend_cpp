cmake_minimum_required(VERSION 3.10)
project(ray_tracer)
file(GLOB SOURCES "src/*.cpp")
add_executable(ray_tracer ${SOURCES})
