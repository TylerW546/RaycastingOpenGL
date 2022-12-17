project('Raycaster', ['cpp','c'],
  version : '0.1',
  default_options : ['warning_level=3', 'cpp_std=c++14'])

project_dir = meson.current_source_dir()
build_dir = meson.current_build_dir()

inc = [include_directories('include')]

cpp = meson.get_compiler('cpp')
c = meson.get_compiler('c')

source_files = ['main.cpp', 'source/Character.cpp', 'source/Entity.cpp', 'source/Game.cpp', 'source/Map.cpp', 'source/Interface.cpp', 'source/Raycaster.cpp', 'source/Textures.cpp']

deps = [cpp.find_library('glBase')]

install_subdir(project_dir / 'shaders', install_dir: build_dir, strip_directory : false)
install_subdir(project_dir / 'sprites', install_dir: build_dir, strip_directory : false)
# install_data('C://share/OpenGL/glfw3.dll', install_dir: build_dir)
# install_data('C://bin/libglBase.dll', install_dir: build_dir)

exe = executable('Raycaster', source_files,
    include_directories : inc,
    dependencies : deps)
    #install : true)