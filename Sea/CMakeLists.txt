cmake_minimum_required(VERSION 2.8)

project(Sea)


add_subdirectory(Src)
add_subdirectory(Test)
add_executable(${PROJECT_NAME} "main.cpp")

target_link_libraries(${PROJECT_NAME} sea_test sea_base "/usr/local/lib/libgtest.a" "-lpthread")
