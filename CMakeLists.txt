cmake_minimum_required(VERSION 3.16)
project(cpp-lab-7-8)

set(CMAKE_CPP_STANDARD 11)

set(Header Customer.h)
set(Sources Customer.cpp)

add_compile_options(-pthread)

add_library(Customer.h STATIC ${Sources} ${Headers})


set(Header MaintenanceRecord.h)
set(Sources MaintenanceRecord.cpp)

add_compile_options(-pthread)

add_library(MaintenanceRecord.h STATIC ${Sources} ${Headers})


set(Header Vehicle.h)
set(Sources Vehicle.cpp)

add_compile_options(-pthread)
SET(CMAKE_CPP_FLAGS "${CMAKE_CPP_FLAGS} -pthread")

add_library(Vehicle.h STATIC ${Sources} ${Headers})

add_executable(cpp-lab-7-8 main.cpp Customer.cpp Customer.h Vehicle.h Vehicle.cpp MaintenanceRecord.h MaintenanceRecord.cpp)
