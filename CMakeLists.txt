cmake_minimum_required(VERSION 3.10)

project(helloworld CXX)

add_executable(helloworld main.cpp)
target_compile_features(helloworld PUBLIC cxx_std_17)
