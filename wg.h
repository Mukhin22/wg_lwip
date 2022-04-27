#ifndef _WG_H_
#define _WG_H_

#include <netdb.h>
#include <netinet/in.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <lwip/mem.h>

#include "wireguard.h"
#include "wireguardif.h"

/* Wireguard setup netif parameters*/
struct wg_init_data {
  ip_addr_t ip;
  ip_addr_t netmask;
  ip_addr_t gateway;
  const char *private_key;
  /* Peer connection data*/
  ip_addr_t peer_ip;
  const char *peer_public_key;
};

/* Wireguard setup function called with parameters struct*/
err_t wireguard_setup(const struct wg_init_data init_data, struct netif *wg_netif);

#endif /* _WG_H_ */