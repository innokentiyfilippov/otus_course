cmake_minimum_required(VERSION 3.10)

project(otus_course CXX)

if (DEFINED ENV{GITHUB_RUN_NUMBER})
  add_definitions(-DGITHUB_RUN_NUMBER=$ENV{GITHUB_RUN_NUMBER})
endif()

add_executable(helloworld main.cpp)
add_library(ipfilter ip_filter.cpp)

target_include_directories(helloworld PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(helloworld PRIVATE
    ipfilter
)

target_compile_features(ipfilter PUBLIC cxx_std_17)
target_compile_features(helloworld PUBLIC cxx_std_17)

