cmake_minimum_required(VERSION 3.8)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS -pthread)
project(wg C)

SET(GCC_LINK_FLAGS    "-Wall -g -pthread")

set (CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(LWIP_CONTRIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lwip-contrib)
set(LWIP_DIR         ${CMAKE_CURRENT_SOURCE_DIR}/lwip)
set(SRC_DIR          ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(CRYPTO_DIR       ${SRC_DIR}/crypto/refc)
set(MINIMAL_DIR      ${CMAKE_CURRENT_SOURCE_DIR}/minimal)
set(TAPIF_DIR        ${LWIP_CONTRIB_DIR}/ports/unix/port/include)
include(${LWIP_CONTRIB_DIR}/ports/CMakeCommon.cmake)

set (LWIP_DEFINITIONS -DLWIP_DEBUG)
set (LWIP_INCLUDE_DIRS
    "${LWIP_DIR}/src/include"
    "${LWIP_CONTRIB_DIR}/"
    "${SRC_DIR}/crypto/refc"
    "${SRC_DIR}"
    "${MINIMAL_DIR}"
    "${TAPIF_DIR}"
)

include(${LWIP_DIR}/src/Filelists.cmake)
include(${LWIP_CONTRIB_DIR}/Filelists.cmake)
include(${LWIP_CONTRIB_DIR}/ports/unix/Filelists.cmake)

add_library(wg STATIC  wg.c src/wireguard.c src/wireguardif.c src/wireguard-platform.c
src/crypto.c src/arch/sys_arch.c)

add_executable(echop "${MINIMAL_DIR}" minimal/main.c minimal/tapif.c lwip-contrib/apps/udpecho_raw/udpecho_raw.c 
lwip-contrib/apps/tcpecho_raw/tcpecho_raw.c src/arch/sys_arch.c)#minimal/custom_timers.c)

add_subdirectory("${CRYPTO_DIR}")

target_link_libraries(wg crypto lwipcore)


target_include_directories(wg PRIVATE ${LWIP_INCLUDE_DIRS})
target_include_directories(echop PRIVATE ${LWIP_INCLUDE_DIRS})
target_include_directories(wg PRIVATE ${CRYPTO_DIR})
target_include_directories(wg PRIVATE ${MINIMAL_DIR})

target_link_libraries(echop lwipcore wg crypto)
#lwipcontribexamples lwipcontribaddons lwipcontribapps
target_compile_definitions(echop PRIVATE ${LWIP_DEFINITIONS})

add_definitions("${GCC_LINK_FLAGS}")

target_compile_definitions(wg PRIVATE ${LWIP_DEFINITIONS})

target_link_libraries(wg ${LWIP_SANITIZER_LIBS} lwipcore )
