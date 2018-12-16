cmake_minimum_required(VERSION 2.8)

set(base_SRCS
    ../Src/Base/Utility/Log.cpp
    ../Src/Base/Utility/LogStream.cpp
    ../Src/Base/Date.cpp
    ../Src/Base/TimeZone.cpp
)

add_library(sea_base STATIC ${base_SRCS})
target_link_libraries(sea_base pthread rt)

#install(TARGETS sea_base DESTINATION lib)

#file(GLOB HEADERS "*.h")
#install(FILES ${HEADERS} DESTINATION include/sea/src/base)

