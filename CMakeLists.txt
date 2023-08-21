cmake_minimum_required(VERSION 3.1)

project(SatisParsery)

include_directories(src)

aux_source_directory(src SRC_DIR)
aux_source_directory(src/DrawioElements DRAWIO_ELEMENTS_DIR)
aux_source_directory(src/RecipeElements RECIPE_ELEMENTS_DIR)

add_compile_options(-Wall --std=c++17)

add_executable(${PROJECT_NAME} ${SRC_DIR}
                               ${DRAWIO_ELEMENTS_DIR}
                               ${RECIPE_ELEMENTS_DIR})
