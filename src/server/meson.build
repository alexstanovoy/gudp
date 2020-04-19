registrator = files('registrator.c')
project_sources += registrator
registrator_lib = library(
  'registrator',
  registrator,
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
    registrator_lib,
    packet_lib
  ],
  include_directories : inc
)

