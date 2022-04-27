# Build with cmake 
 - cmake .
 - cmake --build .

# Run 
 - sudo ./echop -g 172.18.18.1 -i 172.18.18.18 -m 255.255.0.0

# Parameters of two wireguard peers connection in LAN

This parameters could be set with command line arguments of application

 ## first peer

 - first peer private key: "ONj6Iefel47uMKtWRCSMLan2UC5eW3Fj9Gsy9bqcyEc="
 - first peer public key:  "+t97oimvjgG7Qahd9wNv5j1yH9Bve2/FxAEECEzLt1g="
 - ip_addr(tun/tap): 10.0.0.10
 - launch.json file argument for vscode are:
             "args": ["-g", "10.0.0.0", "-i", "10.0.0.10", "-m", "255.255.255.0",
            "-a", "10.0.0.11", "-s", "ONj6Iefel47uMKtWRCSMLan2UC5eW3Fj9Gsy9bqcyEc=",
            "-p", "wCRAsj6Yn0gXvEJW7rNsatSTzyC5CP6nbrNsMxDuVwU="],
 ## seconds peer

 - second peer private key: "SFMJ5Qo0pzZOMfogNGqqq2bUkYlAVZ+es9TV8WDhiWc="
 - second peer public key: "wCRAsj6Yn0gXvEJW7rNsatSTzyC5CP6nbrNsMxDuVwU="
 - ip_addr(tun/tap): 10.0.0.11
 - launch.json file argument for vscode are:
             "args": ["-g", "10.0.0.0", "-i", "10.0.0.11", "-m", "255.255.255.0",
            "-a", "10.0.0.10", "-s", "SFMJ5Qo0pzZOMfogNGqqq2bUkYlAVZ+es9TV8WDhiWc=",
            "-p", "+t97oimvjgG7Qahd9wNv5j1yH9Bve2/FxAEECEzLt1g="],

# Command to start in console

## first peer

- sudo ./echop -g 10.0.0.0 -i 10.0.0.10 -m 255.255.255.0 -a 10.0.0.11 -s ONj6Iefel47uMKtWRCSMLan2UC5eW3Fj9Gsy9bqcyEc= -p wCRAsj6Yn0gXvEJW7rNsatSTzyC5CP6nbrNsMxDuVwU=

## second peer

- sudo ./echop -g 10.0.0.0 -i 10.0.0.11 -m 255.255.255.0 -a 10.0.0.10 -s SFMJ5Qo0pzZOMfogNGqqq2bUkYlAVZ+es9TV8WDhiWc= -p +t97oimvjgG7Qahd9wNv5j1yH9Bve2/FxAEECEzLt1g=