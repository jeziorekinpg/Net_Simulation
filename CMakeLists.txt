cmake_minimum_required(VERSION 3.13)
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
        src/test.cpp                    # ścieżka do pliku 'test.cpp'
        )

# Uwzględnij zawartość zmiennej `SOURCE_FILES` w procesie kompilacji.
add_executable(NetSimulation ${SOURCE_FILES} main.cpp)
