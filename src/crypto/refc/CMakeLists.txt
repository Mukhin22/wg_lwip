cmake_minimum_required(VERSION 3.8)

add_library(crypto STATIC blake2s.c chacha20.c chacha20poly1305.c poly1305-donna.c x25519.c)
