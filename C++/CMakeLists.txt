CMAKE_MINIMUM_REQUIRED(VERSION 3.10)

#ADD_DEFINITIONS("-Wall -std=c++11")

PROJECT(SummerTime)

AUX_SOURCE_DIRECTORY(${PROJECT_SOURCE_DIR}/src DIR_SRC)
AUX_SOURCE_DIRECTORY(${PROJECT_SOURCE_DIR}/src/tools DIR_SRC)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/output/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/output/lib)

INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/src/include)

#ADD_SUBDIRECTORY(${PROJECT_SOURCE_DIR}/test)

#ADD_LIBRARY(lib SHARED xxx.cpp)

ADD_EXECUTABLE(${PROJECT_NAME} ${DIR_SRC})

#TARGET_LINK_LIBRARY(SummerTime lib)
