/* GIO - GLib Input, Output and Streaming Library
 *
 * Copyright (C) 2010 Red Hat, Inc.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General
 * Public License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place, Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#if !defined (__GIO_GIO_H_INSIDE__) && !defined (GIO_COMPILATION)
#error "Only <gio/gio.h> can be included directly."
#endif

#ifndef __G_TLS_CONNECTION_H__
#define __G_TLS_CONNECTION_H__

#include <gio/giostream.h>

G_BEGIN_DECLS

#define G_TYPE_TLS_CONNECTION            (g_tls_connection_get_type ())
#define G_TLS_CONNECTION(inst)           (G_TYPE_CHECK_INSTANCE_CAST ((inst), G_TYPE_TLS_CONNECTION, GTlsConnection))
#define G_TLS_CONNECTION_CLASS(class)    (G_TYPE_CHECK_CLASS_CAST ((class), G_TYPE_TLS_CONNECTION, GTlsConnectionClass))
#define G_IS_TLS_CONNECTION(inst)        (G_TYPE_CHECK_INSTANCE_TYPE ((inst), G_TYPE_TLS_CONNECTION))
#define G_IS_TLS_CONNECTION_CLASS(class) (G_TYPE_CHECK_CLASS_TYPE ((class), G_TYPE_TLS_CONNECTION))
#define G_TLS_CONNECTION_GET_CLASS(inst) (G_TYPE_INSTANCE_GET_CLASS ((inst), G_TYPE_TLS_CONNECTION, GTlsConnectionClass))

typedef struct _GTlsConnectionClass   GTlsConnectionClass;
typedef struct _GTlsConnectionPrivate GTlsConnectionPrivate;

struct _GTlsConnection {
  GIOStream parent_instance;

  GTlsConnectionPrivate *priv;
};

struct _GTlsConnectionClass
{
  GIOStreamClass parent_class;

  /* signals */
  gboolean          ( *accept_certificate) (GTlsConnection       *connection,
					    GTlsCertificate      *peer_cert,
					    GTlsCertificateFlags  errors);

  /* methods */
  gboolean ( *handshake )        (GTlsConnection       *conn,
				  GCancellable         *cancellable,
				  GError              **error);

  void     ( *handshake_async )  (GTlsConnection       *conn,
				  int                   io_priority,
				  GCancellable         *cancellable,
				  GAsyncReadyCallback   callback,
				  gpointer              user_data);
  gboolean ( *handshake_finish ) (GTlsConnection       *conn,
				  GAsyncResult         *result,
				  GError              **error);

  /*< private >*/
  /* Padding for future expansion */
  gpointer padding[8];
};

GType                 g_tls_connection_get_type                    (void) G_GNUC_CONST;

GLIB_DEPRECATED
void                  g_tls_connection_set_use_system_certdb       (GTlsConnection       *conn,
                                                                    gboolean              use_system_certdb);
GLIB_DEPRECATED
gboolean              g_tls_connection_get_use_system_certdb       (GTlsConnection       *conn);

void                  g_tls_connection_set_database                (GTlsConnection       *conn,
								    GTlsDatabase         *database);
GTlsDatabase *        g_tls_connection_get_database                (GTlsConnection       *conn);

void                  g_tls_connection_set_certificate             (GTlsConnection       *conn,
                                                                    GTlsCertificate      *certificate);
GTlsCertificate      *g_tls_connection_get_certificate             (GTlsConnection       *conn);

void                  g_tls_connection_set_interaction             (GTlsConnection       *conn,
                                                                    GTlsInteraction      *interaction);
GTlsInteraction *     g_tls_connection_get_interaction             (GTlsConnection       *conn);

GTlsCertificate      *g_tls_connection_get_peer_certificate        (GTlsConnection                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    