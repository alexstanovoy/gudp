#pragma once

/**
 * @brief      List of gudp functions return codes.
 */
typedef enum {
  /// Successiful return.
  SUCCESS = 0,
  /// SocketInit() error; WSAStartup != NO_ERROR.
  SOCKET_INIT_FAILURE,
  /// SocketShutdown() error; WSACleanup != NO_ERROR.
  SOCKET_CLEANUP_FAILURE,
  /// SocketInit() error; Socket cretion failed.
  SOCKET_INIT_FAILED,
  /// SocketDestroy() error; Socket closing failed.
  SOCKET_DESTROY_FAILED,
  /// SocketBind() error; Socket bind failed.
  SOCKET_BIND_FAILED,
  /// SocketConnect() error; Socket connect failed.
  SOCKET_CONNECT_FAILED,
  /// SocketSend() error; Sending failed.
  SOCKET_SEND_FAILED,
  /// SocketReceive() error; Receive failed.
  SOCKET_RECEIVE_FAILED,
  /// General error; malloc failed.
  NOT_ENOUGH_MEMORY,
  SERVER_USER_NOT_FOUND,
  SERVER_CROWDED,
  CLIENT_KICKED,
} RETCODE;
