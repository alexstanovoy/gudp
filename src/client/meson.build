client = files('client.c')
client_lib = library(
  'client',
  client,
  link_with: [
    socket_lib,
    packet_lib
  ],
  include_directories : inc
)
libs += client_lib
