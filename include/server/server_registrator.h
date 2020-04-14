#pragma once

#include "common/retcode.h"
#include "networking/socket.h"
#include "server/server_struct.h"

RETCODE
ServerRegistratorFindUser(Server* srv, uint16_t client_id);

RETCODE
ServerRegistratorGetUserId(Server* srv, Address* addr, uint16_t* client_id);

RETCODE
ServerRegistratorGetUser(Server* srv, uint16_t client_id,
                         ConnectedClient** client);
