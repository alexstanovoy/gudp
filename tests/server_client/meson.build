server_client_test = executable(
  'server_client_test',
  files('test.c'),
  link_with: [
    socket_lib,
    packet_lib,
    server_lib,
    client_lib
  ],
  include_directories: inc
)
test(
  'Server-client basic IO test',
  server_client_test
)
