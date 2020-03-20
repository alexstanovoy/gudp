if target_os == 'linux'
  socket = files('socket_linux.c')
endif

project_sources += socket
socket_lib = static_library(
  'socket',
  socket,
  include_directories : inc
)
