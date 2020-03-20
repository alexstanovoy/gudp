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
 *             * 16-byte `flags` bit field for marking this packet as encrypted,
 * compressed, synchronization packet, etc.
 *             * 16-byte `client_num` for identificating client. Note that
 * currently `GUDP` checks IP and port of the client before processing too.
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
 * @brief      A GUDP library packet header. See packet.h detailed
 *             description for more information.
 */
typedef struct gudp_packet_header_t {
  uint16_t flags;
  uint16_t client_num;
  uint16_t packet_id;
  uint16_t len;
  uint32_t ack;
} PacketHeader;

/**
 * @brief      A pair of data array pointer and data length.
 */
typedef struct gudp_data_t {
  /// The pointer to the data.
  void* data;
  /// The data length.
  size_t len;
} Data;

/**
 * @brief      Adds a GUDP packet header at the beginning of the RAW data and
 *             writes result to "out" operand.
 *
 * @param      in      The pointer to the RAW data to send.
 * @param      out     The pointer to the GUDP packet header.
 * @param      header  The GUDP packet header.
 *
 * @todo       Explain return values.
 *
 * @return     TODO.
 */
RETCODE
MakePacket(Data* in, Data* out, PacketHeader* header);
