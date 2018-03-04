CMAKE_MINIMUM_REQUIRED(VERSION 3.5)
SET (CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -Wno-attributes -g2")

message("CMAKE DIR IS "  ${PROJECT_SOURCE_DIR}/cmake)

LIST( APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake )

project (pcb_dsl)

# set variable pointing to the antlr tool that supports C++
set(ANTLR4CPP_JAR_LOCATION ${PROJECT_SOURCE_DIR}/thirdparty/antlr/antlr-4.7.1-complete.jar)


include( ./cmake/ExternalAntlr4Cpp.cmake )
include( ./cmake/FindBoost.cmake )
include( ./cmake/FindCairo.cmake )

FIND_PACKAGE( Boost 1.64 COMPONENTS program_options REQUIRED )

include_directories( ${Boost_INCLUDE_DIR} )
include_directories( ${ANTLR4CPP_INCLUDE_DIRS} )

link_directories( ${ANTLR4CPP_LIBS} )
message(STATUS "Found antlr4cpp libs: ${ANTLR4CPP_LIBS} and includes: ${ANTLR4CPP_INCLUDE_DIRS} ")

# Call macro to add lexer and grammar to your build dependencies.
antlr4cpp_process_grammar(pcbgen
	  antlrcpp
	${CMAKE_CURRENT_SOURCE_DIR}/dsl.antlr4)

include_directories(${antlr4cpp_include_dirs} antlr4cpp_generated_src/antlrcpp )
include_directories( ${CMAKE_CURRENT_BINARY_DIR} )



add_executable(pcbgen count_overlaps.cc main.cc draw.cc sum_lengths.cc place_routing_components.cc random_move.cc crossover.cc crossing.cc display.cc optimizer.cc utils.cc create_model.cc model.cc datasheet.cc known_packages.cc ${antlr4cpp_src_files_antlrcpp})


#find_package(Cairo)
include_directories( ${Cairomm_INCLUDE_DIRS} ${Gtkmm_INCLUDE_DIRS} )

#add_dependencies(pcbgen antlr4cpp antlr4cpp_generation_antlrcpp)
target_link_libraries(pcbgen antlr4-runtime ${Sigcpp_LIBRARIES}  ${Boost_LIBRARIES} ${Cairomm_LIBRARIES} ${Gtkmm_LIBRARIES} ${Glibmm_LIBRARIES} -lsigc-2.0 -latkmm-1.6 -lX11 -lpthread)


