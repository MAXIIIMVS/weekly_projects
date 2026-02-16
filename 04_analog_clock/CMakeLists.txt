cmake_minimum_required(VERSION 3.16)

project(main LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ---- Raylib ----
set(RAYLIB_VERSION 5.5)

find_package(raylib ${RAYLIB_VERSION} QUIET) # QUIET or REQUIRED
if (NOT raylib_FOUND) # If there's none, fetch and build raylib
	include(FetchContent)
	FetchContent_Declare(
				raylib
				DOWNLOAD_EXTRACT_TIMESTAMP OFF
				URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
		)
	FetchContent_GetProperties(raylib)
	if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
		set(FETCHCONTENT_QUIET NO)
		FetchContent_MakeAvailable(raylib)
	endif()
endif()

# ---- Executable ----
add_executable(main src/main.c)

target_link_libraries(main PRIVATE raylib)

# ---- Warnings & Debug Flags (GCC/Clang only) ----
if (CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
	target_compile_options(main PRIVATE
		-Wall
		-Wextra
		-Wpedantic
		-Wsign-conversion
		-Werror
		-ggdb3
	)
endif()
