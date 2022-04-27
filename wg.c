#include "wg.h"



err_t wireguard_setup(const struct wg_init_data init_data, struct netif *wg_netif)
{
  err_t err = ERR_OK;
  uint8_t wg_peer_index = WIREGUARDIF_INVALID_INDEX;
  struct wireguardif_init_data wg;
  struct wireguardif_peer peer;
  ip_addr_t ipaddr = init_data.ip;
  ip_addr_t netmask = init_data.netmask;
  ip_addr_t gateway = init_data.gateway;

  // Setup the WireGuard device structure
  if (!init_data.private_key) {  
    wg.private_key = "ONj6Iefel47uMKtWRCSMLan2UC5eW3Fj9Gsy9bqcyEc=";
  } else {
    wg.private_key = init_data.private_key;
  }
  wg.listen_port = 5555;//51820;
  wg.bind_netif = NULL;

  // Register the new WireGuard network interface with lwIP
  netif_add(wg_netif, &ipaddr, &netmask, &gateway, &wg,
                       &wireguardif_init, &ip_input);
  if (!wg_netif) {
    fprintf(stderr, "netif_add failed\n");
    return ERR_MEM;
  }
  // Mark the interface as administratively up, link up flag is set
  // automatically when peer connects
  netif_set_up(wg_netif);

  // Initialise the first WireGuard peer structure
  wireguardif_peer_init(&peer);
  if (!init_data.peer_public_key) {
    peer.public_key = "B3AiK5DLMgprKx2SH/DbCmxyBzKTMKhv1mkpH+5STXI="; // public key of 2nd aws server
  } else {
    peer.public_key = init_data.peer_public_key;
  }
  peer.preshared_key = NULL;

  // Allow all IPs through tunnel
  IP4_ADDR(&peer.allowed_ip, 0, 0, 0, 0);
  IP4_ADDR(&peer.allowed_mask, 0, 0, 0, 0);

  // If we know the endpoint's address can add here
  if (!init_data.peer_ip.addr) {
  // IP4_ADDR(&peer.endpoint_ip, 16, 171, 45, 144);
    IP4_ADDR(&peer.endpoint_ip, 10, 0, 0, 2);
  } else {
    peer.endpoint_ip.addr = init_data.peer_ip.addr;
  }

  peer.endport_port = 5555;

  // Register the new WireGuard peer with the netwok interface
  err = wireguardif_add_peer(wg_netif, &peer, &wg_peer_index);
  LWIP_ERROR("wireguardif_add_peer failed\n", err == ERR_OK, return ERR_ABRT);

  if ((wg_peer_index != WIREGUARDIF_INVALID_INDEX) &&
      !ip_addr_isany(&peer.endpoint_ip)) {
    // Start outbound connection to peer
    err = wireguardif_connect(wg_netif, wg_peer_index);
    LWIP_ERROR("wireguardif_connect failed\n", err == ERR_OK, return ERR_ABRT);
  }

  return err;
}