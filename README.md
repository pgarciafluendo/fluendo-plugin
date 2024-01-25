INSPECT PLUGIN:
> gst-inspect-1.0 --gst-plugin-load=builddir/src/libgstmyelement.so plugin_pablo


RUN A BASIC PIPELINE WITH IT:
If you have added the lib to the GStreamer path  (export GST_PLUGIN_PATH=rute-to-plugin-lib:$GST_PLUGIN_PATH):
> gst-launch-1.0 filesrc location=test/test.txt ! plugin_pablo operation=identity ! filesink location=test/output.txt

If not:
> gst-launch-1.0 filesrc location=test/test.txt ! --gst-plugin-load=builddir/src/libgstplugin.so plugin_pablo operation=identity ! filesink location=test/output.txt

Remembert that 3 basic operations are available:
- operation=identity:bypasses the text
- operation=toupper: text converted to upper case
- operation=tolower: text converted to lower case
