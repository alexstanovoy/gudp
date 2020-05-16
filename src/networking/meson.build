packet = files('packet.c')
packet_lib = static_library(
  'packet',
  packet,
  include_directories : inc
)
libs += packet_lib

socket = files('socket.c')
socket_lib = static_library(
  'socket',
  socket,
  include_directories : inc
)
libs += socket_lib
