#pragma once

#include <stdio.h>
#include <stdlib.h>

#include "common/retcode.h"

void Throw(char* msg, int line) {
  fprintf(stderr, "[line %d] ERROR: %s\n", line, msg);
  exit(EXIT_FAILURE);
}

#define ThrowThis(errline) \
  Throw((errline), line);  \
  break;

void TryThrow(RETCODE result, int line) {
  switch (result) {
    case SUCCESS: {
      break;
    }
    case NOT_ENOUGH_MEMORY: {
      ThrowThis("General error; malloc() failed.");
    }
    case SOCKET_STARTUP: {
      ThrowThis("SocketStartup() error; WSAStartup() != NO_ERROR.");
    }
    case SOCKET_SHUTDOWN: {
      ThrowThis("SocketsShutdown() error; WSACleanup() != NO_ERROR.");
    }
    case SOCKET_INIT: {
      ThrowThis("SocketInit() error; Socket cretion failed.");
    }
    case SOCKET_BIND: {
      ThrowThis("SocketBind() error; Socket bind failed.");
    }
    case SOCKET_CONNECT: {
      ThrowThis("SocketConnect() error; Socket connect failed.");
    }
    case SOCKET_SEND: {
      ThrowThis("SocketSend() error; Sending failed.");
    }
    case SOCKET_RECEIVE: {
      ThrowThis("SocketReceive() error; Receive failed.");
    }
    case SOCKET_TIMEOUT: {
      ThrowThis(
          "SocketReceive() error; Returned after timeout reached. See "
          "SocketSetTimeout() for details.");
    }
    case SOCKET_SETTIMEOUT: {
      ThrowThis("SocketSetTimeout() error; Setting failed.");
    }
    case SERVER_USER_NOT_FOUND: {
      ThrowThis("Server cannot find specified user id.");
    }
    case SERVER_CROWDED: {
      ThrowThis(
          "Server tried to accept connection but there were no place in "
          "server.");
    }
    case CLIENT_KICKED: {
      ThrowThis("Client received disconnect packet while in action.");
    }
    default: {
      ThrowThis("Unhandled retcode!");
    }
  }
}

#define Panic(func) TryThrow((func), __LINE__)