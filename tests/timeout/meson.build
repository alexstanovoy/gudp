timeout_test = executable(
  'timeout_test',
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
  'Timeout test',
  timeout_test
)
