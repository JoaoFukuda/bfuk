add_executable(bfuk main.cpp)
target_link_libraries(bfuk PRIVATE libbfuk_interpreter PRIVATE libbfuk_term)

install(TARGETS bfuk)
