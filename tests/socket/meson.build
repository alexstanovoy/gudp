sockets_test = executable(
  'sockets_test',
  files('test.c'),
  link_with: [
    socket_lib,
    packet_lib
  ],
  include_directories: inc
)
test(
  'Sockets basic IO test',
  sockets_test
)
