#include "common/macro.h"
#include "common/retcode.h"
#include "networking/packet.h"
#include "networking/socket.h"
#include "server/server.h"
#include "server/server_registrator.h"
#include "server/server_struct.h"

RETCODE
ServerHandlerReceive(Server* srv, Response* response) {
  RAII(DataDestroy) Data data;
  THROW_OR_CONTINUE(DataInit(&data));
  RAII(AddressDestroy) Address addr;
  THROW_OR_CONTINUE(AddressInit(&addr));
  THROW_OR_CONTINUE(SocketReceive(&srv->socket, &data, &addr));
  THROW_OR_CONTINUE(GetResponseFromData(&data, response));
  uint16_t client_id;
  THROW_OR_CONTINUE(ServerRegistratorGetUserId(srv, &addr, &client_id));
  response->client_id = client_id;
  return SUCCESS;
}

RETCODE
ServerHandlerSendTo(Server* srv, Response* response) {
  RAII(DataDestroy) Data data;
  THROW_OR_CONTINUE(DataInit(&data));
  THROW_OR_CONTINUE(GetDataFromResponse(response, &data));
  ConnectedClient* client;
  THROW_OR_CONTINUE(
      ServerRegistratorGetUser(srv, response->client_id, &client));
  THROW_OR_CONTINUE(SocketSend(&srv->socket, &data, &client->addr))
  return SUCCESS;
}

// Bad implementation: response can be changed
RETCODE
ServerHandlerSend(Server* srv, Response* response) {
  for (uint16_t id = 0; id < kBaseClients; ++id) {
    if (ServerRegistratorFindUser(srv, id)) {
      response->client_id = id;
      THROW_OR_CONTINUE(ServerHandlerSendTo(srv, response));
    }
  }
  return SUCCESS;
}
