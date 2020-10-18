cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(test)

# c++0X support
set(CMAKE_CXX_FLAGS "-std=c++11 -O2")




#add_executable(class_test main.cpp)
add_executable(atm_demo main.cpp atm.cpp slot.cpp account.cpp bank.cpp cashbin.cpp)


