/**
 * @file registrator.h
 *
 * @brief      Contains structures and interface for server registrator. It's
 *             the data structure that link the Address with Client ID and vice
 *             versa. Also contains RegistratorIter for abstraction.
 *
 * @author     Alexander Stanovoy
 */

#pragma once

#include "common/retcode.h"
#include "networking/socket.h"

/// The maximum number of clients supported for the moment.
static const int kBaseClients = 65535;

/**
 * @brief      The structure to represent connected client.
 */
typedef struct {
  /// Address of the Client.
  Address addr;
  /// Internal ID of the Client.
  uint16_t client_id;
} ConnectedClient;

/**
 * @brief      Registrator structure.
 */
typedef struct {
  /// Array of pointers to clients.
  ConnectedClient** clients;
} Registrator;

/**
 * @brief      Iterator over ConnectedClient's in Registrator.
 */
typedef struct {
  /// Index in ConnectedClient array.
  uint16_t index;
} RegistratorIter;

/**
 * @brief      Initializes the ConnectedClient.
 *
 * @param      client  The pointer to the connected client.
 *
 * @return     SUCCESS when initialization is succesiful, or NOT_ENOUGH_MEMORY
 *             when error occures.
 *
 * @since      0.0.1
 */
RETCODE
ConnectedClientInit(ConnectedClient* client);

/**
 * @brief      Destroys the connected client.
 *
 * @param      client  The pointer to the connected client.
 *
 * @since      0.0.1
 *
 * @note       It's guaranteed ConnectedClientDestroy() will work correctly
 *             after unsuccessful ConnectedClientInit().
 */
void ConnectedClientDestroy(ConnectedClient* client);

/**
 * @brief      Initializes the registrator.
 *
 * @param      registrator  The pointer to the registrator.
 *
 * @return     SUCCESS when initialization is succesiful, or NOT_ENOUGH_MEMORY
 *             when error occures.
 *
 * @since      0.0.1
 */
RETCODE
RegistratorInit(Registrator* registrator);

/**
 * @brief      Destroys the registrator.
 *
 * @param      registrator  The pointer to the registrator.
 *
 * @since      0.0.1
 *
 * @note       It's guaranteed RegistratorDestroy() will work correctly after
 *             unsuccessful RegistratorInit().
 */
void RegistratorDestroy(Registrator* registrator);

/**
 * @brief      Initializes the registrator iterator.
 *
 * @param      registrator  The pointer to the registrator.
 * @param      iter         The pointer to the iterator.
 *
 * @return     SUCCESS if initialization is succesiful, or NOT_ENOUGH_MEMORY
 *             when error occures.
 *
 * @since      0.0.1
 */
RETCODE
RegistratorIterInit(Registrator* registrator, RegistratorIter* iter);

/**
 * @brief      Destroys the iterator.
 *
 * @param      iter  The pointer to the iterator.
 *
 * @since      0.0.1
 *
 * @note       It's guaranteed RegistratorIterDestroy() will work correctly
 * after unsuccessful RegistratorIterInit().
 */
void RegistratorIterDestroy(RegistratorIter* iter);

/**
 * @brief      Gets the ConnectedClient by Address.
 *
 * @param      registrator  The pointer to the registrator.
 * @param      addr         The pointer to the address.
 * @param      client       The pointer ro pointer to the connected client.
 *
 * @return     SUCCESS when user exists, and SERVER_USER_NOT_FOUND when not.
 *
 * @since      0.0.1
 */
RETCODE
RegistratorGetUserByAddress(Registrator* registrator, Address* addr,
                            ConnectedClient** client);

/**
 * @brief      Gets the ConnectedClient by ID.
 *
 * @param      registrator  The pointer to the registrator.
 * @param[in]  client_id    The client identifier
 * @param      client       The pointer ro pointer to the connected client.
 *
 * @return     SUCCESS when user exists, and SERVER_USER_NOT_FOUND when not.
 *
 * @since      0.0.1
 */
RETCODE
RegistratorGetUserByID(Registrator* registrator, uint16_t client_id,
                       ConnectedClient** client);

/**
 * @brief      Adds the user to registrator.
 *
 * @param      registrator  The pointer to the registrator.
 * @param      addr         The pointer to the address.
 * @param      client       The pointer ro pointer to the connected client.
 *
 * @return     SUCCESS when client added successifuly, ConnectedClientInit()
 *             error or SERVER_CROWDED when there are no more place.
 *
 * @since      0.0.1
 */
RETCODE
RegistratorAddUser(Registrator* registrator, Address* addr,
                   ConnectedClient** client);

/**
 * @brief      Removes user via Address.
 *
 * @param      registrator  The pointer to the registrator.
 * @param      addr         The pointer to the address.
 *
 * @since      0.0.1
 */
void RegistratorRemoveUserByAddress(Registrator* registrator, Address* addr);

/**
 * @brief      Moves the iterator to the next client.
 *
 * @param      registrator  The pointer to the registrator.
 * @param      iter         The pointer to the iterator.
 *
 * @since      0.0.1
 */
void RegistratorIterNext(Registrator* registrator, RegistratorIter* iter);

/**
 * @brief      Checks whether iterator is on end position.
 *
 * @param      registrator  The pointer to the registrator.
 * @param      iter         The pointer to the iterator.
 *
 * @return     True or false.
 *
 * @since      0.0.1
 */
int RegistratorIterStopped(Registrator* registrator, RegistratorIter* iter);

/**
 * @brief      Dereferences the iterator providing the ConnectedClient.
 *
 * @param      registrator  The pointer to the registrator.
 * @param      iter         The pointer to the iterator.
 *
 * @return     The pointer to the ConnectedClient.
 *
 * @since      0.0.1
 */
ConnectedClient* RegistratorIterDereference(Registrator* registrator,
                                            RegistratorIter* iter);
