cmake_minimum_required(VERSION 3.0.0)
project(lb_lexer VERSION 0.0.1)

include_directories(${PROJECT_SOURCE_DIR}/include)

file(GLOB_RECURSE SRC_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp)

add_executable(lb_lexer ${SRC_FILES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

include(CPack)

find_package(spdlog CONFIG REQUIRED)
target_link_libraries(lb_lexer PRIVATE spdlog::spdlog spdlog::spdlog_header_only)
