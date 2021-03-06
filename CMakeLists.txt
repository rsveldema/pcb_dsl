CMAKE_MINIMUM_REQUIRED(VERSION 3.5)
SET (CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -Wno-attributes -g2 -O0 -DUSE_GTK=1")
# -pg

message("CMAKE DIR IS "  ${PROJECT_SOURCE_DIR}/cmake)

LIST( APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake )

project (pcb_dsl)

# set variable pointing to the antlr tool that supports C++
set(ANTLR4CPP_JAR_LOCATION ${PROJECT_SOURCE_DIR}/thirdparty/antlr/antlr-4.7.1-complete.jar)

include( ./cmake/FindBoost.cmake )
include( ./cmake/FindCairo.cmake )
include( ./cmake/ExternalAntlr4Cpp.cmake )
execute_process( COMMAND bash -c "(cd antlr_runtime && cmake . && make)" )

FIND_PACKAGE( Boost 1.58 COMPONENTS program_options REQUIRED )

include_directories( ${Boost_INCLUDE_DIR} )
#include_directories( ${ANTLR4CPP_INCLUDE_DIRS} )
include_directories( "antlr_runtime/runtime/src" )

link_directories( ${ANTLR4CPP_LIBS} )
message(STATUS "Found antlr4cpp libs: ${ANTLR4CPP_LIBS} and includes: ${ANTLR4CPP_INCLUDE_DIRS} ")


# Call macro to add lexer and grammar to your build dependencies.
antlr4cpp_process_grammar(pcbgen
	  antlrcpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/dsl.antlr4)

include_directories( ${antlr4cpp_include_dirs} antlr4cpp_generated_src/antlrcpp )
include_directories( ${CMAKE_CURRENT_BINARY_DIR} )


file(GLOB pcbgen_SRC
    "src/*.hpp"
    "src/*.cc"
)

add_executable(pcbgen ${pcbgen_SRC} ${antlr4cpp_src_files_antlrcpp})

include_directories( ${Cairomm_INCLUDE_DIRS} ${Gtkmm_INCLUDE_DIRS} )

# comment this out if you see too much recompilation.
add_dependencies(pcbgen antlr4cpp_generation_antlrcpp)

target_link_libraries(pcbgen -Lantlr_runtime/dist -lantlr4-runtime ${Cairomm_LIBRARIES} ${Gtkmm_LIBRARIES} ${Glibmm_LIBRARIES} -lsigc-2.0 -latkmm-1.6 -lX11 -lpthread -g2 ${Sigcpp_LIBRARIES}  ${Boost_LIBRARIES} -lm)

#-pg
