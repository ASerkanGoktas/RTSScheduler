cmake_minimum_required(VERSION 3.10)

# set the project name
project(Schedulers)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
add_library(Scheduler SHARED 
			RMScheduler.cpp 
			Scheduler.cpp 
			DFScheduler.cpp
			EDFScheduler.cpp
			LLFScheduler.cpp
			${CMAKE_SOURCE_DIR}/include/RTSScheduler/LLFScheduler.h 
			${CMAKE_SOURCE_DIR}/include/RTSScheduler/EDFScheduler.h 
			${CMAKE_SOURCE_DIR}/include/RTSScheduler/DFScheduler.h 
			${CMAKE_SOURCE_DIR}/include/RTSScheduler/RMScheduler.h 
			${CMAKE_SOURCE_DIR}/include/RTSScheduler/Scheduler.h 
			${CMAKE_SOURCE_DIR}/include/RTSScheduler/Task.h
)

target_include_directories(Scheduler PUBLIC ${CMAKE_SOURCE_DIR}/include)
install (TARGETS Scheduler RUNTIME DESTINATION "${CMAKE_SOURCE_DIR}/install")

add_subdirectory(application)

