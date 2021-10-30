add_executable(application main.cpp)
target_link_libraries(application Scheduler)

install (TARGETS application RUNTIME DESTINATION "${CMAKE_SOURCE_DIR}/install")