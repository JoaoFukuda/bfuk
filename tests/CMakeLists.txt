find_package(Catch2)
IF (${Catch2_FOUND})
	add_executable(test_libbfuk_interpreter tests.cpp)
	target_link_libraries(test_libbfuk_interpreter PRIVATE libbfuk_interpreter PRIVATE Catch2::Catch2)

	add_test(NAME test_libbfuk COMMAND test_libbfuk_interpreter)
endif(${Catch2_FOUND})
