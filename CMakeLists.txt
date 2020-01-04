cmake_minimum_required(VERSION 3.15)
# Zdefiniuj projekt o nazwie "NetSimulation".
project(NetSimulation)

# Korzystaj ze standardu C++17.
set(CMAKE_CXX_STANDARD 17)

# Ustaw flagi kompilacji.
add_compile_options(-Wall -Wextra -Werror -Wpedantic -pedantic-errors)

# Uwzględnij katalog 'include'
include_directories(include)

# Utwórz zmienną `SOURCE_FILES` przechowującą ścieżki do plików źródłowych.
set(SOURCE_FILES
        src/package.cpp                 # ścieżka do pliku `package.cpp`
        src/storage_types.cpp           # ścieżka do pliku `storage_types.cpp`
        )

# Uwzględnij zawartość zmiennej `SOURCE_FILES` w procesie kompilacji.
add_executable(NetSimulation ${SOURCE_FILES} main.cpp)

set(SOURCES_FILES_TESTS
        test/test.cpp
        )

add_executable(NetSimulation__test ${SOURCE_FILES} ${SOURCES_FILES_TESTS} test/test.cpp)
