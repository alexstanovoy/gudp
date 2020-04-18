/**
 * @file socket.h
 *
 * @brief      Provides structures and functions for convenient,
 *             platform-independent socket creation, destroying and
 *             modification.
 *
 * @author     Alexander Stanovoy
 */

#pragma once

#include <stdint.h>
#include <string.h>
#ifdef __LINUX__
#include <arpa/inet.h>
#endif

#include "common/retcode.h"
#include "networking/packet.h"

/**
 * @brief      The structure representing socket.
 */
typedef struct gudp_socket_t Socket;

#ifdef __LINUX__
struct gudp_socket_t {
  int socket_fd;
};
#else
#error "Unsupported platform"
#endif

/**
 * @brief      The structure representing address of recipient.
 */
typedef struct gudp_address_t Address;

#ifdef __IPV4__
struct gudp_address_t {
  uint32_t ip;
  uint16_t port;
};

RETCODE
AddressInit(Address* addr, const char* ip, uint16_t port);

void AddressDestroy(Address* addr);

void AddressCopy(Address* dest, Address* src);
#else
#error "Unsupported type of netcode"
#endif

/**
 * @brief      Runs the sockets.
 *
 * @return     SUCCESS if initialization is successiful, and SOCKET_INIT when
 *             error occures.
 *
 * @since      0.0.1
 */
RETCODE
SocketsStartup();

/**
 * @brief      Shutdowns the sockets.
 *
 * @return     SUCCESS if shutdown is successiful, and SOCKET_CLEANUP when error
 *             occures.
 *
 * @since      0.0.1
 */
RETCODE
SocketsShutdown();

/**
 * @brief      Initializes a socket.
 *
 * @param      sock  The pointer to the sock.
 *
 * @return     SUCCESS if initialization is successiful, and SOCKET_INIT when
 *             error occures.
 *
 * @since      0.0.1
 */
RETCODE
SocketInit(Socket* sock);

/**
 * @brief      Destroys the socket.
 *
 * @param      sock  The pointer to the socket.
 *
 * @since      0.0.1
 *
 * @note       It's guaranteed SocketDestroy() will work correctly after
 *             unsuccessful SocketCreate().
 */
void SocketDestroy(Socket* sock);

/**
 * @brief      Binds the socket for listening.
 *
 * @param      sock  The pointer to the socket.
 * @param      addr  The pointer to the address.
 *
 * @return     SUCCESS if bind is successiful, and SOCKET_BIND when error
 *             occures.
 *
 * @since      0.0.1
 */
RETCODE
SocketBind(Socket* sock, Address* addr);

/**
 * @brief      Connects a socket to the server.
 *
 * @param      sock  The pointer to the socket.
 * @param      addr  The pointer to the address.
 *
 * @return     SUCCESS if connect is successiful, and SOCKET_CONNECT when error
 *             occures.
 *
 * @since      0.0.1
 */
RETCODE
SocketConnect(Socket* sock, Address* addr);

/**
 * @brief      Sends a message via socket to provided address.
 *
 * @param      sock  The pointer to the socket.
 * @param      data  The pointer to the data to send.
 * @param      addr  The pointer to the address.
 *
 * @return     SUCCESS if send is successiful, and SOCKET_SEND if error occures.
 *
 * @since      0.0.1
 *
 * @note       When pointer to the address is NULL, function sends data to the
 *             connected server.
 */
RETCODE
SocketSend(Socket* sock, Data* data, Address* addr);

/**
 * @brief      Receives a message via socket and saves address of sender to
 *             provided address structure.
 *
 * @param      sock    The pointer to the socket.
 * @param      buffer  The pointer to the buffer.
 * @param      addr    The pointer to the address.
 *
 * @return     SUCCESS if receive successiful, and SOCKET_RECEIVE if error
 *             occures.
 *
 * @since      0.0.1
 *
 * @note       When pointer to address is NULL, function won't save address.
 */
RETCODE
SocketReceive(Socket* sock, Data* buffer, Address* addr);

/**
 * @brief      Sets the timeout for receiving message from socket.
 *
 * @param      sock          The pointer to the socket.
 * @param[in]  milliseconds  The amount of milliseconds to wait until success.
 *
 * @since      0.0.1
 *
 * @return     SUCCESS if receive is successiful, and SOCKET_SETTIMEOUT when
 *             error occures.
 */
RETCODE
SocketSetTimeout(Socket* sock, time_t milliseconds);
