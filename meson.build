project('wf-simple-gaps-plugin', 'cpp', version: '1.0.0')
args = [
    '-DWLR_USE_UNSTABLE',
    '-DWAYFIRE_PLUGIN',
    '-D_FILE_OFFSET_BITS=64'
]

add_project_arguments(args, language: 'cpp')
add_project_link_arguments(['-rdynamic'], language: 'cpp')

wayfire = dependency('wayfire')
deps = [
    wayfire
]

sources = files(
    'src/main.cpp'
)

shared_module(
    'simple-gaps',
    sources: sources,
    dependencies: deps,

    install: true,
    install_dir: wayfire.get_variable(pkgconfig: 'plugindir')
)

install_data(
    'metadata/simple-gaps.xml',
    install_dir: wayfire.get_variable(pkgconfig: 'metadatadir'),
)
