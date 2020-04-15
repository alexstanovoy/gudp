client = files('client.c')
project_sources += client
client_lib = library(
  'client',
  client,
  link_with: [
    socket_lib,
    packet_lib
  ],
  include_directories : inc
)
