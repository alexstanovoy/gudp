#pragma once

#include "server/server_struct.h"

const int kBaseClients = 65535;

RETCODE
ServerInit(Server* srv);

void ServerDestroy(Server* srv);
