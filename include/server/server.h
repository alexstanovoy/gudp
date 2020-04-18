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
#include "server/server_registrator.h"
#include "server/server_struct.h"

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
