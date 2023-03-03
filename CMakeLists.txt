cmake_minimum_required(VERSION 3.18)

project(route-operator-driver-licenses-post)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
include(${CMAKE_BINARY_DIR}/commonoptions.cmake)
conan_basic_setup()

include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(BEFORE SYSTEM ${CONAN_INCLUDE_DIRS_BOOST})
include_directories(BEFORE SYSTEM ${CONAN_INCLUDE_DIRS_RAPIDJSON})
include_directories(BEFORE SYSTEM ${CONAN_INCLUDE_DIRS_LIBMYSQLCLIENT})
include_directories(BEFORE SYSTEM ${CONAN_INCLUDE_DIRS_HIREDIS})
include_directories(BEFORE SYSTEM ${CONAN_INCLUDE_DIRS_MONGO})

add_library(${PROJECT_NAME}-static STATIC ${CMAKE_SOURCE_DIR}/src/handler.cpp)
target_link_libraries(${PROJECT_NAME}-static ${CONAN_LIBS})

add_library(${PROJECT_NAME} SHARED ${CMAKE_SOURCE_DIR}/src/plugin.cpp)
target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}-static ${CONAN_LIBS})

enable_testing()

add_executable(unit_test ${CMAKE_SOURCE_DIR}/src/unit_test/main.cpp)
target_link_libraries(unit_test ${CONAN_LIBS})
add_test(NAME unit_test
    COMMAND ${CMAKE_BINARY_DIR}/bin/unit_test
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})