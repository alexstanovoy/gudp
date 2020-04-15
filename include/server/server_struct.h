#pragma once

#include <stdint.h>

#include "networking/socket.h"

typedef struct {
  int exist;
  uint16_t client_id;
  Address addr;
} ConnectedClient;

typedef struct {
  Socket socket;
  ConnectedClient* clients;
} Server;
