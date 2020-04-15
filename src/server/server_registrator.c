#include <stdlib.h>
#include <string.h>

#include "common/macro.h"
#include "common/retcode.h"
#include "networking/socket.h"
#include "server/server.h"
#include "server/server_struct.h"

RETCODE
ConnectedClientInit(ConnectedClient* client) {
  THROW_OR_CONTINUE(AddressInit(&client->addr));
  client->exist = 1;
  return SUCCESS;
}

void ConnectedClientDestroy(ConnectedClient* client) {
  AddressDestroy(&client->addr);
  client->exist = 0;
}

RETCODE
ServerRegistratorInit(Server* srv) {
  srv->clients = malloc(kBaseClients * sizeof(ConnectedClient));
  if (srv->clients == NULL) {
    return NOT_ENOUGH_MEMORY;
  }
  return SUCCESS;
}

void ServerRegistratorDestroy(Server* srv) {
  free(srv->clients);
}

RETCODE
ServerRegistratorIsUserExist(Server* srv, Address* addr,
                             ConnectedClient** client) {
  for (uint16_t id = 0; id < kBaseClients; ++id) {
    if (srv->clients[id].exist &&
        memcmp(&srv->clients[id].addr, addr, sizeof(Address)) == 0) {
      *client = &srv->clients[id];
      return SUCCESS;
    }
  }
  return SERVER_USER_NOT_FOUND;
}

RETCODE
ServerRegistratorGetUserByID(Server* srv, uint16_t client_id,
                             ConnectedClient** client) {
  if (srv->clients[client_id].exist) {
    *client = &srv->clients[client_id];
    return SUCCESS;
  }
  return SERVER_USER_NOT_FOUND;
}

RETCODE
ServerRegistratorAddUser(Server* srv, Address* addr, ConnectedClient** client) {
  for (uint16_t id = 0; id < kBaseClients; ++id) {
    if (!srv->clients[id].exist) {
      THROW_OR_CONTINUE(ConnectedClientInit(&srv->clients[id]));
      memcpy(&srv->clients[id].addr, addr, sizeof(Address));
      *client = &srv->clients[id];
      return SUCCESS;
    }
  }
  return SERVER_CROWDED;
}

void ServerRegistratorRemoveUser(Server* srv, Address* addr) {
  for (uint16_t id = 0; id < kBaseClients; ++id) {
    if (memcmp(&srv->clients[id].addr, addr, sizeof(Address)) == 0) {
      ConnectedClientDestroy(&srv->clients[id]);
      break;
    }
  }
}
