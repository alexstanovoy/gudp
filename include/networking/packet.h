#pragma once

#include <stddef.h>
#include <stdint.h>

#include "common/retcode.h"

const size_t kDataLength = 500;

typedef struct {
  void* ptr;
  size_t len;
} Data;

typedef enum {
  CONNECT,
  DISCONNECT,
} ResponseType;

typedef struct {
  ResponseType type;
  uint16_t len;
} PacketHeader;

typedef struct {
  ResponseType type;
  uint16_t client_id;
  Data data;
} Response;

RETCODE
DataInit(Data* data);

void DataDestroy(Data* data);

RETCODE
ResponseInit(Response* response);

void ResponseDestroy(Response* response);

void ResponseSetType(Response* response, ResponseType type);

ResponseType ResponseGetType(Response* response);

void ResponseSetClientId(Response* response, uint16_t client_id);

uint16_t ResponseGetClientId(Response* response);

RETCODE
GetResponseFromData(Data* in, Response* out);

RETCODE
GetDataFromResponse(Response* in, Data* out);
