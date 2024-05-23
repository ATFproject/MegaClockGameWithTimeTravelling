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

# Fetch and compile TGUI library
set(TGUI_BACKEND "SFML_GRAPHICS")
set(TGUI_SHARED_LIBS ON)
set(TGUI_BUILD_GUI_BUILDER ON)

message(STATUS "Downloading TGUI")
FetchContent_Declare(tgui SYSTEM
        GIT_REPOSITORY https://github.com/texus/TGUI.git
        GIT_TAG v1.1.0)
FetchContent_MakeAvailable(tgui)

message(STATUS "Downloading nlohmann/json")
FetchContent_Declare(json SYSTEM
        GIT_REPOSITORY https://github.com/nlohmann/json.git
        GIT_TAG v3.11.3)
FetchContent_MakeAvailable(json)

# Get all cpp files in the project recursively to a variable
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "src/*.cpp")

# Add all cpp files to compilation and add prefix
add_executable(${PROJECT_NAME} ${SOURCES})

# Link SFML and Box2D and TGUI to final binary and set C++ standard for it
target_link_libraries(${PROJECT_NAME}
        PRIVATE sfml-graphics
        PRIVATE sfml-audio
        PRIVATE box2d
        PRIVATE tgui
        PRIVATE nlohmann_json::nlohmann_json
)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_23)

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

# Add all possible warnings to make sure (Шура?) our code is the best!
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(${PROJECT_NAME} PRIVATE
            -Werror -Wall -Wextra -Wpedantic -Wcast-align -Wcast-qual -Wctor-dtor-privacy
            -Wenum-compare -Wnon-virtual-dtor -Wold-style-cast -Woverloaded-virtual
            -Wredundant-decls -Wsign-promo -Wsign-conversion
            -Wno-unused-variable -Wno-float-equal -Wno-unknown-pragmas -Wno-conversion -Wno-unused-parameter
    )
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(${PROJECT_NAME} PRIVATE /W3)
endif ()

# Set output file name
set(OUT_FILE_NAME ${PROJECT_NAME}-${CMAKE_BUILD_TYPE})
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME ${OUT_FILE_NAME})

# Add header dirs for easier usage
# EXAMPLE: set(ADDITIONAL_INCLUDE_DIRS "src/engine" "src/window")
set(ADDITIONAL_INCLUDE_DIRS "src" "src/engine" "src/mcgwtt/components")
target_include_directories(${PROJECT_NAME} PRIVATE ${ADDITIONAL_INCLUDE_DIRS})

target_precompile_headers(${PROJECT_NAME}
        PUBLIC "src/engine/EngineDef.h"
)
# Compile and link the app
install(TARGETS ${PROJECT_NAME})