#include <stdlib.h>

#include "server/server.h"
#include "common/retcode.h"
#include "server/server_handler.h"

RETCODE
ServerInit(Server* srv) {
  srv->clients = malloc(kBaseClients * sizeof(ConnectedClient));
  if (srv->clients == NULL) {
    return NOT_ENOUGH_MEMORY;
  }
  RETCODE result = SocketInit(&srv->socket);
  if (result != SUCCESS) {
    free(srv->clients);
    srv->clients = NULL;
    return result;
  }
  srv->clients_count = 0;
  return SUCCESS;
}

void ServerDestroy(Server* srv) {
  // Send disconnect packet?
  free(srv->clients);
  SocketDestroy(&srv->socket);
}
