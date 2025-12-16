# do le version
cmake_minimum_required(VERSION 3.18.1)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(myProject)

add_executable(${PROJECT_NAME}
  # day_one/part_one.cpp
  # day_one/part_two.cpp
  # day_two/part_one.cpp
  # day_two/part_two.cpp
  # day_three/part_one.cpp
  # day_three/part_two.cpp
  day_four/part_one_two.cpp
  # main.cpp
)

if(WIN32)
    target_link_options(${PROJECT_NAME} PRIVATE -mconsole)
endif()
