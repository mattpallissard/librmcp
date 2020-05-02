cmake_minimum_required(VERSION 3.12.4)
project(librmcp VERSION 0.0.1 LANGUAGES C)

include_directories( include )

add_library(rmcp STATIC src/rmcp.c)
if(CODE_COVERAGE)
	set(CMAKE_BUILD_TYPE Debug)
	set(CMAKE_EXPORT_COMPILE_COMMANDS True)
	link_libraries("-fsanitize=address -fno-omit-frame-pointer")
	target_compile_options(rmcp INTERFACE
		-O0
		-g
		-fsanitize=address
		-fno-omit-frame-pointer
		--coverage
	)
	if(CMAKE_VERSION VERSION_GREATER_EQUAL 3.13)
		target_link_options(rmcp INTERFACE --coverage)
	else()
		target_link_libraries(rmcp INTERFACE --coverage)
	endif()
endif(CODE_COVERAGE)

add_executable(t_unit src/test.c)
if(WITH_EXAMPLES)
	add_executable(print_ping src/print_ping.c)
	add_executable(open_session src/open_session.c)
	target_link_libraries(open_session rmcp)
	target_link_libraries(print_ping rmcp)
endif(WITH_EXAMPLES)

target_link_libraries(t_unit rmcp)

enable_testing()
add_test(NAME unit_tests COMMAND ./t_unit)
