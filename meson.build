# meson.build based on
# https://git.sr.ht/~nloomans/minishell/tree/master/meson.build

project('control1060', 'cpp', default_options : ['cpp_std=c++17'])

cc = meson.get_compiler('cpp')

hidapi = 'hidapi'
if host_machine.system() == 'linux'
	hidapi = 'hidapi-hidraw'
endif
dep_hidapi = dependency(hidapi)

#inc_dir = include_directories([
#    'inc',
#    'src',
#    fltk_include_dir
#])

control1060_deps = [
    dep_hidapi
]

control1060_src = files([
    'control1060.cpp'
])

executable('control1060',
    sources: control1060_src,
    #include_directories: inc_dir,
    dependencies: control1060_deps
)
