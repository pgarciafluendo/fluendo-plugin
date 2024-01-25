

#ifndef __GST_PLUGIN_PABLO_H__
#define __GST_PLUGIN_PABLO_H__

#include <gst/gst.h>

G_BEGIN_DECLS

#define GST_TYPE_PLUGIN_PABLO (gst_plugin_pablo_get_type())
G_DECLARE_FINAL_TYPE (GstPluginPablo, gst_plugin_pablo,
    GST, PLUGIN_PABLO, GstElement)

struct _GstPluginPablo
{
  GstElement element;

  GstPad *sinkpad, *srcpad;

  gboolean silent;

  gchar *operation;
};

G_END_DECLS

#endif /* __GST_PLUGIN_PABLO_H__ */
