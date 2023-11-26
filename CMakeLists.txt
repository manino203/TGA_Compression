cmake_minimum_required(VERSION 3.25.1)
project(TGA_Compression C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=address -g")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -g")
find_package(PkgConfig REQUIRED)
pkg_check_modules(deps REQUIRED IMPORTED_TARGET glib-2.0)
add_executable(jbk
        main.c
        compression.c
        decompression.c
)
target_compile_options(jbk PRIVATE -fsanitize=address -g)
target_link_libraries(jbk PkgConfig::deps)

