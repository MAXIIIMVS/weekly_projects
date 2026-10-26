cmake_minimum_required(VERSION 4.2)
project(starfield LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED On)

add_subdirectory(src)

include(FetchContent)

FetchContent_Declare(
	SDL3
	GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
	GIT_TAG        release-3.4.18
	GIT_SHALLOW    TRUE
)

set(SDL_SHARED ON CACHE BOOL "" FORCE)
set(SDL_STATIC OFF CACHE BOOL "" FORCE)
set(SDL_TESTS OFF CACHE BOOL "" FORCE)
set(SDL_EXAMPLES OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(SDL3)

add_executable(starfield src/main.cpp)

target_link_libraries(starfield PRIVATE SDL3::SDL3)

if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
	target_compile_options(starfield PRIVATE
		-Wall
		-Wextra
		-Wpedantic
		-Wsign-conversion
		-Werror
		-ggdb3
	)
endif()
