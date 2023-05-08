set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/config.h.in ${CMAKE_CURRENT_BINARY_DIR}/config.h)

# Function for building single example
function(buildExample EXAMPLE_NAME)
	SET(EXAMPLE_FOLDER ${CMAKE_CURRENT_SOURCE_DIR}/${EXAMPLE_NAME})
    message(STATUS "Generating project file for example in ${EXAMPLE_FOLDER}")
	# Main
	file(GLOB SOURCES ${EXAMPLE_FOLDER}/*.cpp)
	SET(MAIN_CPP ${EXAMPLE_FOLDER}/${EXAMPLE_NAME}.cpp)
	if(EXISTS ${EXAMPLE_FOLDER}/main.cpp)
		SET(MAIN_CPP ${EXAMPLE_FOLDER}/main.cpp)
	ENDIF()

	# Add shaders
	file(GLOB SHADERS ${EXAMPLE_FOLDER}/*.vert ${EXAMPLE_FOLDER}/*.frag)
	add_executable(${EXAMPLE_NAME} ${MAIN_CPP} ${SOURCES} ${SHADERS})
	target_link_libraries(${EXAMPLE_NAME} PRIVATE base)
	target_include_directories(${EXAMPLE_NAME} PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
endfunction(buildExample)

set(EXAMPLES
    triangle
    shaders
    textures
	transformations
	coordinate_systems
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
