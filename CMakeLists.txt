# Set up cmake and c++ settings
cmake_minimum_required(VERSION 3.8)
project(MegaClockGameWithTimeTravelling VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set output directory for the binary and disable shared library building
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/out)

if (WIN32)
    option(BUILD_SHARED_LIBS "Build shared libraries" OFF)
else ()
    option(BUILD_SHARED_LIBS "Build shared libraries" ON)
endif ()

# Include tool for content fetching
include(FetchContent REQUIRED)

# Fetch and compile SFML library
message(STATUS "Downloading SFML")
FetchContent_Declare(SFML SYSTEM
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)


# Fetch and compile Box2D library
message(STATUS "Downloading Box2D")
FetchContent_Declare(box2d SYSTEM
        GIT_REPOSITORY https://github.com/erincatto/box2d.git
        GIT_TAG v2.4.1)
FetchContent_MakeAvailable(box2d)

set(CMAKE_CXX_CPPCHECK "cppcheck")
find_program(${PROJECT_NAME} NAMES cppcheck)

# Get all cpp files in the project recursively to a variable
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "src/*.cpp")

# Add all cpp files to compilation and add prefix
add_executable(${PROJECT_NAME} ${SOURCES})

# Link SFML and Box2D to final binary and set C++ standard for it
target_link_libraries(${PROJECT_NAME}
        PRIVATE sfml-graphics
        PRIVATE sfml-audio
        PRIVATE box2d
)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

# Disable all docs and example build for SFML and Box2D
if (WIN32)

else ()
    set(BOX2D_BUILD_DOCS OFF)
    set(BOX2D_BUILD_UNIT_TESTS OFF)
    set(SFML_BUILD_DOC OFF)
    set(SFML_BUILD_EXAMPLES OFF)
    set(SFML_BUILD_TEST_SUITE OFF)
    set(SFML_USE_SYSTEM_DEPS OFF)
    set(SFML_USE_DRM OFF)
endif ()

if (WIN32)
    add_custom_command(
            TARGET ${PROJECT_NAME}
            COMMENT "Copy OpenAL DLL"
            PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:${PROJECT_NAME}>
            VERBATIM)
    add_custom_command(
            TARGET ${PROJECT_NAME}
            COMMENT "Copy box2d dll"
            PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/build/${CMAKE_BUILD_TYPE}/_deps/box2d-build/bin/box2d.dll $<TARGET_FILE_DIR:${PROJECT_NAME}>
            VERBATIM)
endif ()

# Add all possible warnings to make sure (Шура?) our code is the best!
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(${PROJECT_NAME} PRIVATE
            -Werror -Wall -Wextra -Wpedantic -Wcast-align -Wcast-qual -Wctor-dtor-privacy
            -Wenum-compare -Wnon-virtual-dtor -Wold-style-cast -Woverloaded-virtual
            -Wredundant-decls -Wsign-promo -Wsign-conversion
            -Wno-unused-variable -Wno-float-equal -Wno-unknown-pragmas -Wno-conversion -Wno-unused-parameter
    )
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(${PROJECT_NAME} PRIVATE /W4 /WX)
endif ()

# Set output file name
set(OUT_FILE_NAME ${PROJECT_NAME}-${CMAKE_BUILD_TYPE})
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME ${OUT_FILE_NAME})

# Add header dirs for easier usage
# EXAMPLE: set(ADDITIONAL_INCLUDE_DIRS "src/engine" "src/window")
set(ADDITIONAL_INCLUDE_DIRS "src" "src/engine/window" "src/engine")
target_include_directories(${PROJECT_NAME} PRIVATE ${ADDITIONAL_INCLUDE_DIRS})

# Compile and link the app
install(TARGETS ${PROJECT_NAME})