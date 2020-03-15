#include <errno.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include "common/retcodes.h"
#include "networking/udplowlevel.h"

typedef struct gudp_socket_ipv4 {
  int socket_fd;
} ipv4_sock;

RETCODE
InitializeSockets() {
  return SUCCESS;
}

RETCODE
ShutdownSockets() {
  return SUCCESS;
}

RETCODE
CreateSocket(ipv4_sock* sock) {
  int socket_fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
  if (socket_fd < 0) {
    return SOCKET_CREATION_FAILED;
  }
  sock->socket_fd = socket_fd;
  return SUCCESS;
}

RETCODE
CloseSocket(ipv4_sock* sock) {
  if (close(sock->socket_fd) < 0) {
    return SOCKET_CLOSING_FAILED;
  }
  return SUCCESS;
}

RETCODE
BindSocket(ipv4_sock* sock, uint32_t addr, uint16_t port) {
  struct sockaddr_in server_sockaddr = {
      .sin_family = AF_INET, .sin_addr = addr, .sin_port = htons(port)};
  if (bind(sock->socket_fd, (const struct sockaddr*)&server_sockaddr,
           sizeof(struct sockaddr_in)) < 0) {
    return SOCKET_BIND_FAILED;
  }
  return SUCCESS;
}

RETCODE
ConnectSocket(ipv4_sock* sock, uint32_t addr, uint16_t port) {
  struct sockaddr_in server_sockaddr = {
      .sin_family = AF_INET, .sin_addr = addr, .sin_port = htons(port)};
  if (connect(sock->socket_fd, (const struct sockaddr*)&server_sockaddr,
              sizeof(struct sockaddr_in)) < 0) {
    return SOCKET_CONNECT_FAILED;
  }
  return SUCCESS;
}

RETCODE
SendMessage(ipv4_sock* sock, void* msg, size_t len) {
  ssize_t sended_cnt = send(sock->socket_fd, msg, len);
  if (sended_cnt < 0) {
    return SOCKET_SEND_FAILED;
  }
  if (sended_cnt < len) {
    return SOCKET_SEND_LESSLEN;
  }
  return SUCCESS;
}

RETCODE
ReceiveMessage(ipv4_sock* sock, void* msg, size_t len, int flags) {
  
}






