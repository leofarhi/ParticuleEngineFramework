cmake_minimum_required(VERSION 3.10)
project(Particule)

# Inclure les modules
include(GenerateG1A)
include(GenerateG3A)
include(Fxconv)
find_package(Gint 2.1 REQUIRED)

# Définition des variables
set(CFLAGS -I ./includes)
set(LDLIBS -lm -L ./includes)
set(OUTPUT ./bin)
set(NAME particule)

# Répertoire source
file(GLOB_RECURSE SRCS 
    "./srcs/*.cpp"
)

# Include directories
include_directories(
    ./includes
)

# Configuration des options de compilation et de liaison
add_compile_options(${CPPFLAGS} ${CFLAGS})
link_libraries(${LDFLAGS} ${LDLIBS} Gint::Gint ${CMAKE_CURRENT_SOURCE_DIR}/lib/libsupc++.a)

# Générer les fichiers objets
add_library(${NAME} STATIC ${SRCS})

# Custom commands for post-build
add_custom_command(TARGET ${NAME} POST_BUILD
    COMMENT "Particule.a done !"
)