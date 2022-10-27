add_library(queue_p queue_p.cpp)

add_executable(queue_p_test queue_p_test.cpp)
target_link_libraries(queue_p_test queue_p)
target_compile_options(queue_p PRIVATE -fPIC)

add_library(c_queue_p SHARED c_queue_p.cpp)
target_link_libraries(c_queue_p queue_p)
# target_compile_options(c_queue_p POSITION_INDEPENDENT_CODE)