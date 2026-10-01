shared_module(
    'simple-gaps',
    sources: files(
        'main.cpp',
    ),

    dependencies: [
        wayfire,
    ],

    install: true,
    install_dir: wayfire.get_variable(pkgconfig: 'plugindir'),

    name_prefix: 'lib',

    cpp_args: [
        '-D_FILE_OFFSET_BITS=64',
    ],
)
