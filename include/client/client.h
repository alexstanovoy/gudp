/**
 * @file client.h
 *
 * @brief      Contains client structures and interface for interacting.
 */

#pragma once

#include <stdint.h>

#include "networking/packet.h"
#include "networking/socket.h"

/**
 * @brief      Client structure.
 */
typedef struct gudp_client_t {
  /// Socket for connection.
  Socket sock;
  /// Address of the server to which client is connected.
  Address addr;
  /// Last sent packet ID.
  uint16_t last_id;
  /// Ack bits for last 32 packets.
  uint32_t ack;
} Client;

/**
 * @brief      Creates client and connects it to the server with specified
 *             address.
 *
 * @param      clt   The pointer to the client to initialize.
 * @param      addr  The pointer to the server address.
 *
 * @return     SUCCESS if initializing is successiful, and CLIENT_INIT_FAILED
 *             when error occures.
 */
RETCODE
ClientInit(Client* clt, Address* addr);

/**
 * @brief      Destroys client and closes the connection with server.
 *
 * @param      clt   The pointer to the client to destroy.
 *
 * @return     SUCCESS if initializing is successiful, and
 *             CLIENT_DESTROY_FAILED when error occures.
 */
RETCODE
ClientDestroy(Client* clt);

/**
 * @brief      Receives one message from the server.
 *
 * @param      clt   The pointer to the client.
 * @param      data  The pointer to the resulting data.
 *
 * @return     SUCCESS if receive is successiful, and CLIENT_RECEIVE_FAILED when
 *             error occures.
 */
RETCODE
ClientReceive(Client* clt, Data* data);

/**
 * @brief      Sends one message to the server.
 *
 * @param      clt   The pointer to the client.
 * @param      data  The pointer to the message.
 *
 * @return     SUCCESS if receive is successiful, and CLIENT_SEND_FAILED when
 *             error occures.
 */
RETCODE
ClientSend(Client* clt, Data* data);
