/* Pango
 * pango-renderer.h: Base class for rendering
 *
 * Copyright (C) 2004, Red Hat, Inc.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */
#ifndef __PANGO_RENDERER_H_
#define __PANGO_RENDERER_H_

#include <pango/pango-layout.h>

G_BEGIN_DECLS

#define PANGO_TYPE_RENDERER            (pango_renderer_get_type())
#define PANGO_RENDERER(object)         (G_TYPE_CHECK_INSTANCE_CAST ((object), PANGO_TYPE_RENDERER, PangoRenderer))
#define PANGO_IS_RENDERER(object)      (G_TYPE_CHECK_INSTANCE_TYPE ((object), PANGO_TYPE_RENDERER))
#define PANGO_RENDERER_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), PANGO_TYPE_RENDERER, PangoRendererClass))
#define PANGO_IS_RENDERER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), PANGO_TYPE_RENDERER))
#define PANGO_RENDERER_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), PANGO_TYPE_RENDERER, PangoRendererClass))

typedef struct _PangoRenderer        PangoRenderer;
typedef struct _PangoRendererClass   PangoRendererClass;
typedef struct _PangoRendererPrivate PangoRendererPrivate;

/**
 * PangoRenderPart:
 * @PANGO_RENDER_PART_FOREGROUND: the text itself
 * @PANGO_RENDER_PART_BACKGROUND: the area behind the text
 * @PANGO_RENDER_PART_UNDERLINE: underlines
 * @PANGO_RENDER_PART_STRIKETHROUGH: strikethrough lines
 *
 * #PangoRenderPart defines different items to render for such
 * purposes as setting colors.
 *
 * Since: 1.8
 **/
/* When extending, note N_RENDER_PARTS #define in pango-renderer.c */
typedef enum
{
  PANGO_RENDER_PART_FOREGROUND,
  PANGO_RENDER_PART_BACKGROUND,
  PANGO_RENDER_PART_UNDERLINE,
  PANGO_RENDER_PART_STRIKETHROUGH
} PangoRenderPart;

/**
 * PangoRenderer:
 * @matrix: the current transformation matrix for the Renderer; may
 *    be %NULL, which should be treated the same as the identity matrix.
 *
 * #PangoRenderer is a base class for objects that are used to
 * render Pango objects such as #PangoGlyphString and
 * #PangoLayout.
 *
 * Since: 1.8
 **/
struct _PangoRenderer
{
  /*< private >*/
  GObject parent_instance;

  PangoUnderline underline;
  gboolean strikethrough;
  int active_count;

  /*< public >*/
  PangoMatrix *matrix;		/* May be NULL */

  /*< private >*/
  PangoRendererPrivate *priv;
};

/**
 * PangoRendererClass:
 * @draw_glyphs: draws a #PangoGlyphString
 * @draw_rectangle: draws a rectangle
 * @draw_error_underline: draws a squiggly line that approximately
 * covers the given rectangle in the style of an underline used to
 * indicate a spelling error.
 * @draw_shape: draw content for a glyph shaped with #PangoAttrShape.
 *   @x, @y are the coordinates of the left edge of the baseline,
 *   in user coordinates.
 * @draw_trapezoid: draws a trapezoidal filled area
 * @draw_glyph: draws a single glyph
 * @part_changed: do renderer specific processing when rendering
 *  attributes change
 * @begin: Do renderer-specific initialization before drawing
 * @end: Do renderer-specific cleanup after drawing
 * @prepare_run: updates the renderer for a new run
 * @draw_glyph_item: draws a #PangoGlyphItem
 *
 * Class structure for #PangoRenderer.
 *
 * Since: 1.8
 **/
struct _PangoRendererClass
{
  /*< private >*/
  GObjectClass parent_class;

  /* vtable - not signals */
  /*< public >*/

  /* All of the following have default implementations
   * and take as coordinates user coordinates in Pango units
   */
  void (*draw_glyphs) (PangoRenderer     *renderer,
		       PangoFont                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           