#pragma once

#include <stdint.h>

#include "common/retcode.h"
#include "networking/packet.h"
#include "server/server_struct.h"

RETCODE
ServerHandlerReceive(Server* srv, Response* response);

RETCODE
ServerHandlerSendTo(Server* srv, Data* data, uint16_t client_id);

RETCODE
ServerHandlerSend(Server* srv, Data* data);
