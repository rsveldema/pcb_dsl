# -*- mode:cmake -*-


CMAKE_MINIMUM_REQUIRED(VERSION 2.8.12.2)
PROJECT(antlr4cpp_fetcher CXX)
FIND_PACKAGE(Git REQUIRED)

# only JRE required
FIND_PACKAGE(Java COMPONENTS Runtime REQUIRED)

############ Download and Generate runtime #################
set(ANTLR4CPP_EXTERNAL_ROOT ${CMAKE_BINARY_DIR}/externals/antlr4cpp)

# external repository
# GIT_REPOSITORY     https://github.com/antlr/antlr4.git
set(ANTLR4CPP_EXTERNAL_REPO "https://github.com/antlr/antlr4.git")
set(ANTLR4CPP_EXTERNAL_TAG  "4.7.1")

if(NOT EXISTS "${ANTLR4CPP_JAR_LOCATION}")
  message(FATAL_ERROR "Unable to find antlr tool. ANTLR4CPP_JAR_LOCATION:${ANTLR4CPP_JAR_LOCATION}")
endif()

# default path for source files
if (NOT ANTLR4CPP_GENERATED_SRC_DIR)
  set(ANTLR4CPP_GENERATED_SRC_DIR ${CMAKE_BINARY_DIR}/antlr4cpp_generated_src)
endif()

list(APPEND ANTLR4CPP_INCLUDE_DIRS ${INSTALL_DIR}/include/antlr4-runtime)
foreach(src_path misc atn dfa tree support)
  list(APPEND ANTLR4CPP_INCLUDE_DIRS ${INSTALL_DIR}/include/antlr4-runtime/${src_path})
endforeach(src_path)

set(ANTLR4CPP_LIBS "${INSTALL_DIR}/lib")

# antlr4_shared ${INSTALL_DIR}/lib/libantlr4-runtime.so
# antlr4_static ${INSTALL_DIR}/lib/libantlr4-runtime.a

############ Generate runtime #################
# macro to add dependencies to target
#
# Param 1 project name
# Param 1 namespace (postfix for dependencies)
# Param 2 Lexer file (full path)
# Param 3 Parser File (full path)
#
# output
#
# antlr4cpp_src_files_{namespace} - src files for add_executable
# antlr4cpp_include_dirs_{namespace} - include dir for generated headers
# antlr4cpp_generation_{namespace} - for add_dependencies tracking

macro(antlr4cpp_process_grammar
    antlr4cpp_project
    antlr4cpp_project_namespace
    antlr4cpp_grammar_parser)

  if(EXISTS "${ANTLR4CPP_JAR_LOCATION}")
    message(STATUS "Found antlr tool: ${ANTLR4CPP_JAR_LOCATION}")
  else()
    message(FATAL_ERROR "Unable to find antlr tool. ANTLR4CPP_JAR_LOCATION:${ANTLR4CPP_JAR_LOCATION}")
  endif()

  add_custom_target("antlr4cpp_generation_${antlr4cpp_project_namespace}"
    COMMAND
    ${CMAKE_COMMAND} -E make_directory ${ANTLR4CPP_GENERATED_SRC_DIR}
    COMMAND
    "${Java_JAVA_EXECUTABLE}" -jar "${ANTLR4CPP_JAR_LOCATION}" -Werror -Dlanguage=Cpp -listener -visitor -o "${ANTLR4CPP_GENERATED_SRC_DIR}/${antlr4cpp_project_namespace}" -package ${antlr4cpp_project_namespace} "${antlr4cpp_grammar_parser}"
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}"
    DEPENDS "${antlr4cpp_grammar_parser}"
    )

  # Find all the input files
  FILE(GLOB generated_files ${ANTLR4CPP_GENERATED_SRC_DIR}/${antlr4cpp_project_namespace}/*.cpp)

  # export generated cpp files into list
  foreach(generated_file ${generated_files})
    list(APPEND antlr4cpp_src_files_${antlr4cpp_project_namespace} ${generated_file})
    if (NOT CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    set_source_files_properties(
      ${generated_file}
      PROPERTIES
      COMPILE_FLAGS -Wno-overloaded-virtual
      )
    endif ()
  endforeach(generated_file)
  message(STATUS "Antlr4Cpp  ${antlr4cpp_project_namespace} Generated: ${generated_files}")

  # export generated include directory
  set(antlr4cpp_include_dirs_${antlr4cpp_project_namespace} ${ANTLR4CPP_GENERATED_SRC_DIR}/${antlr4cpp_project_namespace})
  message(STATUS "Antlr4Cpp ${antlr4cpp_project_namespace} include: ${ANTLR4CPP_GENERATED_SRC_DIR}/${antlr4cpp_project_namespace}")

endmacro()
