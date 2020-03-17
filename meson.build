project(
  'gudp',
  'c',
  default_options: [
    'warning_level=3',
    'buildtype=debugoptimized',
    'cpp_std=c++11'
  ],
  version : '0.0.1',
  license: 'GPLv3'
)

defines = []
target_os = target_machine.system()
if target_os == 'linux'
  defines += [ '-DPLATFORM_LINUX' ]
#elif target_os == 'windows'
#  defines += [ '-DPLATFORM_WINDOWS' ]
#elif target_os == 'darwin'
#  defines += [ '-DPLATFORM_MAC' ]
else
  error('Current platform is not supported by gudp.')
endif

project_sources = []
project_header_files = []
project_test_sources = []

inc = [ include_directories('include') ]

subdir('src')

if get_option('enable-tests')
  subdir('tests')
endif

doxygen = find_program(
  'doxygen',
  required: false
)
if doxygen.found()
  generate_docs = run_target(
    'generate-docs',
    command: [
      doxygen,
      'doxyfile'
    ]
  )
else
  warning('Doxygen was\'nt found. "generate-docs" target won\'t be added')
endif
