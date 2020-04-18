#pragma once

#include <stdint.h>

#include "networking/packet.h"
#include "networking/socket.h"

typedef struct {
  Socket socket;
  Address addr;
} Client;

RETCODE
ClientInit(Client* client, Address* addr);

void ClientDestroy(Client* client);

RETCODE
ClientReceive(Client* client, Response* response);

RETCODE
ClientSend(Client* client, Response* response);

RETCODE
ClientSetTimeout(Client* clt, time_t milliseconds);
