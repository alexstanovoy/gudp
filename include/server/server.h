#pragma once

#include "common/retcode.h"
#include "networking/packet.h"
#include "server/server_struct.h"
#include "server/server_registrator.h"

const int kBaseClients = 65535;

RETCODE
ServerInit(Server* srv, Address* addr);

void ServerDestroy(Server* srv);

RETCODE
ServerReceive(Server* srv, Response* response);

RETCODE
ServerSendTo(Server* srv, Response* response);

RETCODE
ServerSend(Server* srv, Response* response);

RETCODE
ServerSetTimeout(Server* srv, time_t milliseconds);
