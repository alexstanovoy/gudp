#include "networking/packet.h"

#include "common/macro.h"
#include "common/retcode.h"

RETCODE
DataInit(Data* data) {
}

void DataDestroy(Data* data) {
}

RETCODE
PacketInit(Packet* packet) {
}

void PacketDestroy(Packet* packet) {
}

RETCODE
ResponseInit(Response* packet) {
}

void ResponseDestroy(Response* packet) {
}

RETCODE
GetResponseFromData(Data* in, Response* out) {
}

RETCODE
GetDataFromResponse(Response* in, Data* out) {
}
