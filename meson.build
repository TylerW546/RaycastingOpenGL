project('Raycaster', ['cpp','c'],
  version : '0.1',
  default_options : ['warning_level=3', 'cpp_std=c++14'])

project_dir = meson.current_source_dir()
build_dir = meson.current_build_dir()



cpp = meson.get_compiler('cpp')
c = meson.get_compiler('c')

source_files = ['main.cpp', 'source/Character.cpp', 'source/Entity.cpp', 'source/Game.cpp', 'source/Map.cpp', 'source/Interface.cpp', 'source/Raycaster.cpp', 'source/Textures.cpp', 'source/MarchingMap/src/Environment.cpp', 'source/MarchingMap/src/NodeMap.cpp', 'source/MarchingMap/src/Square.cpp']

host_system = host_machine.system()
if host_system == 'windows'
  inc = [include_directories('include'), include_directories('C:/include'),include_directories('C:/Libraries/include'), include_directories('source/MarchingMap/include')]
  deps = [cpp.find_library('glBase', dirs : 'C:/lib')]

  install_subdir(project_dir / 'shaders', install_dir: build_dir, strip_directory : false)
  install_subdir(project_dir / 'sprites', install_dir: build_dir, strip_directory : false)
  install_data('C:/share/OpenGL/glfw3.dll', install_dir: build_dir)
  install_data('C:/bin/libglBase.dll', install_dir: build_dir)
elif host_system == 'darwin'
  inc = [include_directories('include'), include_directories('/usr/local/include'),include_directories('/usr/local/Libraries/include'), include_directories('source/MarchingMap/include')]
  deps = [cpp.find_library('glBase', dirs : '/usr/local/lib')]

  install_subdir(project_dir / 'shaders', install_dir: build_dir, strip_directory : false)
  install_subdir(project_dir / 'sprites', install_dir: build_dir, strip_directory : false)
  install_data('/usr/local/share/OpenGL/glfw3.dll', install_dir: build_dir)
endif

exe = executable('Raycaster', source_files,
    include_directories : inc,
    dependencies : deps)
    #install : true)