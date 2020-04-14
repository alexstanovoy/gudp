server = files('server.c')
project_sources += server
server_lib = library(
  'server',
  server,
  link_with: socket_lib,
  include_directories : inc
)

server_registrator = files('server_registrator.c')
project_sources += server_registrator
server_registrator_lib = library(
  'server_registrator',
  server_registrator,
  include_directories : inc
)

server_handler = files('server_handler.c')
project_sources += server_handler
server_handler_lib = library(
  'server_handler',
  server_handler,
  link_with: [
    socket_lib,
    packet_lib,
    server_registrator_lib
  ],
  include_directories : inc
)
