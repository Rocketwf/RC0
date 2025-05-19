cmake_minimum_required(VERSION 3.16)
project(main CXX)

# Set compiler and flags
set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_options(-Wall)

# Directories
set(SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)
set(BUILD_DIR ${CMAKE_BINARY_DIR})
set(OBJ_DIR ${BUILD_DIR}/obj)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Get all .cpp source files from src/
file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS ${SOURCE_DIR}/*.cpp)

# Create list of object files with paths under build/obj/
set(OBJECTS "")
foreach(SRC ${SOURCE_FILES})
    file(RELATIVE_PATH REL_PATH ${SOURCE_DIR} ${SRC})
    get_filename_component(OBJ_SUBDIR ${REL_PATH} DIRECTORY)
    get_filename_component(FILENAME ${SRC} NAME_WE)
    set(OBJ_PATH ${OBJ_DIR}/${OBJ_SUBDIR}/${FILENAME}.o)

    # Make sure the obj subdirectory exists at configure time
    file(MAKE_DIRECTORY ${OBJ_DIR}/${OBJ_SUBDIR})

    # Add a custom command to compile this source to its object
    add_custom_command(
        OUTPUT ${OBJ_PATH}
        COMMAND ${CMAKE_CXX_COMPILER}
                -std=c++20
                -Wall
                -I${SOURCE_DIR}
                -c ${SRC}
                -o ${OBJ_PATH}
        DEPENDS ${SRC}
        COMMENT "Compiling ${SRC} -> ${OBJ_PATH}"
        VERBATIM
    )
    list(APPEND OBJECTS ${OBJ_PATH})
endforeach()

# Custom target to build all objects
add_custom_target(build_objects ALL DEPENDS ${OBJECTS})

# Link all objects into the final executable
add_custom_command(
    OUTPUT ${BUILD_DIR}/main
    COMMAND ${CMAKE_CXX_COMPILER} ${OBJECTS} -o ${BUILD_DIR}/main
    DEPENDS ${OBJECTS}
    COMMENT "Linking executable main"
)

add_custom_target(main ALL DEPENDS ${BUILD_DIR}/main)

# Custom target: run
add_custom_target(run
    COMMAND ${BUILD_DIR}/main
    DEPENDS main
    WORKING_DIRECTORY ${BUILD_DIR}
)

# Custom target: rebuild
add_custom_target(rebuild
    COMMAND ${CMAKE_COMMAND} --build . --target clean
    COMMAND ${CMAKE_COMMAND} --build .
)

# Custom clean (removes the build dir)
add_custom_target(clean-all
    COMMAND ${CMAKE_COMMAND} -E rm -rf ${BUILD_DIR}
)
