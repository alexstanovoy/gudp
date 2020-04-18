#include "server/server.h"

#include <stdlib.h>

#include "common/macro.h"
#include "common/retcode.h"
#include "server/server_registrator.h"

RETCODE
ServerInit(Server* srv, Address* addr) {
  THROW_OR_CONTINUE(ServerRegistratorInit(srv));
  RETCODE result = SocketInit(&srv->socket);
  if (result != SUCCESS) {
    ServerRegistratorDestroy(srv);
    return result;
  }
  result = SocketBind(&srv->socket, addr);
  if (result != SUCCESS) {
    SocketDestroy(&srv->socket);
    ServerRegistratorDestroy(srv);
    return result;
  }
  return SUCCESS;
}

void ServerDestroy(Server* srv) {
  // Send disconnect packet?
  ServerRegistratorDestroy(srv);
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
      if (ServerRegistratorGetUserByAddress(srv, &addr, &client) != SUCCESS) {
        THROW_OR_CONTINUE(ServerRegistratorAddUser(srv, &addr, &client));
      }
      ResponseSetClientId(response, client->client_id);
      break;
    }
    case DISCONNECT: {
      ConnectedClient* client;
      if (ServerRegistratorGetUserByAddress(srv, &addr, &client) == SUCCESS) {
        ServerRegistratorRemoveUserByAddress(srv, &client->addr);
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
      ServerRegistratorGetUserByID(srv, response->client_id, &client));
  THROW_OR_CONTINUE(SocketSend(&srv->socket, &data, &client->addr))
  return SUCCESS;
}

RETCODE
ServerSend(Server* srv, Response* response) {
  uint16_t old_client_id = response->client_id;
  for (uint16_t id = 0; id < kBaseClients; ++id) {
    if (srv->clients[id].exist) {
      response->client_id = id;
      RETCODE result = ServerSendTo(srv, response);
      if (result != SUCCESS) {
        response->client_id = old_client_id;
        return result;
      }
    }
  }
  response->client_id = old_client_id;
  return SUCCESS;
}

RETCODE
ServerSetTimeout(Server* srv, time_t milliseconds) {
  THROW_OR_CONTINUE(SocketSetTimeout(&srv->socket, milliseconds));
  return SUCCESS;
}
