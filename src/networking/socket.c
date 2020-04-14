#include "networking/socket.h"

#include <errno.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include "common/retcode.h"

static const int kSocketDomain = AF_INET;
static const int kSocketType = SOCK_DGRAM;
static const int kSocketProtocol = 0;

RETCODE
SocketsInit() {
  return SUCCESS;
}

RETCODE
SocketsShutdown() {
  return SUCCESS;
}

RETCODE
SocketInit(Socket* sock) {
  sock->socket_fd = socket(kSocketDomain, kSocketType, kSocketProtocol);
  if (sock->socket_fd < 0) {
    return SOCKET_INIT_FAILED;
  }
  return SUCCESS;
}

void SocketDestroy(Socket* sock) {
  if (sock->socket_fd != -1) {
    close(sock->socket_fd);
  }
}

static inline void AddressToSockaddrIn(struct sockaddr_in* result,
                                       Address* addr) {
  *result = (struct sockaddr_in){.sin_family = kSocketDomain,
                                 .sin_addr = htonl(addr->ip),
                                 .sin_port = htons(addr->port)};
}

RETCODE
SocketBind(Socket* sock, Address* addr) {
  struct sockaddr_in bind_addr;
  AddressToSockaddrIn(&bind_addr, addr);
  if (bind(sock->socket_fd, (const struct sockaddr*)&bind_addr,
           sizeof(struct sockaddr_in)) < 0) {
    return SOCKET_BIND_FAILED;
  }
  return SUCCESS;
}

RETCODE
SocketConnect(Socket* sock, Address* addr) {
  struct sockaddr_in connect_addr;
  AddressToSockaddrIn(&connect_addr, addr);
  if (connect(sock->socket_fd, (const struct sockaddr*)&connect_addr,
              sizeof(struct sockaddr_in)) < 0) {
    return SOCKET_CONNECT_FAILED;
  }
  return SUCCESS;
}

RETCODE
SocketSend(Socket* sock, Data* data, Address* addr) {
  if (addr == NULL) {
    if (send(sock->socket_fd, data->ptr, data->len, 0) < 0) {
      return SOCKET_SEND_FAILED;
    }
    return SUCCESS;
  }
  struct sockaddr_in client_addr;
  AddressToSockaddrIn(&client_addr, addr);
  if (sendto(sock->socket_fd, data->ptr, data->len, 0,
             (const struct sockaddr*)&client_addr,
             sizeof(struct sockaddr_in)) < 0) {
    return SOCKET_SEND_FAILED;
  }
  return SUCCESS;
}

RETCODE
SocketReceive(Socket* sock, Data* buffer, Address* addr) {
  if (addr == NULL) {
    if (recv(sock->socket_fd, buffer->ptr, buffer->len, 0) < 0) {
      return SOCKET_RECEIVE_FAILED;
    }
    return SUCCESS;
  }
  struct sockaddr_storage seed;
  if (recvfrom(sock->socket_fd, buffer->ptr, buffer->len, 0,
               (const struct sockaddr*)&seed,
               sizeof(struct sockaddr_storage)) < 0) {
    return SOCKET_RECEIVE_FAILED;
  }
  // ???
  /*
    memcpy (&ret->addr.sin_addr, &((struct sockaddr_in *) native)->sin_addr,
    sizeof (struct in_addr)); ret->family = P_SOCKET_FAMILY_INET; ret->port   =
    p_ntohs (((struct sockaddr_in *) native)->sin_port);
  */
  memcpy(&addr->ip, &((struct sockaddr_in*)&seed)->sin_addr, sizeof(addr->ip));
  addr->port = ntohs(((struct sockaddr_in*)&seed)->sin_port);
  // ???
  return SUCCESS;
}
