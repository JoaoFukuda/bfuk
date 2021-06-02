cmake_minimum_required(VERSION 3.5)
project(bfuk)

link_libraries(pthread)

add_executable(bfuk src/main.cpp src/interpreter.cpp src/term.cpp)
target_compile_options(bfuk PRIVATE
	$<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:
		-Werror
		-Wall
		-Wextra
		-Wshadow
		-Wunused
		-Wnon-virtual-dtor
		-Wold-style-cast
		-Wcast-align
		-Wunused
		-Woverloaded-virtual
		-Wpedantic
		-Wconversion
		-Wsign-conversion
		-Wmisleading-indentation
		-Wduplicated-cond
		-Wduplicated-branches
		-Wlogical-op
		-Wnull-dereference
		-Wuseless-cast
		-Wdouble-promotion
		-Wformat=2>
	$<$<CXX_COMPILER_ID:MSVC>:
		/W4
		/w14242
		/w14254
		/w14263
		/w14265
		/w14287
		/we4289
		/w14296
		/w14311
		/w14545
		/w14546
		/w14547
		/w14549
		/w14555
		/w14619
		/w14640
		/w14826
		/w14905
		/w14906
		/w14928>)

find_package(Catch2 REQUIRED)
add_executable(test src/tests.cpp src/interpreter.cpp)
include_directories(test ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_link_libraries(test Catch2Main Catch2)
