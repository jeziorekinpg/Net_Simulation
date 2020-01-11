cmake_minimum_required(VERSION 3.15)
# Zdefiniuj projekt o nazwie "Net_Simulation".
project(Net_Simulation)

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
        src/nodes.cpp                   # ścieżka do pliku 'nodes.cpp'
        src/helpers.cpp                 # ścieżka do pliku 'helpers.cpp'
        src/factory.cpp                 # ścieżka do pliku 'factory.cpp'
        )

# Uwzględnij zawartość zmiennej `SOURCE_FILES` w procesie kompilacji.
#add_executable(Net_Simulation ${SOURCE_FILES} main.cpp)

add_executable(Net_Simulation__test ${SOURCE_FILES})
