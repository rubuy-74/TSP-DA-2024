cmake_minimum_required(VERSION 3.28)
project(TSP_DA_2024)

set(CMAKE_CXX_STANDARD 14)

include_directories(classes)

# Doxygen Build
find_package(Doxygen)
if(DOXYGEN_FOUND)
    set(BUILD_DOC_DIR "${CMAKE_SOURCE_DIR}/Doxyfile")
    if(NOT EXISTS "${BUILD_DOC_DIR}")
        file(MAKE_DIRECTORY "${BUILD_DOC_DIR}")
    endif()
    set(DOXYGEN_IN "${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile")
    set(DOXYGEN_OUT "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile")
    configure_file("${DOXYGEN_IN}" "${DOXYGEN_OUT}" @ONLY)
    message("Doxygen build started")
    add_custom_target(Doxygen ALL
            COMMAND "${DOXYGEN_EXECUTABLE}" "${DOXYGEN_OUT}"
            WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
            COMMENT "Generating API documentation with Doxygen"
            VERBATIM)
else(DOXYGEN_FOUND)
    message("Doxygen needs to be installed to generate the documentation.")
endif(DOXYGEN_FOUND)

add_executable(TSP_DA_2024
        classes/Dataset.cpp
        classes/Dataset.h
        classes/Graph.h
        classes/Parser.cpp
        classes/Parser.h
        main.cpp
        classes/Graph.cpp
        classes/TSP.h
        classes/TSP.cpp
        classes/Triangular.cpp
        classes/Triangular.h
        classes/MutablePriorityQueue.h
        classes/Heuristic.cpp
        classes/Heuristic.h
        classes/Prim.cpp
        classes/Prim.h
        classes/Menu.cpp
        classes/Menu.h)
