cmake_minimum_required(VERSION 3.12)

project(
    ASCIILib
    VERSION 0.0.0
    LANGUAGES C
)

file(GLOB_RECURSE ASCIILIB_SRC ${PROJECT_SOURCE_DIR}/src/*)
file(GLOB_RECURSE ASCIILIB_INC ${PROJECT_SOURCE_DIR}/include/*)
add_library(ASCIILib ${ASCIILIB_SRC} ${ASCIILIB_INC})
target_include_directories(ASCIILib PUBLIC ${PROJECT_SOURCE_DIR}/include)

file(GLOB_RECURSE IMAGE-CONVERTER_SRC ${PROJECT_SOURCE_DIR}/examples/image-converter/src/*)
file(GLOB_RECURSE IMAGE-CONVERTER_INC ${PROJECT_SOURCE_DIR}/examples/image-converter/include/*)
add_executable(image-converter ${IMAGE-CONVERTER_SRC} ${IMAGE-CONVERTER_INC})

target_include_directories(image-converter
    PUBLIC ${PROJECT_SOURCE_DIR}/include
    PUBLIC ${PROJECT_SOURCE_DIR}/examples/image-converter/include
)
target_link_libraries(image-converter PUBLIC ASCIILib png)
target_compile_options(image-converter PUBLIC -lpng)

