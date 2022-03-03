# Build with cmake 
 - cmake .
 - cmake --build .

# Run 
 - sudo ./echop -g 172.18.18.1 -i 172.18.18.18 -m 255.255.0.0

# Current problems
 - segfault in chacha20poly1305.c on line 146 in chacha20() func
 - Place where called: device->public_key in wireguard.c (line 799) is out array in chacha20() func
 - seems like the out[] array is not in available pool of memory for program
 - Debug info before call: Address of out: 0x7fff83a03628, in: 0x21a566a000000010, output: 0x7fff83a03340,  len is 32
 - Seems like the address of public key array is a problem
