####################################################################
#   Project configuration
####################################################################
cmake_minimum_required(VERSION 3.4 FATAL_ERROR)

project (PhoenixAsservissement)
set     (PhoenixAsservissement_VERSION_MAJOR 0)
set     (PhoenixAsservissement_VERSION_MINOR 1)

include(${GenericCmakeLists})

####################################################################
#   Source
####################################################################
# Fichier de réglages dépendant de la plateforme
set(ROBOT gros)
if(${TOOLCHAIN} STREQUAL PC)
    set(REGLAGES_H "PC.h")
else()
    set(REGLAGES_H "${ROBOT}_robot.h")
endif()
add_definitions("-DREGLAGES_HEADER=\"reglages/${REGLAGES_H}\"")

## Déclaration de la librairie aux projets qui utilisent celui-ci
# Déclaration des sources de la librairie
add_library(${PROJECT_NAME}Lib STATIC
    asser.c
    PID.c
    odometrie.c
    trajectoire.c
    math_precalc.c
    tests_unitaires.c
    reception_communication.c
    hardware_${TOOLCHAIN}.c
)
# Includes publics
target_include_directories(${PROJECT_NAME}Lib INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/>
)
target_link_libraries(${PROJECT_NAME}Lib INTERFACE
    m
)

# Librairie à linker
export(TARGETS ${PROJECT_NAME}Lib FILE Librairie.cmake)

include_directories(..)

add_executable(${PROJECT_NAME}
    ${CMAKE_CURRENT_SOURCE_DIR}/main.c
)
add_executable(main_binary ALIAS ${PROJECT_NAME})
target_link_libraries(${PROJECT_NAME}
    ${PROJECT_NAME}Lib
    ${Toolchain_LFlags}
)
