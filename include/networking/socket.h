/**
 * @file socket.h
 *
 * @brief      Provides structures and functions for conveniant,
 *             platform-independent socket creation, destroying and
 *             modification.
 *
 * @author     Alexander Stanovoy
 */

#pragma once

#include <stdint.h>

#include "common/retcode.h"
#include "networking/packet.h"

#ifdef __IPV4__
typedef struct {
  uint32_t ip;
  uint16_t port;
} Address;

RETCODE
AddressInit(Address* addr) {
  return SUCCESS;
}

void AddressDestroy(Address* addr) {
}
#endif

#ifdef __LINUX__
typedef struct {
  int socket_fd;
} Socket;
#endif

/**
 * @brief      Initializes the sockets.
 *
 * @return     SUCCESS if initialization is successiful, and SOCKET_INIT_FAILURE
 *             when error occures.
 *
 * @since      0.0.1
 *
 * @note       Must be used before creating sockets on Windows only.
 */
RETCODE
SocketInit();

/**
 * @brief      Shutdowns the sockets.
 *
 * @return     SUCCESS if shutdown is successiful, and SOCKET_CLEANUP_FAILURE
 *             when error occures.
 *
 * @since      0.0.1
 *
 * @note       Must be used after closing sockets on Windows only.
 */
RETCODE
SocketShutdown();

/**
 * @brief      Initializes a socket.
 *
 * @param      socket  The pointer to the socket.
 *
 * @return     SUCCESS if initialization is successiful, and SOCKET_INIT_FAILED
 *             if error occures.
 *
 * @since      0.0.1
 */
RETCODE
SocketInit(Socket* socket);

/**
 * @brief      Destroys the socket.
 *
 * @param      socket  The pointer to the socket.
 *
 * @since      0.0.1
 *
 * @note       It's guaranteed SocketDestroy() will work correctly after
 *             unsuccessful SocketCreate().
 */
void SocketDestroy(Socket* socket);

/**
 * @brief      Binds the socket for listening.
 *
 * @param      socket  The pointer to the socket.
 * @param      addr    The pointer to the address.
 *
 * @return     SUCCESS if bind is successiful, and SOCKET_BIND_FAILED when error
 *             occures.
 *
 * @since      0.0.1
 */
RETCODE
SocketBind(Socket* socket, Address* addr);

/**
 * @brief      Connects a socket to the server.
 *
 * @param      socket  The pointer to the socket.
 * @param      addr    The pointer to the address.
 *
 * @return     SUCCESS if connect is successiful, and SOCKET_CONNECT_FAILED when
 *             error occures.
 *
 * @since      0.0.1
 */
RETCODE
SocketConnect(Socket* socket, Address* addr);

/**
 * @brief      Sends a message via socket to provided address.
 *
 * @param      socket  The pointer to the socket.
 * @param      data    The pointer to the data to send.
 * @param      addr    The pointer to the address.
 *
 * @return     SUCCESS if send is successiful, and SOCKET_SEND_FAILED if error
 *             occures.
 *
 * @since      0.0.1
 *
 * @note       When pointer to the address is NULL, function sends data to the
 *             connected server.
 */
RETCODE
SocketSend(Socket* socket, Data* data, Address* addr);

/**
 * @brief      Receives a message via socket and saves address of sender to
 *             provided address structure.
 *
 * @param      socket  The pointer to the socket.
 * @param      buffer  The pointer to the buffer.
 * @param      addr    The pointer to the address.
 *
 * @return     SUCCESS if receive successiful, and SOCKET_RECEIVE_FAILED if
 *             error occures.
 *
 * @since      0.0.1
 *
 * @note       When pointer to address is NULL, function won't save address.
 */
RETCODE
SocketReceive(Socket* socket, Data* buffer, Address* addr);
