cmake_minimum_required(VERSION 3.8)
set(CMAKE_C_STANDARD 11)
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
    "${LWIP_CONTRIB_DIR}/ports/unix/port/include"
    "${LWIP_CONTRIB_DIR}/examples/example_app"
    "${LWIP_CONTRIB_DIR}/"
    "${SRC_DIR}/crypto/refc"
    "${SRC_DIR}"
)

include(${LWIP_DIR}/src/Filelists.cmake)
include(${LWIP_CONTRIB_DIR}/Filelists.cmake)
include(${LWIP_CONTRIB_DIR}/ports/unix/Filelists.cmake)


add_executable(wg "${CMAKE_CURRENT_SOURCE_DIR}"  wg.c src/wireguard.c src/wireguardif.c src/wireguard-platform.c
src/crypto.c)

add_subdirectory("${CRYPTO_DIR}")

target_link_libraries(wg crypto)


target_include_directories(wg PRIVATE ${LWIP_INCLUDE_DIRS})

# target_compile_options(wg PRIVATE ${LWIP_COMPILER_FLAGS})
add_definitions("${GCC_LINK_FLAGS}")

target_compile_definitions(wg PRIVATE ${LWIP_DEFINITIONS})
# set_property(TARGET wg PROPERTY C_STANDARD 11)
# target_compile_features(wg PUBLIC c_std_11)
target_link_libraries(wg ${LWIP_SANITIZER_LIBS} lwipcore lwipallapps lwipcontribportunix)

# add_executable(makefsdata ${lwipmakefsdata_SRCS})
# target_compile_options(makefsdata PRIVATE ${LWIP_COMPILER_FLAGS})
# target_include_directories(makefsdata PRIVATE ${LWIP_INCLUDE_DIRS})
# target_link_libraries(makefsdata ${LWIP_SANITIZER_LIBS})

# cmake_minimum_required(VERSION 3.8)

# project(example_app C)

# set (CMAKE_EXPORT_COMPILE_COMMANDS ON)

# set(LWIP_CONTRIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../..)
# set(LWIP_DIR         ${CMAKE_CURRENT_SOURCE_DIR}/../../../../lwip)

# include(${LWIP_CONTRIB_DIR}/ports/CMakeCommon.cmake)

# set (LWIP_DEFINITIONS -DLWIP_DEBUG)
# set (LWIP_INCLUDE_DIRS
#     "${LWIP_DIR}/src/include"
#     "${LWIP_CONTRIB_DIR}/"
#     "${LWIP_CONTRIB_DIR}/ports/unix/port/include"
#     "${LWIP_CONTRIB_DIR}/examples/example_app"
# )

# include(${LWIP_DIR}/src/Filelists.cmake)
# include(${LWIP_CONTRIB_DIR}/Filelists.cmake)
# include(${LWIP_CONTRIB_DIR}/ports/unix/Filelists.cmake)

# add_executable(example_app ${LWIP_CONTRIB_DIR}/examples/example_app/test.c default_netif.c)
# target_include_directories(example_app PRIVATE ${LWIP_INCLUDE_DIRS})
# target_compile_options(example_app PRIVATE ${LWIP_COMPILER_FLAGS})
# target_compile_definitions(example_app PRIVATE ${LWIP_DEFINITIONS} ${LWIP_MBEDTLS_DEFINITIONS})
# target_link_libraries(example_app ${LWIP_SANITIZER_LIBS} lwipcontribexamples lwipcontribapps lwipcontribaddons lwipallapps lwipcontribportunix lwipcore)

# add_executable(makefsdata ${lwipmakefsdata_SRCS})
# target_compile_options(makefsdata PRIVATE ${LWIP_COMPILER_FLAGS})
# target_include_directories(makefsdata PRIVATE ${LWIP_INCLUDE_DIRS})
# target_link_libraries(makefsdata ${LWIP_SANITIZER_LIBS})