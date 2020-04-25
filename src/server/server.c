#include "server/server.h"

#include <stdlib.h>

#include "common/macro.h"
#include "common/retcode.h"
#include "server/registrator.h"

RETCODE
ServerInit(Server* srv, Address* addr) {
  THROW_OR_CONTINUE(RegistratorInit(&srv->registrator));
  RETCODE result = SocketInit(&srv->socket);
  if (result != SUCCESS) {
    RegistratorDestroy(&srv->registrator);
    return result;
  }
  result = SocketBind(&srv->socket, addr);
  if (result != SUCCESS) {
    SocketDestroy(&srv->socket);
    RegistratorDestroy(&srv->registrator);
    return result;
  }
  return SUCCESS;
}

void ServerDestroy(Server* srv) {
  // Send disconnect packet?
  RegistratorDestroy(&srv->registrator);
  SocketDestroy(&srv->socket);
}

static RETCODE ServerRAWReceive(Server* srv, Response* response,
                                Address* addr) {
  RAII(DataDestroy) Data data;
  THROW_OR_CONTINUE(DataInit(&data));
  THROW_OR_CONTINUE(SocketReceive(&srv->socket, &data, addr));
  THROW_OR_CONTINUE(DataToResponse(&data, response));
  return SUCCESS;
}

RETCODE
ServerReceive(Server* srv, Response* response) {
  RAII(AddressDestroy) Address addr;
  THROW_OR_CONTINUE(AddressInit(&addr, NULL, 0));
  THROW_OR_CONTINUE(ServerRAWReceive(srv, response, &addr));
  switch (ResponseGetType(response)) {
    case CONNECT: {
      ConnectedClient* client;
      if (RegistratorGetUserByAddress(&srv->registrator, &addr, &client) !=
          SUCCESS) {
        THROW_OR_CONTINUE(
            RegistratorAddUser(&srv->registrator, &addr, &client));
      }
      ResponseSetClientId(response, client->client_id);
      break;
    }
    case DISCONNECT: {
      ConnectedClient* client;
      if (RegistratorGetUserByAddress(&srv->registrator, &addr, &client) ==
          SUCCESS) {
        RegistratorRemoveUserByAddress(&srv->registrator, &client->addr);
      }
      break;
    }
  }
  return SUCCESS;
}

RETCODE
ServerSendTo(Server* srv, Response* response) {
  RAII(DataDestroy) Data data;
  THROW_OR_CONTINUE(DataInit(&data));
  THROW_OR_CONTINUE(ResponseToData(response, &data));
  ConnectedClient* client;
  THROW_OR_CONTINUE(
      RegistratorGetUserByID(&srv->registrator, response->client_id, &client));
  THROW_OR_CONTINUE(SocketSend(&srv->socket, &data, &client->addr))
  return SUCCESS;
}

RETCODE
ServerSend(Server* srv, Response* response) {
  RAII(RegistratorIterDestroy) RegistratorIter iter;
  THROW_OR_CONTINUE(RegistratorIterInit(&srv->registrator, &iter));
  while (!RegistratorIterStopped(&srv->registrator, &iter)) {
    response->client_id =
        RegistratorIterDereference(&srv->registrator, &iter)->client_id;
    THROW_OR_CONTINUE(ServerSendTo(srv, response));
    RegistratorIterNext(&srv->registrator, &iter);
  }
  return SUCCESS;
}

RETCODE
ServerSetTimeout(Server* srv, time_t milliseconds) {
  THROW_OR_CONTINUE(SocketSetTimeout(&srv->socket, milliseconds));
  return SUCCESS;
}

RETCODE
ServerMakeNonBlocking(Server* server) {
  THROW_OR_CONTINUE(ServerMakeNonBlocking(&server->socket));
  return SUCCESS;
}
