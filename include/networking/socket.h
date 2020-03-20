/**
 * @file socket.h
 *
 * @brief      Provides structures and functions for conveniant,
 *             platform-independent socket creation, destroying and
 *             modification.
 */

#pragma once

#include <stddef.h>
#include <stdint.h>

#include "common/retcode.h"
#include "networking/packet.h"

/**
 * @brief      A crossplatform structure that represents OS socket.
 */
typedef struct gudp_socket_t Socket;

/**
 * @brief      A structure that represents address. Can be IPv4 or IPv6
 *             depending on compile options.
 */
typedef struct gudp_address_t Address;

/**
 * @brief      A enumeration that stores flags for operations with sockets.
 *             Exact values are platform-dependent.
 */
typedef enum gudp_socket_flags FLAG;

/**
 * @brief      Initializes the sockets. Must be used before creating sockets.
 *
 * @return     SUCCESS if initialization is successiful, and SOCKET_INIT_FAILURE
 *             when error occures.
 */
RETCODE
SocketInit();

/**
 * @brief      Shutdowns the sockets. Must be used after closing sockets.
 *
 * @return     SUCCESS if shutdown is successiful, and SOCKET_CLEANUP_FAILURE
 *             when error occures.
 */
RETCODE
SocketShutdown();

/**
 * @brief      Creates a socket.
 *
 * @param      sock  The pointer to the socket.
 *
 * @return     Socket file descriptor if creation is successiful, and
 *             SOCKET_CREATION_FAILED when error occures.
 */
RETCODE
SocketCreate(Socket* sock);

/**
 * @brief      Closes the socket.
 *
 * @param      sock  The pointer to the socket.
 *
 * @return     SUCCESS if closing is successiful, and SOCKET_CLOSING_FAILED when
 *             error occures.
 */
RETCODE
SocketClose(Socket* sock);

/**
 * @brief      Bind the socket for listening.
 *
 * @param      sock  The pointer to the socket.
 * @param      addr  The address.
 *
 * @return     SUCCESS if bind is successiful, and SOCKET_BIND_FAILED when error
 *             occures.
 */
RETCODE
SocketBind(Socket* sock, Address* addr);

/**
 * @brief      Connects a socket to the server.
 *
 * @param      sock  The pointer to the socket.
 * @param      addr  The address.
 *
 * @return     SUCCESS if connect is successiful, and SOCKET_CONNECT_FAILED when
 *             error occures.
 */
RETCODE
SocketConnect(Socket* sock, Address* addr);

/**
 * @brief      Sends message to the address via socket with specified flags.
 *
 * @param      sock   The pointer to the socket.
 * @param      data   The pointer to the message.
 * @param      addr   The address.
 * @param[in]  flags  The flags.
 *
 * @return     SUCCESS if sending is successiful, and SOCKET_SENDTO_FAILED when
 *             error occures.
 */
RETCODE
SocketSendTo(Socket* sock, Data* data, Address* addr, int flags);

/**
 * @brief      Sends message via socket with specified flags. Socket must be
 *             connected.
 *
 * @param      sock   The pointer to the socket.
 * @param      data   The pointer to the message.
 * @param[in]  flags  The flags.
 *
 * @return     SUCCESS if sending is successiful, and SOCKET_SENDTO_FAILED when
 *             error occures.
 */
RETCODE
SocketSend(Socket* sock, Data* data, int flags);

/**
 * @brief      Receives a message via provided socket from specified address.
 *
 * @param      sock   The pointer to the socket.
 * @param      data   The pointer to the buffer.
 * @param      addr   The pointer to the address.
 * @param[in]  flags  The flags.
 *
 * @return     SUCCESS if sending is successiful, and SOCKET_RECEIVEFROM_FAILED
 *             when error occures.
 */
RETCODE
SocketReceiveFrom(Socket* sock, Data* data, Address* addr, int flags);

/**
 * @brief      Receives a message via provided socket with specified flags.
 *             Socket must be binded.
 *
 * @param      sock   The pointer to the socket.
 * @param      data   The pointer to the buffer.
 * @param[in]  flags  The flags.
 *
 * @return     SUCCESS if sending is successiful, and SOCKET_RECEIVEFROM_FAILED
 *             when error occures.
 */
RETCODE
SocketReceive(Socket* sock, Data* data, int flags);
