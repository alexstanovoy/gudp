if target_os == 'linux'
  udplowlevel = files('udplowlevel_linux.c')
endif

project_sources += udplowlevel
udplowlevel_lib = static_library(
  'udplowlevel',
  udplowlevel,
  include_directories : inc
)
