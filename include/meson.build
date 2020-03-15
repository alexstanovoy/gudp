dependencies = []
c_compiler = meson.get_compiler('c')
incdirs = include_directories('.')
target_os = target_machine.system()

sources = []

gudp = static_library(
  'gudp',
  sources,
  include_directories: incdirs,
  dependencies: dependencies
)
