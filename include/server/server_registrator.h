#pragma once

#include "common/retcode.h"
#include "networking/socket.h"
#include "server/server_struct.h"

RETCODE
ConnectedClientInit(ConnectedClient* client);

void ConnectedClientDestroy(ConnectedClient* client);

RETCODE
ServerRegistratorInit(Server* srv);

void ServerRegistratorDestroy(Server* srv);

RETCODE
ServerRegistratorIsUserExist(Server* srv, Address* addr,
                             ConnectedClient** client);

RETCODE
ServerRegistratorGetUserByID(Server* srv, uint16_t client_id,
                             ConnectedClient** client);

RETCODE
ServerRegistratorAddUser(Server* srv, Address* addr, ConnectedClient** client);

void ServerRegistratorRemoveUser(Server* srv, Address* addr);
