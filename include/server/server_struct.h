#pragma once

#include <stdint.h>

#include "networking/socket.h"

/**
 * @brief      Represents one of the connected clients to the server.
 */
typedef struct {
  /// Address of the client.
  Address addr;
} ConnectedClient;

/**
 * @brief      Server structure.
 */
typedef struct {
  /// Server socket.
  Socket socket;
  /// Array of connected clients.
  ConnectedClient** clients;
  /// Clients array size.
  uint16_t clients_count;
} Server;
