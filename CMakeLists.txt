cmake_minimum_required(VERSION 3.10)

project(cgql2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED on)
set(CMAKE_EXPORT_COMPILE_COMMANDS on)

add_library(cgql2Source)

target_include_directories(cgql2Source
  PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

set(SOURCES
  schema/schemaImpl.cpp
  schema/printSchema.cpp
)

target_sources(cgql2Source PRIVATE ${SOURCES})

add_subdirectory(tests)
