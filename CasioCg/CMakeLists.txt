cmake_minimum_required(VERSION 3.10)
project(Particule)

# Inclure les modules
include(GenerateG1A)
include(GenerateG3A)
include(Fxconv)
find_package(Gint 2.1 REQUIRED)

# Définition des variables
set(CFLAGS -I ${CMAKE_BINARY_DIR}/includes)
set(LDLIBS -lm -L ${CMAKE_BINARY_DIR}/includes)
set(OUTPUT ${CMAKE_BINARY_DIR}/../bin)
set(NAME particule)

# Répertoire source
file(GLOB_RECURSE SRCS 
    "../Particule/*.cpp"
    "./Particule/*.cpp"
)

# Include directories
include_directories(
    ${OUTPUT}/includes
)

# Configuration des options de compilation et de liaison
add_compile_options(${CPPFLAGS} ${CFLAGS})
link_libraries(${LDFLAGS} ${LDLIBS} Gint::Gint ${CMAKE_CURRENT_SOURCE_DIR}/libsupc++.a)

# Générer les fichiers objets
add_library(${NAME} STATIC ${SRCS})

# Custom commands for post-build
add_custom_command(TARGET ${NAME} POST_BUILD
    COMMENT "Particule.a done !"
)

# Custom target for includes
add_custom_target(includes ALL
    COMMAND ${CMAKE_COMMAND} -E make_directory ${OUTPUT}/includes
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/../Particule/includes ${OUTPUT}/includes
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/Particule/includes ${OUTPUT}/includes
    COMMENT "Includes copied"
)

# Dépendance de la bibliothèque sur la cible includes
add_dependencies(${NAME} includes)