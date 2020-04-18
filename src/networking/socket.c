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

#ifdef __IPV4__
RETCODE
AddressInit(Address* addr, const char* ip, uint16_t port) {
  if (ip != NULL) {
    addr->ip = inet_addr(ip);
  }
  addr->port = htons(port);
  return SUCCESS;
}

void AddressDestroy(Address* addr) {
}

void AddressCopy(Address* dest, Address* src) {
  memcpy(dest, src, sizeof(Address));
}
#else
#error "Unsupported type of netcode"
#endif

RETCODE
SocketsStartup() {
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
    return SOCKET_INIT;
  }
  return SUCCESS;
}

void SocketDestroy(Socket* sock) {
  if (sock->socket_fd != -1) {
    close(sock->socket_fd);
  }
}

static void AddressToSockaddrIn(struct sockaddr_in* result, Address* addr) {
  *result = (struct sockaddr_in){.sin_family = kSocketDomain,
                                 .sin_addr = addr->ip,
                                 .sin_port = addr->port};
}

RETCODE
SocketBind(Socket* sock, Address* addr) {
  struct sockaddr_in bind_addr;
  AddressToSockaddrIn(&bind_addr, addr);
  if (bind(sock->socket_fd, (const struct sockaddr*)&bind_addr,
           sizeof(struct sockaddr_in)) < 0) {
    return SOCKET_BIND;
  }
  return SUCCESS;
}

RETCODE
SocketConnect(Socket* sock, Address* addr) {
  struct sockaddr_in connect_addr;
  AddressToSockaddrIn(&connect_addr, addr);
  if (connect(sock->socket_fd, (const struct sockaddr*)&connect_addr,
              sizeof(struct sockaddr_in)) < 0) {
    return SOCKET_CONNECT;
  }
  return SUCCESS;
}

RETCODE
SocketSend(Socket* sock, Data* data, Address* addr) {
  if (addr == NULL) {
    if (send(sock->socket_fd, data->ptr, data->len, 0) < 0) {
      return SOCKET_SEND;
    }
    return SUCCESS;
  }
  struct sockaddr_in client_addr;
  AddressToSockaddrIn(&client_addr, addr);
  if (sendto(sock->socket_fd, data->ptr, data->len, 0,
             (const struct sockaddr*)&client_addr,
             sizeof(struct sockaddr_in)) < 0) {
    return SOCKET_SEND;
  }
  return SUCCESS;
}

RETCODE
SocketReceive(Socket* sock, Data* buffer, Address* addr) {
  if (addr == NULL) {
    if (recv(sock->socket_fd, buffer->ptr, buffer->len, 0) < 0) {
      return errno == EAGAIN ? SOCKET_TIMEOUT : SOCKET_RECEIVE;
    }
    return SUCCESS;
  }
  struct sockaddr_storage seed;
  socklen_t seedlen = sizeof(seed);
  if (recvfrom(sock->socket_fd, buffer->ptr, buffer->len, 0,
               (struct sockaddr*)&seed, &seedlen) < 0) {
    return errno == EAGAIN ? SOCKET_TIMEOUT : SOCKET_RECEIVE;
  }
#ifdef __IPV4__
  memcpy(&addr->ip, &((struct sockaddr_in*)&seed)->sin_addr, sizeof(addr->ip));
  addr->port = ((struct sockaddr_in*)&seed)->sin_port;
#else
#error "Unsupported type of netcode"
#endif
  return SUCCESS;
}

RETCODE
SocketSetTimeout(Socket* sock, time_t milliseconds) {
  struct timeval tv = (struct timeval){.tv_sec = milliseconds / 1000,
                                       .tv_usec = milliseconds % 1000};
  if (setsockopt(sock->socket_fd, SOL_SOCKET, SO_RCVTIMEO, (struct timeval*)&tv,
                 sizeof(struct timeval)) == -1) {
    return SOCKET_SETTIMEOUT;
  }
  return SUCCESS;
}
