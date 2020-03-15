#pragma once

/**
 * @brief      List of gudp return codes.
 */
typedef enum retcode {
  /// Successiful return.
  SUCCESS = 0,
  /// InitializeSockets() error; WSAStartup != NO_ERROR.
  WINSOCK_INIT_FAILURE = -1,
  /// ShutdownSockets() error; WSACleanup != NO_ERROR.
  WINSOCK_CLEANUP_FAILURE = -2,
  /// CreateSocket() error; Socket cretion failed.
  SOCKET_CREATION_FAILED = -3,
  /// CloseSocket() error; Socket closing failed.
  SOCKET_CLOSING_FAILED = -4,
  /// BindSocket() error; Socket bind failed.
  SOCKET_BIND_FAILED = -5,
  /// ConnectSocket() error; Socket connect failed.
  SOCKET_CONNECT_FAILED = -6,
  /// SendMessage() error; Sending failed.
  SOCKET_SEND_FAILED = -7,
  /// SendMessage() error; Not all bytes were send.
  SOCKET_SEND_LESSLEN = -8,
} RETCODE;
