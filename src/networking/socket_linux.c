#include <errno.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include "common/retcode.h"
#include "networking/socket.h"

typedef struct gudp_socket_t {
  int socket_fd;
} Socket;

typedef struct gudp_address_t {
  uint32_t ip;
  uint16_t port;
} Address;

typedef enum gudp_socket_flags {
  SOCKET_NONBLOCKING = MSG_DONTWAIT,
} FLAG;

RETCODE
SocketsInit() {
  return SUCCESS;
}

RETCODE
SocketsShutdown() {
  return SUCCESS;
}

RETCODE
SocketCreate(Socket* sock) {
  sock->socket_fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
  if (sock->socket_fd < 0) {
    return SOCKET_CREATION_FAILED;
  }
  return SUCCESS;
}

RETCODE
SocketClose(Socket* sock) {
  if (close(sock->socket_fd) < 0) {
    return SOCKET_CLOSING_FAILED;
  }
  return SUCCESS;
}

RETCODE
SocketBind(Socket* sock, Address* addr) {
  struct sockaddr_in server_sockaddr = {.sin_family = AF_INET,
                                        .sin_addr = htonl(addr->ip),
                                        .sin_port = htons(addr->port)};
  if (bind(sock->socket_fd, (const struct sockaddr*)&server_sockaddr,
           sizeof(struct sockaddr_in)) < 0) {
    return SOCKET_BIND_FAILED;
  }
  return SUCCESS;
}

RETCODE
SocketConnect(Socket* sock, Address* addr) {
  struct sockaddr_in server_sockaddr = {.sin_family = AF_INET,
                                        .sin_addr = htonl(addr->ip),
                                        .sin_port = htons(addr->port)};
  if (connect(sock->socket_fd, (const struct sockaddr*)&server_sockaddr,
              sizeof(struct sockaddr_in)) < 0) {
    return SOCKET_CONNECT_FAILED;
  }
  return SUCCESS;
}

RETCODE
SocketSendTo(Socket* sock, Data* data, Address* addr, int flags) {
}

RETCODE
SocketSend(Socket* sock, Data* data, int flags) {
}

RETCODE
SocketReceiveFrom(Socket* sock, Data* data, Address* addr, int flags) {
}

RETCODE
SocketReceive(Socket* sock, Data* data, int flags) {
}
