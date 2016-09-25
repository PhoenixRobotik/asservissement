####################################################################
#   Project configuration
####################################################################
cmake_minimum_required(VERSION 3.4 FATAL_ERROR)

# Toolchain = architecture utilisée
include("${CMAKE_CURRENT_SOURCE_DIR}/../toolchains/${ARCH}.cmake")

project (PhoenixAsservissement)
set     (PhoenixAsservissement_VERSION_MAJOR 0)
set     (PhoenixAsservissement_VERSION_MINOR 1)

####################################################################
#   Source
####################################################################
# Déclaration du nom (public) de la librairie
set(Library cartographieLib)

# Fichier de réglages dépendant de la plateforme
if(${ARCH} STREQUAL PC)
    set(REGLAGES_H "PC.h")
else()
    set(REGLAGES_H "${ROBOT}_robot.h")
endif()
add_definitions("-DREGLAGES_HEADER=\"reglages/${REGLAGES_H}\"")

## Déclaration de la librairie aux projets qui utilisent celui-ci
# Déclaration des sources de la librairie
add_library(${Library} STATIC
    asser.c
    PID.c
    odometrie.c
    trajectoire.c
    math_precalc.c
    tests_unitaires.c
    reception_communication.c
    hardware_${ARCH}.c
)
# Includes publics
target_include_directories(${Library} INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/>
)
target_link_libraries(${Library} INTERFACE
    m
)

# Librairie à linker
export(TARGETS ${Library} FILE Librairie.cmake)

include_directories(..)

add_executable(asservissement
    ${CMAKE_CURRENT_SOURCE_DIR}/main.c
)
target_link_libraries(asservissement
    ${Library}
)
