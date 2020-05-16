#include "server/registrator.h"

#include <stdlib.h>
#include <string.h>

#include "common/macro.h"
#include "common/retcode.h"
#include "networking/socket.h"
#include "server/server.h"

static const int kBaseClients = 65535;

RETCODE
ConnectedClientInit(ConnectedClient* client) {
  THROW_OR_CONTINUE(AddressInit(&client->addr, NULL, 0));
  return SUCCESS;
}

void ConnectedClientDestroy(ConnectedClient* client) {
  AddressDestroy(&client->addr);
}

RETCODE
RegistratorInit(Registrator* registrator) {
  registrator->clients =
      (ConnectedClient**)malloc(kBaseClients * sizeof(ConnectedClient*));
  if (registrator->clients == NULL) {
    return NOT_ENOUGH_MEMORY;
  }
  for (uint16_t id = 0; id < kBaseClients; ++id) {
    registrator->clients[id] = NULL;
  }
  return SUCCESS;
}

void RegistratorDestroy(Registrator* registrator) {
  free(registrator->clients);
}

RETCODE
RegistratorIterInit(Registrator* registrator, RegistratorIter* iter) {
  iter->index = 0;
  while (iter->index < kBaseClients) {
    if (registrator->clients[iter->index] != NULL) {
      break;
    }
    ++iter->index;
  }
  return SUCCESS;
}

void RegistratorIterDestroy(RegistratorIter* iter) {
}

RETCODE
RegistratorGetUserByAddress(Registrator* registrator, Address* addr,
                            ConnectedClient** client) {
  for (uint16_t id = 0; id < kBaseClients; ++id) {
    if (registrator->clients[id] != NULL &&
        memcmp(&registrator->clients[id]->addr, addr, sizeof(Address)) == 0) {
      *client = registrator->clients[id];
      return SUCCESS;
    }
  }
  return SERVER_USER_NOT_FOUND;
}

RETCODE
RegistratorGetUserByID(Registrator* registrator, uint16_t client_id,
                       ConnectedClient** client) {
  if (registrator->clients[client_id] != NULL) {
    *client = registrator->clients[client_id];
    return SUCCESS;
  }
  return SERVER_USER_NOT_FOUND;
}

RETCODE
RegistratorAddUser(Registrator* registrator, Address* addr,
                   ConnectedClient** client) {
  for (uint16_t id = 0; id < kBaseClients; ++id) {
    if (registrator->clients[id] == NULL) {
      registrator->clients[id] =
          (ConnectedClient*)malloc(sizeof(ConnectedClient));
      THROW_OR_CONTINUE(ConnectedClientInit(registrator->clients[id]));
      memcpy(&registrator->clients[id]->addr, addr, sizeof(Address));
      registrator->clients[id]->client_id = id;
      *client = registrator->clients[id];
      return SUCCESS;
    }
  }
  return SERVER_CROWDED;
}

void RegistratorRemoveUserByAddress(Registrator* registrator, Address* addr) {
  for (uint16_t id = 0; id < kBaseClients; ++id) {
    if (memcmp(&registrator->clients[id]->addr, addr, sizeof(Address)) == 0) {
      ConnectedClientDestroy(registrator->clients[id]);
      free(registrator->clients[id]);
      break;
    }
  }
}

void RegistratorIterNext(Registrator* registrator, RegistratorIter* iter) {
  while (iter->index < kBaseClients) {
    if (registrator->clients[++iter->index] != NULL) {
      return;
    }
  }
}

int RegistratorIterStopped(Registrator* registrator, RegistratorIter* iter) {
  return iter->index == kBaseClients;
}

ConnectedClient* RegistratorIterDereference(Registrator* registrator,
                                            RegistratorIter* iter) {
  return registrator->clients[iter->index];
}
