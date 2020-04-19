/**
 * @file server.h
 *
 * @brief      Contains structure and interface for server interaction.
 *
 * @author     Alexander Stanovoy
 */

#pragma once

#include "common/retcode.h"
#include "networking/packet.h"
#include "server/registrator.h"

/**
 * @brief      The server structure.
 */
typedef struct {
  /// Server socket.
  Socket socket;
  /// Server registrator.
  Registrator registrator;
} Server;

/**
 * @brief      Initalizes the server and binds it to the specified address.
 *
 * @param      srv   The pointer to the server.
 * @param      addr  The pointer to the address.
 *
 * @return     SUCCESS when initialization is succesiful, or traceback of the
 *             following functions:
 *             - RegistratorInit()
 *             - SocketInit()
 *             - SocketBind()
 *
 * @since      0.0.1
 */
RETCODE
ServerInit(Server* srv, Address* addr);

/**
 * @brief      Destroys the server.
 *
 * @param      srv   The pointer to the server.
 *
 * @since      0.0.1
 *
 * @note       It's guaranteed ServerDestroy() will work correctly after
 *             unsuccessful ServerInit().
 */
void ServerDestroy(Server* srv);

/**
 * @brief      Receives one response.
 *
 * @param      srv       The pointer to the server.
 * @param      response  The pointer to the response.
 *
 * @return     SUCCESS when receive is succesiful, or traceback of the following
 *             functions:
 *             - DataInit()
 *             - SocketReceive()
 *             - DataToResponse()
 *             - AddressInit()
 *             - RegistratorAddUser()
 *
 * @since      0.0.1
 */
RETCODE
ServerReceive(Server* srv, Response* response);

/**
 * @brief      Sends the response to the specified client. Client ID must be set
 *             on response.
 *
 * @param      srv       The pointer to the server.
 * @param      response  The pointer to the response.
 *
 * @return     SUCCESS when send to is succesiful, or traceback of the following
 *             functions:
 *             - DataInit()
 *             - ResponseToData()
 *             - RegistratorGetUserByID()
 *             - SocketSend()
 *
 * @since      0.0.1
 */
RETCODE
ServerSendTo(Server* srv, Response* response);

/**
 * @brief      Sends the response to all of the connected clients.
 *
 * @param      srv       The pointer to the server.
 * @param      response  The pointer to the response.
 *
 * @return     SUCCESS when send is succesiful, or traceback of the following
 *             functions:
 *             - RegistratorIterInit()
 *             - ServerSendTo()
 *
 * @since      0.0.1
 */
RETCODE
ServerSend(Server* srv, Response* response);

/**
 * @brief      Sets the timeout for ServerReceive().
 *
 * @param      srv           The pointer to the server.
 * @param[in]  milliseconds  The milliseconds to wait.
 *
 * @return     Traceback of SocketSetTimeout() function.
 *
 * @since      0.0.1
 */
RETCODE
ServerSetTimeout(Server* srv, time_t milliseconds);
