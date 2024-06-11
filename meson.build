project('_pyne', 'c')

py = import('python').find_installation(pure: false)

sources = ['_pyne/_pyne.c', '_pyne/window.c']
pysources = ['_pyne/stubs/__init__.pyi']

dependencies = [dependency('sdl2')]

py.extension_module(
  '_pyne',
  sources: sources,
  dependencies: dependencies,
  install: true,
)

py.install_sources(pysources, subdir: '_pyne')
# Finish later when we finish the python module

new_pysources = ['pyne/__init__.py', 'pyne/display.py']

py.install_sources(new_pysources, subdir: 'pyne')
