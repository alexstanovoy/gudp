/**
 * @file retcode.h
 *
 * @brief      Contains enum with GUDP return codes.
 *
 * @author     Alexander Stanovoy
 */

#pragma once

/**
 * @brief      List of gudp functions return codes.
 */
typedef enum {
  /// Successiful return.
  SUCCESS = 0,
  /// General error; malloc() failed.
  NOT_ENOUGH_MEMORY = 1,
  /// SocketsStartup() error; WSAStartup() != NO_ERROR.
  SOCKET_STARTUP = 2,
  /// SocketsShutdown() error; WSACleanup() != NO_ERROR.
  SOCKET_SHUTDOWN = 3,
  /// SocketInit() error; Socket cretion failed.
  SOCKET_INIT = 4,
  /// SocketBind() error; Socket bind failed.
  SOCKET_BIND = 5,
  /// SocketConnect() error; Socket connect failed.
  SOCKET_CONNECT = 6,
  /// SocketSend() error; Sending failed.
  SOCKET_SEND = 7,
  /// SocketReceive() error; Receive failed.
  SOCKET_RECEIVE = 8,
  SOCKET_MAKE_NONBLOCKING = 9,
  /// SocketReceive() error; Returned after timeout reached. See
  /// SocketSetTimeout() for details.
  SOCKET_TIMEOUT = 10,
  /// SocketSetTimeout() error; Setting failed.
  SOCKET_SETTIMEOUT = 11,
  /// Server cannot find specified user id.
  SERVER_USER_NOT_FOUND = 12,
  /// Server tried to accept connection but there were no place in server.
  SERVER_CROWDED = 13,
  /// Client received disconnect packet while in action.
  CLIENT_KICKED = 14,
} RETCODE;
