# Project details
cmake_minimum_required(VERSION 3.20)
project(SDL_mask)

# Global options

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(INC_DIR "${CMAKE_SOURCE_DIR}/include")
set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")
set(LIB_A "${PROJECT_NAME}-static")
set(LIB_SO "${PROJECT_NAME}")
set(INC "${INC_DIR}/${PROJECT_NAME}.h")
set(SRC "${SRC_DIR}/${PROJECT_NAME}.c")
set(TEST_MAIN test/test.c)
set(EXAMPLE_MAIN example/example.c)
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

# Targets

add_library(${LIB_SO} SHARED ${SRC})
add_library(${LIB_A} STATIC ${SRC})
add_executable(test EXCLUDE_FROM_ALL ${TEST_MAIN} ${SRC})
add_executable(example EXCLUDE_FROM_ALL ${EXAMPLE_MAIN})

# Target options

set_target_properties(${LIB_A} PROPERTIES OUTPUT_NAME ${PROJECT_NAME})
target_include_directories(${LIB_SO} PRIVATE ${INC_DIR} ${SRC_DIR})
target_include_directories(${LIB_A} PRIVATE ${INC_DIR} ${SRC_DIR})
target_include_directories(test PRIVATE ${INC_DIR} ${SRC_DIR})
target_link_libraries(test PRIVATE SDL2 SDL2_image)
target_link_libraries(example PRIVATE SDL2 SDL2_image ${PROJECT_NAME})

install(TARGETS ${LIB_A} ARCHIVE DESTINATION lib)
install(TARGETS ${LIB_SO} LIBRARY DESTINATION lib)
install(FILES ${INC} DESTINATION include)

# Platform-specific options
if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang|AppleClang")
	message("Compiling with Gcc/Clang")
	target_compile_options(${LIB_SO} PRIVATE -O3 -march=native -flto)
	target_compile_options(${LIB_A} PRIVATE -O3 -march=native -flto)
	target_compile_options(test PRIVATE -Wall -Wextra -Werror -Wunused-result -Wconversion)
	target_compile_options(example PRIVATE -Wall -Wextra -Werror -Wunused-result -Wconversion)
endif()
