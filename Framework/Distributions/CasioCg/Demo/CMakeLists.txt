# Configure with [fxsdk build-fx] or [fxsdk build-cg], which provide the
# toolchain file and module path of the fxSDK

cmake_minimum_required(VERSION 3.15)
project(MyAddin)

include(GenerateG1A)
include(GenerateG3A)
include(Fxconv)
find_package(Gint 2.1 REQUIRED)

message(STATUS "Library path: ${LIBRARY_PATH}")

# Récupérer tous les fichiers sources, en excluant les fichiers de build
file(GLOB_RECURSE SOURCES
  "${CMAKE_CURRENT_SOURCE_DIR}/../srcs/*.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/ext/*.cpp"
)

# Filtrer les fichiers qui se trouvent dans le répertoire de build
list(FILTER SOURCES EXCLUDE REGEX "${CMAKE_BINARY_DIR}")

# Shared assets, fx-9860G-only assets and fx-CG-50-only assets
set(ASSETS
)
set(ASSETS_fx
)
set(ASSETS_cg
)

include_directories(${LIBRARY_PATH}/includes)
link_directories(${LIBRARY_PATH}/includes)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../includes)

fxconv_declare_assets(${ASSETS} ${ASSETS_fx} ${ASSETS_cg} WITH_METADATA)

add_executable(myaddin ${SOURCES} ${ASSETS} ${ASSETS_${FXSDK_PLATFORM}})
target_compile_options(myaddin PRIVATE -Wall -Wextra -Os)
target_link_libraries(myaddin Gint::Gint "${LIBRARY_PATH}/lib/libsupc++.a" "${LIBRARY_PATH}/lib/libparticule.a" stdc++) 

set(NAME_APP "demo")

set(DIR_OUT "bin")

generate_g3a(TARGET myaddin OUTPUT "${DIR_OUT}/${NAME_APP}.g3a"
    NAME "" ICONS assets/icon-uns.png assets/icon-sel.png)
