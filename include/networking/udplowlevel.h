#pragma once

/**
 * @brief      A crossplatform structure that represents OS socket.
 */
typedef struct gudp_socket_ipv4 ipv4_sock;

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
CreateSocket(ipv4_sock* sock);

/**
 * @brief      Closes the socket.
 *
 * @param      sock  The pointer to resulting socket.
 *
 * @return     SUCCESS if closing is successiful, and SOCKET_CLOSING_FAILED when
 *             error occures.
 */
RETCODE
CloseSocket(ipv4_sock* sock);

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
BindSocket(ipv4_sock* sock, uint32_t addr, uint16_t port);

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
ConnectSocket(ipv4_sock* sock, uint32_t addr, uint16_t port);

/**
 * @brief      Sends a message to specified adress via socket.
 *
 * @param      sock  The pointer to socket.
 * @param      msg   The pointer to the start of the message.
 * @param[in]  len   The number of bytes to send from the message
 *
 * @return     SUCCESS if sending is successiful, and SOCKET_SEND_FAILED when
 *             error occures.
 */
RETCODE
SendMessage(ipv4_sock* sock, void* msg, size_t len);

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
ReceiveMessage(ipv4_sock* sock, void* buf, size_t len, int flags);
