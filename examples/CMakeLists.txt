# Function for building single example
function(buildExample EXAMPLE_NAME)
	SET(EXAMPLE_FOLDER ${CMAKE_CURRENT_SOURCE_DIR}/${EXAMPLE_NAME})
    message(STATUS "Generating project file for example in ${EXAMPLE_FOLDER}")
	# Main
	file(GLOB SOURCE ${EXAMPLE_FOLDER}/*.cpp)
	SET(MAIN_CPP ${EXAMPLE_FOLDER}/${EXAMPLE_NAME}.cpp)
	if(EXISTS ${EXAMPLE_FOLDER}/main.cpp)
		SET(MAIN_CPP ${EXAMPLE_FOLDER}/main.cpp)
	ENDIF()

	add_executable(${EXAMPLE_NAME} ${MAIN_CPP} ${SOURCE})
	target_link_libraries(${EXAMPLE_NAME} PRIVATE base)
endfunction(buildExample)

set(EXAMPLES
    triangle
)

# Function for building single example
function(buildExamples)
    foreach(EXAMPLE ${EXAMPLES})
        buildExample(${EXAMPLE})
    endforeach()
endfunction(buildExamples)

if(BUILD_EXAMPLES)
	buildExamples()
endif(BUILD_EXAMPLES)
