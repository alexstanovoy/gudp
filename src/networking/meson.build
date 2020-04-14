packet = files('packet.c')
project_sources += packet
packet_lib = library(
  'packet',
  packet,
  include_directories : inc
)

socket = files('socket.c')
project_sources += socket
socket_lib = library(
  'socket',
  socket,
  include_directories : inc
)
