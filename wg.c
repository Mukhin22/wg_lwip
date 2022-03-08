#include "wg.h"

err_t wireguard_setup(const struct wg_init_data init_data, struct netif *wg_netif) {
  err_t err = ERR_OK;
  struct netif wg_netif_struct = {0};
  // static struct netif *wg_netif = NULL;
  uint8_t wg_peer_index = WIREGUARDIF_INVALID_INDEX;
  struct wireguardif_init_data wg;
  struct wireguardif_peer peer;
  ip_addr_t ipaddr;
  ip_addr_t netmask;
  ip_addr_t gateway;
  // ip_addr_t ipaddr = init_data.ip;
  IP4_ADDR(&ipaddr, 192, 168, 40, 10);
  // ip_addr_t netmask = init_data.netmask;
  IP4_ADDR(&netmask, 255, 255, 255, 0);
  // ip_addr_t gateway = init_data.gateway;
  IP4_ADDR(&gateway, 192, 168, 40, 1);

  // Setup the WireGuard device structure
  wg.private_key = "8BU1giso23adjCk93dnpLJnK788bRAtpZxs8d+Jo+Vg=";
  wg.listen_port = 51820;
  wg.bind_netif = NULL;

  // Register the new WireGuard network interface with lwIP
  wg_netif = netif_add(&wg_netif_struct, &ipaddr, &netmask, &gateway, &wg,
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
  peer.public_key = "cDfetaDFWnbxts2Pbz4vFYreikPEEVhTlV/sniIEBjo=";
  peer.preshared_key = NULL;
  // Allow all IPs through tunnel
  IP4_ADDR(&peer.allowed_ip, 0, 0, 0, 0);
  IP4_ADDR(&peer.allowed_mask, 0, 0, 0, 0);

  // If we know the endpoint's address can add here
  IP4_ADDR(&peer.endpoint_ip, 10, 0, 0, 12);
  peer.endport_port = 12345;

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

// int main(void) {
//   err_t err; 
//   mem_init();
//   err = wireguard_setup();
//   LWIP_ERROR("wireguard_setup failed\n", err == ERR_OK, return ERR_ABRT);
//   return 0;
// }