project(
  'gudp',
  'c',
  default_options: [
    'warning_level=3',
    'buildtype=debugoptimized'
  ],
  version : '0.0.1',
  license: 'GPLv3'
)

defines = []

target_os = target_machine.system()
if target_os == 'linux'
  defines += [
    '-D__LINUX__',
    '-D__PLATFORM__=\"linux\"'
  ]
#elif target_os == 'windows'
#  defines += [
#    '-D__WINDOWS__',
#    '-D__PLATFORM__=\"windows\"'
#  ]
#elif target_os == 'darwin'
#  defines += [
#    '-D__DARWIN__',
#    '-D__PLATFORM__=\"darwin\"'
#  ]
else
  error('Current platform is not supported by gudp.')
endif

defines += [
  '-D__' + get_option('domain-type').to_upper() + '__',
  '-D__NETCODE__=' + get_option('domain-type')
]

project_sources = []
project_header_files = []
project_test_sources = []
inc = [
  include_directories('include')
]

add_project_arguments(defines, language: 'c')

subdir('src')

if get_option('enable-tests')
  inc += include_directories('tests')
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
      'docs/doxycfg/doxyfile'
    ]
  )
else
  warning('Doxygen was\'nt found. "generate-docs" target won\'t be added.')
endif
