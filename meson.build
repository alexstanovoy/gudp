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
else
  error('Current platform is not supported by gudp.')
endif

defines += [
  '-D__' + get_option('domain-type').to_upper() + '__',
  '-D__NETCODE__=' + get_option('domain-type')
]

libs = []
inc = [
  include_directories('include')
]

add_project_arguments(defines, language: 'c')

subdir('src')

gudp_dep = declare_dependency(
  include_directories: inc,
  link_with: libs
)

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
