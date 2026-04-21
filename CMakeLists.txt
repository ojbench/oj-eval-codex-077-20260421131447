cmake_minimum_required(VERSION 3.10)
project(problem_077 LANGUAGES CXX)

# For this OJ problem, the evaluator expects a plain-text file named
# `code` at the project root that contains the header implementation.
# We therefore create a custom target that copies `crossarray.hpp` to `code`.

add_custom_target(build_code ALL
    COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_CURRENT_SOURCE_DIR}/crossarray.hpp
            ${CMAKE_CURRENT_BINARY_DIR}/code
    BYPRODUCTS ${CMAKE_CURRENT_BINARY_DIR}/code
    COMMENT "Copying crossarray.hpp to code for OJ"
)
