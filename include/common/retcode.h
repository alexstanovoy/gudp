#pragma once

/**
 * @brief      List of gudp functions return codes.
 */
typedef enum gudp_retcodes {
  /// Successiful return.
  SUCCESS = 0,
  /// SocketInit() error; WSAStartup != NO_ERROR.
  SOCKET_INIT_FAILURE = 1,
  /// SocketShutdown() error; WSACleanup != NO_ERROR.
  SOCKET_CLEANUP_FAILURE = 2,
  /// SocketCreate() error; Socket cretion failed.
  SOCKET_CREATION_FAILED = 3,
  /// SocketClose() error; Socket closing failed.
  SOCKET_CLOSING_FAILED = 4,
  /// SocketBind() error; Socket bind failed.
  SOCKET_BIND_FAILED = 5,
  /// SocketConnect() error; Socket connect failed.
  SOCKET_CONNECT_FAILED = 6,
  /// SocketSend() and SocketSendTo() error; Sending failed.
  SOCKET_SENDTO_FAILED = 7,
  /// SocketReceive() and SocketReceiveFrom() error; Receive failed.
  SOCKET_RECEIVEFROM_FAILED = 8,
  /// ClientInit() failed; Init failed.
  CLIENT_INIT_FAILED = 9,
  /// ClientDestroy() failed; Destroy failed.
  CLIENT_DESTROY_FAILED = 10,
  /// ClientReceive() failed; Receive failed.
  CLIENT_RECEIVE_FAILED = 11,
  /// ClientSend() failed; Send failed.
  CLIENT_SEND_FAILED = 12,
  /// ServerInit() failed; Init failed.
  SERVER_INIT_FAILURE = 13,
  /// ServerDestroy() failed; Destroy failed.
  SERVER_DESTROY_FAILURE = 14,
  /// ServerReceiveFrom() failed; Receive from failed.
  SERVER_RECEIVEFROM_FAILED = 15,
  /// ServerReceive() failed; Receive failed.
  SERVER_RECEIVE_FAILED = 16,
  /// ServerSendTo() failed; Send to failed.
  SERVER_SENDTO_FAILED = 17,
  /// ServerSend() failed; Send failed.
  SERVER_SEND_FAILED = 18,
} RETCODE;
