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

void DataSet(Data* data, const char* msg) {
  size_t len = strlen(msg);
  strncpy(data->ptr, msg, len);
  data->len = len;
}

RETCODE
ResponseInit(Response* response) {
  THROW_OR_CONTINUE(DataInit(&response->data));
  return SUCCESS;
}

void ResponseDestroy(Response* response) {
  DataDestroy(&response->data);
}

void ResponseSetData(Response* response, const char* msg) {
  size_t len = strlen(msg);
  strncpy(response->data.ptr, msg, len);
  response->data.len = len;
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
DataToResponse(Data* in, Response* out) {
  memcpy(&out->type, &((PacketHeader*)in->ptr)->type, sizeof(ResponseType));
  memcpy(&out->data.len, &((PacketHeader*)in->ptr)->len, sizeof(uint16_t));
  memcpy(out->data.ptr, in->ptr + sizeof(PacketHeader), out->data.len);
  return SUCCESS;
}

RETCODE
ResponseToData(Response* in, Data* out) {
  ((PacketHeader*)out->ptr)->type = in->type;
  ((PacketHeader*)out->ptr)->len = in->data.len;
  memcpy(out->ptr + sizeof(PacketHeader), in->data.ptr, in->data.len);
  return SUCCESS;
}
