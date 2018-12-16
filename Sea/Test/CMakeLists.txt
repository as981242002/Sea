cmake_minimum_required(VERSION 2.8)
set(test_SRCS
    TestLog.cpp
)

add_library(sea_test STATIC ${test_SRCS})
target_link_libraries(sea_test pthread rt)

#install(TARGETS sea_test DESTINATION lib)

#file(GLOB HEADERS "*.h")
#install(FILES ${HEADERS} DESTINATION include/sea/test)

