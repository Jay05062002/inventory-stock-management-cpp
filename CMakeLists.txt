cmake_minimum_required(VERSION 3.16)

project(InventoryManagementSystem
    VERSION 1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(inventory
    main.cpp
    Product.cpp
    Inventory.cpp
)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(inventory PRIVATE
        -Wall
        -Wextra
        -Wpedantic
    )
endif()
