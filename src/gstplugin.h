

#ifndef __GST_PLUGIN_TEMPLATE_H__
#define __GST_PLUGIN_TEMPLATE_H__

#include <gst/gst.h>

G_BEGIN_DECLS

#define GST_TYPE_PLUGIN_TEMPLATE (gst_plugin_template_get_type())
G_DECLARE_FINAL_TYPE (GstPluginTemplate, gst_plugin_template,
    GST, PLUGIN_TEMPLATE, GstElement)

struct _GstPluginTemplate
{
  GstElement element;

  GstPad *sinkpad, *srcpad;

  gboolean silent;
};

G_END_DECLS

#endif /* __GST_PLUGIN_TEMPLATE_H__ */
