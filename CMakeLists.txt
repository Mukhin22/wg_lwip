cmake_minimum_required(VERSION 3.8)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS -pthread)
project(wg C)

SET(GCC_LINK_FLAGS    "-nostartfiles -Wall -g -pthread")

set (CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(LWIP_CONTRIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lwip-contrib)
set(LWIP_DIR         ${CMAKE_CURRENT_SOURCE_DIR}/lwip)
set(SRC_DIR          ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(CRYPTO_DIR       ${SRC_DIR}/crypto/refc)
include(${LWIP_CONTRIB_DIR}/ports/CMakeCommon.cmake)

set (LWIP_DEFINITIONS -DLWIP_DEBUG)
set (LWIP_INCLUDE_DIRS
    "${LWIP_DIR}/src/include"
    # "${LWIP_CONTRIB_DIR}/ports/unix/port/include"
    # "${LWIP_CONTRIB_DIR}/examples/example_app"
    "${LWIP_CONTRIB_DIR}/"
    "${SRC_DIR}/crypto/refc"
    "${SRC_DIR}"
)

include(${LWIP_DIR}/src/Filelists.cmake)
include(${LWIP_CONTRIB_DIR}/Filelists.cmake)
include(${LWIP_CONTRIB_DIR}/ports/unix/Filelists.cmake)


add_executable(wg "${CMAKE_CURRENT_SOURCE_DIR}"  wg.c src/wireguard.c src/wireguardif.c src/wireguard-platform.c
src/crypto.c src/arch/sys_arch.c)

add_subdirectory("${CRYPTO_DIR}")

target_link_libraries(wg crypto)


target_include_directories(wg PRIVATE ${LWIP_INCLUDE_DIRS})

add_definitions("${GCC_LINK_FLAGS}")

target_compile_definitions(wg PRIVATE ${LWIP_DEFINITIONS})

target_link_libraries(wg ${LWIP_SANITIZER_LIBS} lwipcore ) # lwipallapps lwipcontribportunix
