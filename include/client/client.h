/**
 * @file client.h
 *
 * @brief      Contains structure and interface for client interaction.
 *
 * @author     Alexander Stanovoy
 */

#pragma once

#include <stdint.h>

#include "networking/packet.h"
#include "networking/socket.h"

/**
 * @brief      The client structure.
 */
typedef struct {
  /// The socket of the client.
  Socket socket;
  /// The address of the server.
  Address addr;
} Client;

/**
 * @brief      Initializes the client and connects to the server.
 *
 * @param      client  The pointer to the client.
 * @param      addr    The pointer to the structure with server address.
 *
 * @return     SUCCESS when initialization is succesiful, or traceback of the
 *             following functions:
 *             - SocketInit()
 *             - AddressInit()
 *             - SocketConnect()
 *
 * @since      0.0.1
 */
RETCODE
ClientInit(Client* client, Address* addr);

/**
 * @brief      Destroys the client.
 *
 * @param      client  The pointer to the client.
 *
 * @since      0.0.1
 *
 * @note       It's guaranteed ClientDestroy() will work correctly after
 *             unsuccessful ClientInit().
 */
void ClientDestroy(Client* client);

/**
 * @brief      Receives the packet from the server.
 *
 * @param      client    The pointer to the client.
 * @param      response  The pointer to the response.
 *
 * @return     SUCCESS when receive is succesiful, or traceback of the following
 *             functions:
 *             - DataInit()
 *             - SocketReceive()
 *             - DataToResponse()
 *
 * @since      0.0.1
 */
RETCODE
ClientReceive(Client* client, Response* response);

/**
 * @brief      Sends a message to the server.
 *
 * @param      client    The pointer to the client.
 * @param      response  The pointer to the response.
 *
 * @return     SUCCESS when send is succesiful, or traceback of the following
 *             functions:
 *             - DataInit()
 *             - ResponseToData()
 *             - SocketSend()
 *
 * @since      0.0.1
 */
RETCODE
ClientSend(Client* client, Response* response);

/**
 * @brief      Sets the timeout for ClientReceive().
 *
 * @param      client        The pointer to the client.
 * @param[in]  milliseconds  The milliseconds to wait.
 *
 * @return     Traceback of SocketSetTimeout() function.
 *
 * @since      0.0.1
 */
RETCODE
ClientSetTimeout(Client* client, time_t milliseconds);

RETCODE
ClientMakeNonBlocking(Client* client);
