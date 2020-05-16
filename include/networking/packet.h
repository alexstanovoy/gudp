/**
 * @file packet.h
 *
 * @brief      Contains functions for working with packets that GUDP library
 *             instances (Server and Client) send and receive.
 *
 *             The core functions are DataToResponse() and ResponseToData().
 *             They make a valid readable Response from received RAW Data and
 *             compressed Data from Responce respectively.
 *
 * @author     Alexander Stanovoy
 */

#pragma once

#include <stddef.h>
#include <stdint.h>

#include "common/retcode.h"

/// Maximum packet size to send.
const size_t kDataLength;

/**
 * @brief      A pair of the pointer to the array and length of the array.
 */
typedef struct {
  /// The pointer to the array.
  char* ptr;
  /// The length of the array.
  size_t len;
} Data;

/**
 * @brief      A list of packet types.
 */
typedef enum {
  /// Connection packet. Also synchronization packet.
  CONNECT,
  /// Kick/Disconnect packet.
  DISCONNECT,
} ResponseType;

/**
 * @brief      A GUDP packet header.
 */
typedef struct {
  /// Type of the packet.
  ResponseType type;
  /// Length of the data.
  uint16_t len;
} PacketHeader;

/**
 * @brief      A GUDP response.
 */
typedef struct {
  /// Type of the response.
  ResponseType type;
  /// ID of client who sent the packet.
  uint16_t client_id;
  /// RAW data of packet.
  Data data;
} Response;

/**
 * @brief      Initializes the data with size kDataLength.
 *
 * @param      data  The pointer to the data.
 *
 * @return     SUCCESS if initialization is successiful, and NOT_ENOUGH_MEMORY
 *             when error occures.
 *
 * @since      0.0.1
 */
RETCODE
DataInit(Data* data);

/**
 * @brief      Destroys the data.
 *
 * @param      data  The pointer to the data.
 *
 * @since      0.0.1
 *
 * @note       It's guarranted DataDestroy() will work correctly after
 *             unsuccessiful SocketCreate().
 */
void DataDestroy(Data* data);

/**
 * @brief      Sets value for data from str string.
 *
 * @param      data  The pointer to the data.
 * @param[in]  str   The pointer to the string.
 *
 * @since      0.0.1
 */
void DataSet(Data* data, const char* str);

/**
 * @brief      Initializes the response by size kDataLength.
 *
 * @param      response  The pointer to the response.
 *
 * @return     SUCCESS if initialization is successiful, and NOT_ENOUGH_MEMORY
 *             when error occures.
 *
 * @since      0.0.1
 */
RETCODE
ResponseInit(Response* response);

/**
 * @brief      Destroys the response.
 *
 * @param      response  The pointer to the response.
 *
 * @since      0.0.1
 *
 * @note       It's guaranteed ResponseDestroy() will work correctly after
 *             unsuccessful ResponseInit().
 */
void ResponseDestroy(Response* response);

/**
 * @brief      Sets the data in response using provided string.
 *
 * @param      response  The pointer to the response.
 * @param[in]  str       The pointer to the string.
 *
 * @since      0.0.1
 */
void ResponseSetData(Response* response, const char* str);

/**
 * @brief      Sets the type of response.
 *
 * @param      response  The pointer to the response.
 * @param[in]  type      The new type of response.
 *
 * @since      0.0.1
 */
void ResponseSetType(Response* response, ResponseType type);

/**
 * @brief      Gets the response type.
 *
 * @param      response  The pointer to the response.
 *
 * @return     The response type.
 *
 * @since      0.0.1
 */
ResponseType ResponseGetType(Response* response);

/**
 * @brief      Sets the client ID in response
 *
 * @param      response   The pointer to the response.
 * @param[in]  client_id  The client identifier.
 *
 * @since      0.0.1
 */
void ResponseSetClientId(Response* response, uint16_t client_id);

/**
 * @brief      Gets the client ID in the response.
 *
 * @param      response  The pointer to the response.
 *
 * @return     The client identifier.
 *
 * @since      0.0.1
 */
uint16_t ResponseGetClientId(Response* response);

/**
 * @brief      Converts the RAW data to response.
 *
 * @param      in    The pointer to the input Data.
 * @param      out   The pointer to the output Response.
 *
 * @return     SUCCESS.
 *
 * @since      0.0.1
 */
RETCODE
DataToResponse(Data* in, Response* out);

/**
 * @brief      Converts the response to the RAW data.
 *
 * @param      in    The pointer to the input Response.
 * @param      out   The pointer to the output Data.
 *
 * @return     SUCCESS.
 *
 * @since      0.0.1
 */
RETCODE
ResponseToData(Response* in, Data* out);
