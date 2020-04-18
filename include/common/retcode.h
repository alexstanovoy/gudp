#pragma once

/**
 * @brief      List of gudp functions return codes.
 */
typedef enum {
  /// Successiful return.
  SUCCESS = 0,
  /// General error; malloc() failed.
  NOT_ENOUGH_MEMORY,
  /// SocketStartup() error; WSAStartup() != NO_ERROR.
  SOCKET_STARTUP,
  /// SocketsShutdown() error; WSACleanup() != NO_ERROR.
  SOCKET_SHUTDOWN,
  /// SocketInit() error; Socket cretion failed.
  SOCKET_INIT,
  /// SocketBind() error; Socket bind failed.
  SOCKET_BIND,
  /// SocketConnect() error; Socket connect failed.
  SOCKET_CONNECT,
  /// SocketSend() error; Sending failed.
  SOCKET_SEND,
  /// SocketReceive() error; Receive failed.
  SOCKET_RECEIVE,
  /// SocketReceive() error; Returned after timeout reached. See SocketSetTimeout() for details.
  SOCKET_TIMEOUT,
  /// SocketSetTimeout() error; Setting failed.
  SOCKET_SETTIMEOUT,
  /// Server cannot find specified user id.
  SERVER_USER_NOT_FOUND,
  /// Server tried to accept connection but there were no place in server.
  SERVER_CROWDED,
  /// Client received disconnect packet while in action.
  CLIENT_KICKED,
} RETCODE;
