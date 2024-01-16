project('pablo-plugin', 'c', default_options : ['c_std=gnu99'])

# Configuración de GStreamer
gstreamer_dep = dependency('gstreamer-1.0', version : '>=1.14.0')

# Configuración de la biblioteca compartida
shared_library('gzdec',
  sources : files('src/gst_plugin.c'),
  include_directories : 'src',
  dependencies : gstreamer_dep
)

