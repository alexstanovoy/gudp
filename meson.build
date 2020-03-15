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

inc = [include_directories('include')]

subdir('src')

if get_option('enable-tests')
  subdir('tests')
endif

doxygen = find_program('doxygen')
generate_docs = run_target(
  'docs',
  command: [
    doxygen,
    'config/doxygen.cfg'
  ]
)

configure_file(
  input : '.clang-format',
  output : '.clang-format',
  copy: true
)
run_target(
  'format',
  command : [
    'clang-format',
    '-i',
    '-style=file',
    project_sources,
    project_test_sources,
    project_header_files
  ]
)
