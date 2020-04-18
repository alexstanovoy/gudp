#include <assert.h>

#include "client/client.h"
#include "networking/packet.h"
#include "panic.h"
#include "server/server.h"

const char kLocalHost[] = "127.0.0.1";
const char kTestPacket[] = "hello world!";
const char kTrashPacket[] = "298746019324782";
const int kPort = 22807;
const int kTimeoutTime = 1000;

Address addr;
Server srv;
Client clt1;
Client clt2;
Response response;

int main() {
#ifdef __IPV4__
  Panic(AddressInit(&addr, kLocalHost, kPort));
#else
#error "Unsupported netcode"
#endif

  Panic(ServerInit(&srv, &addr));
  Panic(ClientInit(&clt1, &addr));
  Panic(ClientInit(&clt2, &addr));
  Panic(ResponseInit(&response));

  Panic(ServerSetTimeout(&srv, kTimeoutTime));
  Panic(ClientSetTimeout(&clt1, kTimeoutTime));
  Panic(ClientSetTimeout(&clt2, kTimeoutTime));

  ResponseSetData(&response, kTestPacket);
  Panic(ClientSend(&clt1, &response));
  ResponseSetData(&response, kTrashPacket);
  Panic(ServerReceive(&srv, &response));
  assert(strncmp(response.data.ptr, kTestPacket, strlen(kTestPacket)) == 0);
  assert(response.client_id == 0);

  ResponseSetData(&response, kTestPacket);
  Panic(ClientSend(&clt2, &response));
  ResponseSetData(&response, kTrashPacket);
  Panic(ServerReceive(&srv, &response));
  assert(strncmp(response.data.ptr, kTestPacket, strlen(kTestPacket)) == 0);
  assert(response.client_id == 1);

  ResponseSetData(&response, kTestPacket);
  Panic(ClientSend(&clt1, &response));
  ResponseSetData(&response, kTrashPacket);
  Panic(ServerReceive(&srv, &response));
  assert(strncmp(response.data.ptr, kTestPacket, strlen(kTestPacket)) == 0);
  assert(response.client_id == 0);

  ResponseSetData(&response, kTestPacket);
  Panic(ClientSend(&clt2, &response));
  ResponseSetData(&response, kTrashPacket);
  Panic(ServerReceive(&srv, &response));
  assert(strncmp(response.data.ptr, kTestPacket, strlen(kTestPacket)) == 0);
  assert(response.client_id == 1);

  ResponseSetData(&response, kTestPacket);
  Panic(ServerSend(&srv, &response));
  ResponseSetData(&response, kTrashPacket);
  Panic(ClientReceive(&clt1, &response));
  assert(strncmp(response.data.ptr, kTestPacket, strlen(kTestPacket)) == 0);
  ResponseSetData(&response, kTrashPacket);
  Panic(ClientReceive(&clt2, &response));
  assert(strncmp(response.data.ptr, kTestPacket, strlen(kTestPacket)) == 0);

  ServerDestroy(&srv);
  ClientDestroy(&clt1);
  ClientDestroy(&clt2);
  AddressDestroy(&addr);
  ResponseDestroy(&response);
}
