project('pyne', 'c')

py = import('python').find_installation(pure: false)

sources = []
pysources = []

dependencies = [dependency('sdl2')]

py.extension_module(
  '_pyne',
  sources: sources,
  dependencies: dependencies,
  install: true,
)


py.install_sources(pysources, subdir: '_pyne')
