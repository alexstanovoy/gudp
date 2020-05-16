registrator = files('registrator.c')
registrator_lib = static_library(
  'registrator',
  registrator,
  link_with: socket_lib,
  include_directories : inc
)
libs += registrator_lib

server = files('server.c')
server_lib = static_library(
  'server',
  server,
  link_with: [
    socket_lib,
    registrator_lib,
    packet_lib
  ],
  include_directories : inc
)
libs += server_lib
