/**
 * @file packet.h
 *
 * @brief      Contains functions for packing GUDP packets to regular UDP
 *             messages and unpacking from messages to GUDP packets.
 *
 *             The main difference between real-time games and many other
 *             applications is that games send **time critical data**. We don't
 *             care about missing packages because they contain outdated
 *             information, and it's better to move forward rather than send
 *             packet again and wait. That's the reason why games send packets
 *             only once. The project uses approach proposed by [Glenn
 *             Fiedler](https://gafferongames.com/post/reliable_ordered_messages/)
 *             for reliable in-game connections.
 *
 *             The structure of the header is following:
 *
 *             * 4-bit `packet_type` bit field for marking this packet as
 * encrypted, compressed, synchronization packet, etc.
 *             * 16-byte `packet_id` for packet identificating. If the packet
 * was already processed (it's duplicate or broken) -- packet is skipped.
 *             * 16-byte `len` shows information about data length.
 *             * 32-byte `ack` bit field shows if the acknowledgment for 32
 * previous packets was received.
 */

#pragma once

#include <stddef.h>
#include <stdint.h>

#include "common/retcode.h"

/**
 * @brief      A pair of data array pointer and data length.
 */
typedef struct {
  /// The pointer to the data.
  char* ptr;
  /// The data length.
  size_t len;
} Data;

/**
 * @brief      A GUDP library packet header.
 */
typedef struct {
  uint16_t packet_type : 2;
  uint16_t encryption_type : 2;
  uint16_t compression_type : 2;
  uint16_t packet_id;
  uint16_t len;
  uint32_t ack;
} PacketHeader;

/**
 * @brief      A GUDP library packet.
 */
typedef struct {
  /// The header.
  PacketHeader header;
  /// The packet.
  Data data;
} Packet;

typedef enum {
  SYNC,
  CONNECT,
  OVERHEAD,
  DISCONNECT,
} ResponseType;

typedef struct {
  ResponseType response_type;
  uint16_t client_id;
  Data data;
} Response;

RETCODE
DataInit(Data* data);

void DataDestroy(Data* data);

RETCODE
PacketInit(Packet* packet);

void PacketDestroy(Packet* packet);

RETCODE
ResponseInit(Response* packet);

void ResponseDestroy(Response* packet);

RETCODE
GetResponseFromData(Data* in, Response* out);

RETCODE
GetDataFromResponse(Response* in, Data* out);
