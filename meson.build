project('_pyne', 'c')

py = import('python').find_installation(pure: false)

sources = ['_pyne/_pyne.c', '_pyne/window.c', '_pyne/event.c', '_pyne/image.c']
pysources = ['_pyne/stubs/__init__.pyi']

dependencies = [dependency('sdl2'), dependency('sdl2_image')]

py.extension_module(
'_pyne',
  sources: sources,
  dependencies: dependencies,
  install: true,
)

py.install_sources(pysources, subdir: '_pyne')

new_pysources = ['pyne/__init__.py', 'pyne/display.py', 'pyne/event.py']

py.install_sources(new_pysources, subdir: 'pyne')
