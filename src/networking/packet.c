#include "networking/packet.h"

#include <stdlib.h>
#include <string.h>

#include "common/macro.h"
#include "common/retcode.h"

RETCODE
DataInit(Data* data) {
  if ((data->ptr = malloc(kDataLength)) == NULL) {
    return NOT_ENOUGH_MEMORY;
  }
  data->len = kDataLength;
  return SUCCESS;
}

void DataDestroy(Data* data) {
  free(data->ptr);
}

RETCODE
ResponseInit(Response* response) {
  THROW_OR_CONTINUE(DataInit(&response->data));
  return SUCCESS;
}

void ResponseDestroy(Response* response) {
  DataDestroy(&response->data);
}

void ResponseSetType(Response* response, ResponseType type) {
  response->type = type;
}

ResponseType ResponseGetType(Response* response) {
  return response->type;
}

void ResponseSetClientId(Response* response, uint16_t client_id) {
  response->client_id = client_id;
}

uint16_t ResponseGetClientId(Response* response) {
  return response->client_id;
}

RETCODE
GetResponseFromData(Data* in, Response* out) {
  ResponseSetType(out, ((PacketHeader*)in)->type);
  memcpy(out->data.ptr, in->ptr + sizeof(PacketHeader),
         ((PacketHeader*)in)->len);
  return SUCCESS;
}

RETCODE
GetDataFromResponse(Response* in, Data* out) {
  ((PacketHeader*)out)->type = in->type;
  ((PacketHeader*)out)->len = in->data.len;
  memcpy(out->ptr, in->data.ptr, in->data.len);
  return SUCCESS;
}
