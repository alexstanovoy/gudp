server_registrator = files('server_registrator.c')
project_sources += server_registrator
server_registrator_lib = library(
  'server_registrator',
  server_registrator,
  link_with: socket_lib,
  include_directories : inc
)

server = files('server.c')
project_sources += server
server_lib = library(
  'server',
  server,
  link_with: [
    socket_lib,
    server_registrator_lib,
    packet_lib
  ],
  include_directories : inc
)

