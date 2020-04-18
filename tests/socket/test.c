#include <assert.h>
#include <string.h>

#include "networking/packet.h"
#include "networking/socket.h"
#include "panic.h"

const char kLocalHost[] = "127.0.0.1";
const char kTestPacket[] = "hello world!";
const char kTrashPacket[] = "298746019324782";
const int kPort = 44752;
const int kTimeoutTime = 1000;

Socket sock1;
Socket sock2;
Address addr;
Data data;

int main() {
  Panic(SocketInit(&sock1));
  Panic(SocketInit(&sock2));
#ifdef __IPV4__
  Panic(AddressInit(&addr, kLocalHost, kPort));
#else
#error "Unsupported netcode"
#endif
  Panic(DataInit(&data));

  Panic(SocketBind(&sock1, &addr));
  Panic(SocketSetTimeout(&sock1, kTimeoutTime));

  DataSet(&data, kTestPacket);
  Panic(SocketSend(&sock2, &data, &addr));
  DataSet(&data, kTrashPacket);
  Panic(SocketReceive(&sock1, &data, NULL));
  assert(strncmp(data.ptr, kTestPacket, strlen(kTestPacket)) == 0);

  Panic(SocketConnect(&sock2, &addr));
  DataSet(&data, kTestPacket);
  Panic(SocketSend(&sock2, &data, NULL));
  DataSet(&data, kTrashPacket);
  Panic(SocketReceive(&sock1, &data, NULL));
  assert(strncmp(data.ptr, kTestPacket, strlen(kTestPacket)) == 0);

  SocketDestroy(&sock1);
  SocketDestroy(&sock2);
  AddressDestroy(&addr);
  DataDestroy(&data);
}
