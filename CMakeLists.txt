cmake_minimum_required(VERSION 3.10.0)
project(lab4 VERSION 0.1.0 LANGUAGES C CXX)


add_compile_definitions(LOGIC_LIBRARY)

# 1. Собираем библиотеку (она общая для консоли и для тестов)
add_library(logic SHARED 
    domain.h 
    logic.h 
    main.cpp
)


add_executable(lab4_app main.cpp)
target_link_libraries(lab4_app logic)

add_executable(unit_tests main_test.cpp)
target_link_libraries(unit_tests logic)

include(CTest)
enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
