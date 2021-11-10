add_library(libbfuk_interpreter STATIC interpreter.cpp)
target_link_libraries(libbfuk_interpreter PRIVATE pthread)
target_include_directories(libbfuk_interpreter PUBLIC ../include)

add_library(libbfuk_term STATIC term.cpp)
target_include_directories(libbfuk_term PUBLIC ../include)
