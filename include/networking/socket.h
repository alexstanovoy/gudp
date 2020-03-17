#pragma once

#include <stddef.h>
#include <stdint.h>

#include "common/retcodes.h"

/**
 * @brief      A crossplatform structure that represents OS socket.
 */
typedef struct gudp_socket_ipv4 IPv4Sock;

/**
 * @brief      Initializes the sockets. Must be used before creating sockets on
 *             Windows.
 *
 * @return     SUCCESS if initialization is successiful, and
 *             WINSOCK_INIT_FAILURE when error occures.
 */
RETCODE
InitializeSockets();

/**
 * @brief      Shutdowns the socket. Must be used jafter creating sockets on
 *             Windows.
 *
 * @return     SUCCESS if shutdown is successiful, and WINSOCK_CLEANUP_FAILURE
 *             when error occures.
 */
RETCODE
ShutdownSockets();

/**
 * @brief      Creates a socket.
 *
 * @param      sock  The pointer to resulting socket.
 *
 * @return     Socket file descriptor if creation is successiful, and
 *             SOCKET_CREATION_FAILED when error occures.
 */
RETCODE
CreateSocket(IPv4Sock* sock);

/**
 * @brief      Closes the socket.
 *
 * @param      sock  The pointer to resulting socket.
 *
 * @return     SUCCESS if closing is successiful, and SOCKET_CLOSING_FAILED when
 *             error occures.
 */
RETCODE
CloseSocket(IPv4Sock* sock);

/**
 * @brief      Bind the socket for listening.
 *
 * @param      sock  The pointer to socket.
 * @param[in]  addr  The IPv4 address.
 * @param[in]  port  The port.
 *
 * @return     SUCCESS if bind is successiful, and SOCKET_BIND_FAILED when error
 *             occures.
 */
RETCODE
BindSocket(IPv4Sock* sock, uint32_t addr, uint16_t port);

/**
 * @brief      Connects a socket to the server.
 *
 * @param      sock  The pointer to socket.
 * @param[in]  addr  The IPv4 address.
 * @param[in]  port  The port.
 *
 * @return     SUCCESS if connect is successiful, and SOCKET_CONNECT_FAILED when
 *             error occures.
 */
RETCODE
ConnectSocket(IPv4Sock* sock, uint32_t addr, uint16_t port);

/**
 * @brief      Sends a message to specified adress via socket.
 *
 * @param      sock  The pointer to socket.
 * @param      msg   The pointer to the start of the message.
 * @param[in]  len   The number of bytes to send from the message
 * @param[in]  flags The flags
 *
 * @todo       Detailed flag description in SendMessage(),
 *
 * @return     SUCCESS if sending is successiful, and SOCKET_SEND_FAILED when
 *             error occures.
 */
RETCODE
SendMessage(IPv4Sock* sock, void* msg, size_t len, int flags);

/**
 * @brief      Receive a message via provided socket.
 *
 * @param      sock   The pointer to socket.
 * @param      buf    The pointer to the start of the buffer.
 * @param[in]  len    The buffer length.
 * @param[in]  flags  The flags.
 *
 * @todo       Detailed flag description in ReceiveMessage(), implementation on
 *             Linux.
 *
 * @return     SUCCESS if sending is successiful, and SOCKET_RECEIVE_FAILED when
 *             error occures.
 */
RETCODE
ReceiveMessage(IPv4Sock* sock, void* buf, size_t len, int flags);
