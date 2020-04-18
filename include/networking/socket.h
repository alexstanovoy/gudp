/**
 * @file sock.h
 *
 * @brief      Provides structures and functions for conveniant,
 *             platform-independent sock creation, destroying and
 *             modification.
 *
 * @author     Alexander Stanovoy
 */

#pragma once

#include <stdint.h>
#include <string.h>

#include "common/retcode.h"
#include "networking/packet.h"

#ifdef __LINUX__
#include <arpa/inet.h>

typedef struct {
  int socket_fd;
} Socket;
#else
#error "Unsupported platform"
#endif

#ifdef __IPV4__

typedef struct {
  uint32_t ip;
  uint16_t port;
} Address;

RETCODE
AddressInit(Address* addr, const char* ip, uint16_t port);

void AddressDestroy(Address* addr);

void AddressCopy(Address* dest, Address* src);

#else
#error "Unsupported type of netcode"
#endif

/**
 * @brief      Startups the sockets.
 *
 * @return     SUCCESS if initialization is successiful, and SOCKET_INIT_FAILURE
 *             when error occures.
 *
 * @since      0.0.1
 *
 * @note       Must be used before creating sockets on Windows only.
 */
RETCODE
SocketsStartup();

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
SocketsShutdown();

/**
 * @brief      Initializes a sock.
 *
 * @param      sock  The pointer to the sock.
 *
 * @return     SUCCESS if initialization is successiful, and SOCKET_INIT_FAILED
 *             if error occures.
 *
 * @since      0.0.1
 */
RETCODE
SocketInit(Socket* sock);

/**
 * @brief      Destroys the sock.
 *
 * @param      sock  The pointer to the sock.
 *
 * @since      0.0.1
 *
 * @note       It's guaranteed SocketDestroy() will work correctly after
 *             unsuccessful SocketCreate().
 */
void SocketDestroy(Socket* sock);

/**
 * @brief      Binds the sock for listening.
 *
 * @param      sock  The pointer to the sock.
 * @param      addr    The pointer to the address.
 *
 * @return     SUCCESS if bind is successiful, and SOCKET_BIND_FAILED when error
 *             occures.
 *
 * @since      0.0.1
 */
RETCODE
SocketBind(Socket* sock, Address* addr);

/**
 * @brief      Connects a sock to the server.
 *
 * @param      sock  The pointer to the sock.
 * @param      addr    The pointer to the address.
 *
 * @return     SUCCESS if connect is successiful, and SOCKET_CONNECT_FAILED when
 *             error occures.
 *
 * @since      0.0.1
 */
RETCODE
SocketConnect(Socket* sock, Address* addr);

/**
 * @brief      Sends a message via sock to provided address.
 *
 * @param      sock  The pointer to the sock.
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
SocketSend(Socket* sock, Data* data, Address* addr);

/**
 * @brief      Receives a message via sock and saves address of sender to
 *             provided address structure.
 *
 * @param      sock  The pointer to the sock.
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
SocketReceive(Socket* sock, Data* buffer, Address* addr);

RETCODE
SocketSetTimeout(Socket* sock, time_t milliseconds);
