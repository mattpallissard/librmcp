cmake_minimum_required(VERSION 3.12.4)
project(librmcp VERSION 0.0.1 LANGUAGES C)


if(CODE_COVERAGE AND CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
  set(CMAKE_BUILD_TYPE Debug)
  set(CMAKE_EXPORT_COMPILE_COMMANDS True)
  # Add required flags (GCC & LLVM/Clang)
  link_libraries("-fsanitize=address -fno-omit-frame-pointer")
  target_compile_options(coverage_config INTERFACE
    -O0        # no optimization
    -g         # generate debug info
	#-fsanitize=address
	#-fno-omit-frame-pointer
    --coverage # sets all required flags
  )
  if(CMAKE_VERSION VERSION_GREATER_EQUAL 3.13)
    target_link_options(coverage_config INTERFACE --coverage)
  else()
    target_link_libraries(coverage_config INTERFACE --coverage)
  endif()
endif(CODE_COVERAGE AND CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")

include_directories( include )

add_library(rmcp STATIC src/rmcp.c)

add_executable(t_unit src/test.c)
add_executable(print_ping src/print_ping.c)

target_link_libraries(print_ping rmcp)
target_link_libraries(t_unit rmcp)

enable_testing()
add_test(NAME unit_tests COMMAND ./t_unit)
