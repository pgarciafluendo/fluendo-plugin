

/**
 * SECTION:element-plugin
 *
 * FIXME:Describe plugin here.
 *
 * <refsect2>
 * <title>Example launch line</title>
 * |[
 * gst-launch -v -m fakesrc ! plugin ! fakesink silent=TRUE
 * ]|
 * </refsect2>
 */




#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif
#include <gst/gst.h>
#include "gstplugin.h"

//Definition of a debugging category
GST_DEBUG_CATEGORY_STATIC (gst_plugin_template_debug);
#define GST_CAT_DEFAULT gst_plugin_template_debug


//Definition of signals its and propierties
/* Filter signals and args */
enum
{
  /* FILL ME */
  LAST_SIGNAL
};

enum
{
  PROP_0,
  PROP_SILENT
};


//Templates for the pads (source and sink)
/* the capabilities of the inputs and outputs.
 *
 * describe the real formats here.
 */
// Templates for the pads (source and sink)
static GstStaticPadTemplate sink_factory = GST_STATIC_PAD_TEMPLATE ("sink",
    GST_PAD_SINK, //Type of pad (in this case, a sink)
    GST_PAD_ALWAYS, //PAd will always be present
    GST_STATIC_CAPS ("text/plain") //Capacities of the pad (in this case, it accepts text)
);

static GstStaticPadTemplate src_factory = GST_STATIC_PAD_TEMPLATE ("src",
    GST_PAD_SRC,
    GST_PAD_ALWAYS,
    GST_STATIC_CAPS ("text/plain")
);


//Implementation of the type of element: GstPluginTemplate
#define gst_plugin_template_parent_class parent_class
G_DEFINE_TYPE (GstPluginTemplate, gst_plugin_template, GST_TYPE_ELEMENT); //Definition of the type
GST_ELEMENT_REGISTER_DEFINE (plugin_template, "plugin_template", GST_RANK_NONE, //Registration of the element (plugin)
    GST_TYPE_PLUGIN_TEMPLATE);


//Handling propierties
static void gst_plugin_template_set_property (GObject * object, //Set property
    guint prop_id, const GValue * value, GParamSpec * pspec);
static void gst_plugin_template_get_property (GObject * object, //Get property
    guint prop_id, GValue * value, GParamSpec * pspec);


static gboolean gst_plugin_template_sink_event (GstPad * pad,
    GstObject * parent, GstEvent * event);
static GstFlowReturn gst_plugin_template_chain (GstPad * pad,
    GstObject * parent, GstBuffer * buf);



/* GObject vmethod implementations */

/* initialize the plugin's class */
//Class initializing
static void
gst_plugin_template_class_init (GstPluginTemplateClass * klass)
{
  GObjectClass *gobject_class;
  GstElementClass *gstelement_class;

  //These lines "associate" the GstPluginTemplateClass class to GObjectClass and GstElementClass ir order to access their methods
  gobject_class = (GObjectClass *) klass;
  gstelement_class = (GstElementClass *) klass;

  gobject_class->set_property = gst_plugin_template_set_property;
  gobject_class->get_property = gst_plugin_template_get_property;

  //Property: produces verbose info
  g_object_class_install_property (gobject_class, PROP_SILENT,
      g_param_spec_boolean ("silent", "Silent", "Produce verbose output ?",
          FALSE, G_PARAM_READWRITE));

  gst_element_class_set_details_simple (gstelement_class,
      "Plugin",
      "FIXME:Generic",
      "FIXME:Generic Template Element", "AUTHOR_NAME AUTHOR_EMAIL");

  //Adds the sink&source templates to the GstElement class 
  gst_element_class_add_pad_template (gstelement_class,
      gst_static_pad_template_get (&src_factory));
  gst_element_class_add_pad_template (gstelement_class,
      gst_static_pad_template_get (&sink_factory));
}


/* initialize the new element
 * instantiate pads and add them to element
 * set pad callback functions
 * initialize instance structure
 */
//Instance initializing
static void
gst_plugin_template_init (GstPluginTemplate * filter)
{
  //Creates a new sink pad based on the static template sink_factory
  filter->sinkpad = gst_pad_new_from_static_template (&sink_factory, "sink");

  //Establishes the function for events in the sink
  gst_pad_set_event_function (filter->sinkpad, GST_DEBUG_FUNCPTR (gst_plugin_template_sink_event));

  //Establishes the chain function for the pad
  gst_pad_set_chain_function (filter->sinkpad, GST_DEBUG_FUNCPTR (gst_plugin_template_chain));

  //Establishes proxy capabilities of the pad (pad adapting automatically to the connected pad)
  GST_PAD_SET_PROXY_CAPS (filter->sinkpad); gst_element_add_pad (GST_ELEMENT (filter), filter->sinkpad);

  //Creates a new pad for sending the data
  filter->srcpad = gst_pad_new_from_static_template (&src_factory, "src");

  //Proxy capabilities for the data pad
  GST_PAD_SET_PROXY_CAPS (filter->srcpad); gst_element_add_pad (GST_ELEMENT (filter), filter->srcpad);

  //Filter property (see gst_plugin_template_class_init)
  filter->silent = FALSE; //If silent=true, no modification will happen (see chain)
}

//Functions that allow writting/reading the "silent" property in instances of GstPluginTemplate
static void
gst_plugin_template_set_property (GObject * object, guint prop_id,
    const GValue * value, GParamSpec * pspec)
{
  GstPluginTemplate *filter = GST_PLUGIN_TEMPLATE (object);

  switch (prop_id) {
    case PROP_SILENT:
      filter->silent = g_value_get_boolean (value);
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
  }
}

static void
gst_plugin_template_get_property (GObject * object, guint prop_id,
    GValue * value, GParamSpec * pspec)
{
  GstPluginTemplate *filter = GST_PLUGIN_TEMPLATE (object);

  switch (prop_id) {
    case PROP_SILENT:
      g_value_set_boolean (value, filter->silent);
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
  }
}



/* GstElement vmethod implementations */

/* this function handles sink events */


// Sink event function 
static gboolean gst_plugin_template_sink_event (GstPad * pad, GstObject * parent,
    GstEvent * event)
{
  GstPluginTemplate *filter;
  gboolean ret;

  filter = GST_PLUGIN_TEMPLATE (parent);

  GST_LOG_OBJECT (filter, "Received %s event: %" GST_PTR_FORMAT,
      GST_EVENT_TYPE_NAME (event), event);

  switch (GST_EVENT_TYPE (event)) {
    case GST_EVENT_CAPS:
    {
      GstCaps *caps;

      gst_event_parse_caps (event, &caps);
      /* do something with the caps */
      //Place where the event should be handled

      /* and forward */
      ret = gst_pad_event_default (pad, parent, event);
      break;
    }
    default: //For the rest of the cases, does the default action
      ret = gst_pad_event_default (pad, parent, event);
      break;
  }
  return ret;
}


/* chain function
 * this function does the actual processing: VERY IMPORTANT ONE!!!!!!!
 */
// Chain function (new)
static GstFlowReturn gst_plugin_template_chain (GstPad * pad, GstObject * parent,
    GstBuffer * buf)
{
  GstPluginTemplate *filter;

  filter = GST_PLUGIN_TEMPLATE (parent);

  if (filter->silent == FALSE)
    g_print ("Here the text modification must happen.\n"); //Modifies text

  /* just push out the incoming buffer without touching it */
  return gst_pad_push (filter->srcpad, buf);
}



/* entry point to initialize the plug-in
 * initialize the plug-in itself
 * register the element factories and other features
 */
//Plugin initializing
static gboolean
plugin_init (GstPlugin * plugin)
{
  /* debug category for filtering log messages
   *
   * exchange the string 'Template plugin' with your description
   */
  GST_DEBUG_CATEGORY_INIT (gst_plugin_template_debug, "plugin",
      0, "Template plugin");

  return GST_ELEMENT_REGISTER (plugin_template, plugin);
}

/* PACKAGE: this is usually set by meson depending on some _INIT macro
 * in meson.build and then written into and defined in config.h, but we can
 * just set it ourselves here in case someone doesn't use meson to
 * compile this code. GST_PLUGIN_DEFINE needs PACKAGE to be defined.
 */
#ifndef PACKAGE
#define PACKAGE "myfirstplugin"
#endif

/* gstreamer looks for this structure to register plugins
 *
 * exchange the string 'Template plugin' with your plugin description
 */
GST_PLUGIN_DEFINE (GST_VERSION_MAJOR,
    GST_VERSION_MINOR,
    plugin,
    "Pablo's test plugin",
    plugin_init,
    PACKAGE_VERSION, GST_LICENSE, GST_PACKAGE_NAME, GST_PACKAGE_ORIGIN)
