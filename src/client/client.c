#include "client/client.h"

#include <string.h>

#include "common/macro.h"
#include "common/retcode.h"
#include "networking/packet.h"
#include "networking/socket.h"

RETCODE
ClientInit(Client* client, Address* addr) {
  THROW_OR_CONTINUE(SocketInit(&client->socket));
  RETCODE result = AddressInit(&client->addr, NULL, 0);
  if (result != SUCCESS) {
    SocketDestroy(&client->socket);
    return result;
  }
  AddressCopy(&client->addr, addr);
  result = SocketConnect(&client->socket, &client->addr);
  if (result != SUCCESS) {
    SocketDestroy(&client->socket);
    AddressDestroy(&client->addr);
    return result;
  }
  return SUCCESS;
}

void ClientDestroy(Client* client) {
  SocketDestroy(&client->socket);
  AddressDestroy(&client->addr);
}

RETCODE
ClientReceive(Client* client, Response* response) {
  RAII(DataDestroy) Data data;
  THROW_OR_CONTINUE(DataInit(&data));
  THROW_OR_CONTINUE(SocketReceive(&client->socket, &data, NULL));
  THROW_OR_CONTINUE(DataToResponse(&data, response));
  if (response->type == DISCONNECT) {
    return CLIENT_KICKED;
  }
  return SUCCESS;
}

RETCODE
ClientSend(Client* client, Response* response) {
  RAII(DataDestroy) Data data;
  THROW_OR_CONTINUE(DataInit(&data));
  response->type = CONNECT;
  THROW_OR_CONTINUE(ResponseToData(response, &data));
  THROW_OR_CONTINUE(SocketSend(&client->socket, &data, &client->addr))
  return SUCCESS;
}
