#pragma once

#include "common/retcode.h"
#include "server/server_struct.h"

const int kBaseClients = 65535;

RETCODE
ServerInit(Server* srv);

void ServerDestroy(Server* srv);

RETCODE
ServerReceive(Server* srv, Response* response);

RETCODE
ServerSendTo(Server* srv, Response* response);

RETCODE
ServerSend(Server* srv, Response* response);
