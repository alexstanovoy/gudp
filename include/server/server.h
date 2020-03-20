/**
 * @file server.h
 *
 * @brief      Contains server structures and interface for interacting.
 */

#pragma once

#include <stdint.h>

#include "common/retcode.h"
#include "networking/packet.h"
#include "networking/socket.h"

/**
 * @brief      Represents one of the connected clients to the server.
 */
typedef struct gudp_connected_client_t {
  /// Address of the client.
  Address* addr;
} ConnectedClient;

/**
 * @brief      Server structure.
 */
typedef struct gudp_server_t {
  /// Array of connected clients.
  ConnectedClient* clients;
  /// Server socket.
  Socket sock;
  /// Clients array size.
  uint16_t clients_count;
  /// Clients array capacity.
  uint16_t clients_capacity;
} Server;

/**
 * @brief      Initializes the server.
 *
 * @param      srv   The pointer to the server to initialize.
 *
 * @return     SUCCESS if initializing is successiful, and SERVER_INIT_FAILURE
 *             when error occures.
 */
RETCODE
ServerInit(Server* srv);

/**
 * @brief      Destroys the server and sends clients the message.
 *
 * @param      srv   The pointer to the server to destroy.
 *
 * @return     SUCCESS if initializing is succesiful, and SERVER_DESTROY_FAILURE
 *             when error occures.
 */
RETCODE
ServerDestroy(Server* srv);

/**
 * @brief      Receives a message from specified client.
 *
 * @param      srv        The pointer to the server.
 * @param      data       The pointer to the buffer.
 * @param[in]  client_id  The client identifier.
 *
 * @return     SUCCESS if receive from is succesiful, and
 *             SERVER_RECEIVEFROM_FAILED when error occures.
 */
RETCODE
ServerReceiveFrom(Server* srv, Data* data, uint16_t client_id);

/**
 * @brief      Receives one message from the server message queue.
 *
 * @param      srv   The pointer to the server.
 * @param      data  The pointer to the buffer.
 *
 * @return     SUCCESS if receive is successiful, and SERVER_RECEIVE_FAILED
 *             when error occures.
 */
RETCODE
ServerReceive(Server* srv, Data* data);

/**
 * @brief      Sends one message to the specified client.
 *
 * @param      srv        The pointer to the server.
 * @param[in]  client_id  The client identifier.
 * @param      data       The pointer to the message.
 *
 * @return     SUCCESS if receive is successiful, and SERVER_SENDTO_FAILED when
 *             error occures.
 */
RETCODE
ServerSendTo(Server* srv, Data* data, uint16_t client_id);

/**
 * @brief      Sends message to all connected clients.
 *
 * @param      srv   The pointer to the server.
 * @param      data  The pointer to the data.
 *
 * @return     SUCCESS if receive is successiful, and SERVER_SEND_FAILED when
 *             error occures.
 */
RETCODE
ServerSend(Server* srv, Data* data);
