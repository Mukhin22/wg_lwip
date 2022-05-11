# Build with cmake 

```
 cmake .
 cmake --build .
```

# Run 

```
sudo ./echop -g 10.0.0.0 -i 10.0.0.10 -m 255.255.255.0
            -a 10.0.0.11 -s ONj6Iefel47uMKtWRCSMLan2UC5eW3Fj9Gsy9bqcyEc=
            -p Cme9E2nbgTgkDUa+oS5fbqF9HC7KTRgnw8zLvwRp9z4=
```

# Connecting linux wireguard(wg0) and echop application

## Launch parameters for echop
 - NOTE: -p parameter - public key of the wg0 interface
 - NOTE: -s parameter - private key that will be assigned to wireguard interface of echop application
 - NOTE: -a parameter - peer address for echop application - in our case is vpn address of linux wg0 interface
 - NOTE: -g parameter - gateway address for wireguard of echop
 - NOTE: -i parameter - ip address for wireguard of echop
 - NOTE: -m parameter - network mask for wireguard of echop
 - NOTE: by default tap0 interface created in echop use such configuration:

  1. gateway address -  192.168.1.1
  2. ip address - 192.168.1.20
  3. netmask - 255.255.255.0

### Command to start from console

```
  sudo ./echop -g 10.0.0.0 -i 10.0.0.10 -m 255.255.255.0
            -a 10.0.0.11 -s ONj6Iefel47uMKtWRCSMLan2UC5eW3Fj9Gsy9bqcyEc=
            -p Cme9E2nbgTgkDUa+oS5fbqF9HC7KTRgnw8zLvwRp9z4=
```

### Launch.json "args" field for running in VSCode

```
            "args": ["-g", "10.0.0.0", "-i", "10.0.0.10", "-m", "255.255.255.0",
            "-a", "10.0.0.11", "-s", "ONj6Iefel47uMKtWRCSMLan2UC5eW3Fj9Gsy9bqcyEc=",
            "-p", "Cme9E2nbgTgkDUa+oS5fbqF9HC7KTRgnw8zLvwRp9z4="],
```
## Linux wireguard wg0.conf file content example

```
[Interface]
Address = 10.0.0.11/24
SaveConfig = true
ListenPort = 5555
PrivateKey = gO4EqJS2djMy4eE+clsVNlhZap9DUJH0k3Ny0NlZ0Wk=

[Peer]
PublicKey = u5EZtNSLFtXFfZZgb4gVdahERLXCOdmmupDBSvWgD04=
AllowedIPs = 10.0.0.10/32, 10.0.0.0/32
```
## Modification for running on different linux machine
- address of the peer parameter(-a) - has to be the same as in wg0.conf of your machine
- public key of the peer parameter(-p) - has to be same as in your wg0 interface could be known by using command:

```
sudo cat /etc/wireguard/publickey
```

# Attempt to connect two echop devices within the same LAN (no success yet)

This parameters could be set with command line arguments of application

 ## First peer

 - first peer private key: "ONj6Iefel47uMKtWRCSMLan2UC5eW3Fj9Gsy9bqcyEc="
 - first peer public key:  "+t97oimvjgG7Qahd9wNv5j1yH9Bve2/FxAEECEzLt1g="
 - ip_addr(tun/tap): 10.0.0.10
 - launch.json file argument for vscode are:

```
             "args": ["-g", "10.0.0.0", "-i", "10.0.0.10", "-m", "255.255.255.0",
            "-a", "10.0.0.11", "-s", "ONj6Iefel47uMKtWRCSMLan2UC5eW3Fj9Gsy9bqcyEc=",
            "-p", "wCRAsj6Yn0gXvEJW7rNsatSTzyC5CP6nbrNsMxDuVwU="],
```

 ## Seconds peer

 - second peer private key: "SFMJ5Qo0pzZOMfogNGqqq2bUkYlAVZ+es9TV8WDhiWc="
 - second peer public key: "wCRAsj6Yn0gXvEJW7rNsatSTzyC5CP6nbrNsMxDuVwU="
 - ip_addr(tun/tap): 10.0.0.11
 - launch.json file argument for vscode are:
 
```
             "args": ["-g", "10.0.0.0", "-i", "10.0.0.11", "-m", "255.255.255.0",
            "-a", "10.0.0.10", "-s", "SFMJ5Qo0pzZOMfogNGqqq2bUkYlAVZ+es9TV8WDhiWc=",
            "-p", "+t97oimvjgG7Qahd9wNv5j1yH9Bve2/FxAEECEzLt1g="],
```

## Command to start in console

### First peer

```
 sudo ./echop -g 10.0.0.0 -i 10.0.0.10 -m 255.255.255.0 -a 10.0.0.11 -s ONj6Iefel47uMKtWRCSMLan2UC5eW3Fj9Gsy9bqcyEc= -p wCRAsj6Yn0gXvEJW7rNsatSTzyC5CP6nbrNsMxDuVwU=
```

### Second peer

```
 sudo ./echop -g 10.0.0.0 -i 10.0.0.11 -m 255.255.255.0 -a 10.0.0.10 -s SFMJ5Qo0pzZOMfogNGqqq2bUkYlAVZ+es9TV8WDhiWc= -p +t97oimvjgG7Qahd9wNv5j1yH9Bve2/FxAEECEzLt1g=
 ```
