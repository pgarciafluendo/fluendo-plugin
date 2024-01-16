#include <gst/gst.h>

#define GST_TYPE_MYELEMENT gst_my_element_get_type()
G_DECLARE_FINAL_TYPE (GstMyElement, gst_my_element, GST, MYELEMENT, GstElement)

// El objeto y sus atributos
struct _GstMyElement
{
  GstElement element;
};

#define gst_my_element_parent_class parent_class
G_DEFINE_TYPE (GstMyElement, gst_my_element, GST_TYPE_ELEMENT);

GST_ELEMENT_REGISTER_DEFINE (my_element, "my_element", GST_RANK_NONE,
    GST_TYPE_MYELEMENT);

// Inicialización del tipo (métodos virtuales, metadatos, etc)
static void
gst_my_element_class_init (GstMyElementClass * klass)
{
  GstElementClass *gstelement_class = GST_ELEMENT_CLASS (klass);
  gst_element_class_set_details_simple (gstelement_class,
      "MyElement",
      "Video:Generic",
      "Video:Generic Template Element",
      "User <<user@hostname.org>>"
  );
}

// Inicialización del objeto (seteo de atributos, etc)
static void
gst_my_element_init (GstMyElement * filter)
{
}

// Registro del plugin
static gboolean
plugin_init (GstPlugin * myelement)
{
  return GST_ELEMENT_REGISTER (my_element, myelement);
}

#define PACKAGE "example"
GST_PLUGIN_DEFINE (GST_VERSION_MAJOR,
    GST_VERSION_MINOR,
    gzdec, //Changed from myelement to gzdec to make it work
    "my_element",
    plugin_init,
    "0.1",
    "LGPL",
    "GStreamer",
    "https://fluendo.com"
    )
