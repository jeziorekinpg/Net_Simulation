cmake_minimum_required(VERSION 3.13)

project(NetSim)
set(CMAKE_CXX_STANDARD 17)

add_compile_options(-Wall -Wextra -Werror -Wpedantic -pedantic-errors)

include_directories(
        include
)

set(SOURCE_FILES
        src/package.cpp
        src/storage_types.cpp
        src/nodes.cpp
        src/helpers.cpp
        src/factory.cpp
        src/simulation.cpp
        src/reports.cpp
        )


set(SOURCES_FILES_TESTS
        #test/test_package.cpp
        #test/test_storage_types.cpp
        #test/test_nodes.cpp
        #test/test_Factory.cpp
        #test/test_factory_io.cpp
        test/test_simulate.cpp
        )

add_executable(test_wezly ${SOURCE_FILES} ${SOURCES_FILES_TESTS} test/main_gtest.cpp)
target_compile_definitions(test_wezly PUBLIC EXERCISE_ID=2)


target_include_directories(test_wezly PUBLIC
        googletest-master/googlemock/include
        googletest-master/googletest/include
        )

add_subdirectory(googletest-master googletest-master)

target_link_libraries(test_wezly gmock)
