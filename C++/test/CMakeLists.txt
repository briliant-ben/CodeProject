CMAKE_MINIMUM_REQUIRED(VERSION 3.10)

#ADD_DEFINITIONS("-Wall -std=c++11")

PROJECT(gtest)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/output/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/output/lib)

INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/include)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/../src/include)

AUX_SOURCE_DIRECTORY(${PROJECT_SOURCE_DIR}/unitest DIR_TEST_SRC)
AUX_SOURCE_DIRECTORY(${PROJECT_SOURCE_DIR}/../src/tools DIR_SRC)

LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/lib)

ADD_EXECUTABLE(${PROJECT_NAME} ${DIR_TEST_SRC} ${DIR_SRC})

TARGET_LINK_LIBRARIES(${PROJECT_NAME} libgtest.a libgtest_main.a pthread)
