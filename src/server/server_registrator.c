#include "common/retcode.h"
#include "networking/socket.h"
#include "server/server.h"
#include "server/server_struct.h"
#include "string.h"

RETCODE
ServerRegistratorFindUser(Server* srv, uint16_t client_id) {
  if (srv->clients[client_id] == NULL) {
    return SERVER_USER_NOT_FOUND;
  }
  return SUCCESS;
}

int ServerRegistratorGetUserId(Server* srv, Address* addr,
                               uint16_t* client_id) {
  for (uint16_t id = 0; id < kBaseClients; ++id) {
    if (memcmp(&srv->clients[id]->addr, addr, sizeof(Address)) == 0) {
      *client_id = id;
      return SUCCESS;
    }
  }
  return SERVER_USER_NOT_FOUND;
}

RETCODE
ServerRegistratorGetUser(Server* srv, uint16_t client_id,
                         ConnectedClient** client) {
  if (srv->clients[client_id] == NULL) {
    return SERVER_USER_NOT_FOUND;
  }
  *client = srv->clients[client_id];
  return SUCCESS;
}
