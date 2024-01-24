
project('gst-template', 'c', version : '1.19.0.1', license : 'LGPL')

plugins_install_dir = join_paths(get_option('libdir'), 'gstreamer-1.0')

cc = meson.get_compiler('c')

gst_version = meson.project_version()

api_version = '1.0'

gst_dep = dependency('gstreamer-1.0', version : '>=1.19',
    required : true, fallback : ['gstreamer', 'gst_dep'])
gstbase_dep = dependency('gstreamer-base-1.0', version : '>=1.19',
    fallback : ['gstreamer', 'gst_base_dep'])

subdir('src')




#project('fluendo-test-pablo', 'c', default_options : ['c_std=gnu99'])

# Configuración de GStreamer
#dependencies = []
#dependencies += dependency('gstreamer-1.0')
#dependencies += dependency('gstreamer-base-1.0')

# Configuración de la biblioteca compartida
#gst_template = shared_library('gst-template',
#  sources : files('src/gstplugin.c'),
#  include_directories : 'src',
#  dependencies : dependencies
#)


