cmake_minimum_required(VERSION 3.14)
project(Balls)

add_subdirectory(deps/SDL EXCLUDE_FROM_ALL) # Do not rebuild

file(GLOB SOURCES "src/*.c")

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} m)
target_link_libraries(${PROJECT_NAME} SDL3)
target_link_directories(${PROJECT_NAME} PRIVATE deps/SDL/build)

target_include_directories(${PROJECT_NAME} PRIVATE deps/SDL/include)
