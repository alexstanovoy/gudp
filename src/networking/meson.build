packet = files('packet.c')
packet_lib = library(
  'packet',
  packet,
  include_directories : inc
)
libs += packet_lib

socket = files('socket.c')
socket_lib = library(
  'socket',
  socket,
  include_directories : inc
)
libs += socket_lib
