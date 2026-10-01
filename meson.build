project(
	'wf-simple-gaps-plugin',
        'c',
	'cpp',
	version: '0.0',
	license: 'MIT',
	meson_version: '>=0.51.0',
	default_options: [
		'cpp_std=c++17',
                'c_std=c99',
		'werror=false',
	],
)

wayfire = dependency('wayfire', version: '>=0.11.0')

project_args = ['-DWLR_USE_UNSTABLE']
add_project_arguments(project_args, language: ['cpp', 'c'])

subdir('src')
subdir('metadata')
