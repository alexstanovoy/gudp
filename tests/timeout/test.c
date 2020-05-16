#include <assert.h>
#include <string.h>
#include <time.h>

#include "client/client.h"
#include "networking/socket.h"
#include "panic.h"
#include "server/server.h"

const char kLocalHost[] = "127.0.0.1";
const int kPort = 51865;
const int kTimeoutTime1 = 1234;
const int kTimeoutTime2 = 123;

Socket sock;
Server srv;
Client clt;
Response resp;
Address addr;
struct timeval t1, t2;
double elapsed_time;

void SetTimer() {
  gettimeofday(&t1, NULL);
}

double GetTimer() {
  gettimeofday(&t2, NULL);
  elapsed_time = (t2.tv_sec - t1.tv_sec) * 1000.0;
  elapsed_time += (t2.tv_usec - t1.tv_usec) / 1000.0;
  printf("%lf\n", elapsed_time);
  fflush(stdout);
  return elapsed_time;
}

int main() {
  ResponseInit(&resp);

  Panic(SocketInit(&sock));
  Panic(SocketSetTimeout(&sock, kTimeoutTime1));
  SetTimer();
  assert(SocketReceive(&sock, &resp.data, NULL) == SOCKET_TIMEOUT);
  assert(GetTimer() >= kTimeoutTime1);
  SocketDestroy(&sock);

#ifdef __IPV4__
  Panic(AddressInit(&addr, kLocalHost, kPort));
#else
#error "Unsupported netcode"
#endif

  Panic(ServerInit(&srv, &addr));
  Panic(ServerSetTimeout(&srv, kTimeoutTime2));
  SetTimer();
  assert(ServerReceive(&srv, &resp) == SOCKET_TIMEOUT);
  assert(GetTimer() >= kTimeoutTime2);
  ServerDestroy(&srv);

  Panic(ClientInit(&clt, &addr));
  Panic(ClientSetTimeout(&clt, kTimeoutTime2));
  SetTimer();
  assert(ClientReceive(&clt, &resp) == SOCKET_TIMEOUT);
  assert(GetTimer() >= kTimeoutTime2);
  ClientDestroy(&clt);

  AddressDestroy(&addr);
  ResponseDestroy(&resp);
}
