                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                *list,
                                          GdkAtom         target);
gboolean       gtk_target_list_find      (GtkTargetList  *list,
                                          GdkAtom         target,
                                          guint          *info);

GtkTargetEntry * gtk_target_table_new_from_list (GtkTargetList  *list,
                                                 gint           *n_targets);
void             gtk_target_table_free          (GtkTargetEntry *targets,
                                                 gint            n_targets);

gboolean gtk_selection_owner_set             (GtkWidget  *widget,
                                              GdkAtom     selection,
                                              guint32     time_);
gboolean gtk_selection_owner_set_for_display (GdkDisplay *display,
                                              GtkWidget  *widget,
                                              GdkAtom     selection,
                                              guint32     time_);

void     gtk_selection_add_target    (GtkWidget            *widget,
                                      GdkAtom               selection,
                                      GdkAtom               target,
                                      guint                 info);
void     gtk_selection_add_targets   (GtkWidget            *widget,
                                      GdkAtom               selection,
                                      const GtkTargetEntry *targets,
                                      guint                 ntargets);
void     gtk_selection_clear_targets (GtkWidget            *widget,
                                      GdkAtom               selection);
gboolean gtk_selection_convert       (GtkWidget            *widget,
                                      GdkAtom               selection,
                                      GdkAtom               target,
                                      guint32               time_);
void     gtk_selection_remove_all    (GtkWidget             *widget);

GdkAtom       gtk_selection_data_get_selection (const GtkSelectionData *selection_data);
GdkAtom       gtk_selection_data_get_target    (const GtkSelectionData *selection_data);
GdkAtom       gtk_selection_data_get_data_type (const GtkSelectionData *selection_data);
gint          gtk_selection_data_get_format    (const GtkSelectionData *selection_data);
const guchar *gtk_selection_data_get_data      (const GtkSelectionData *selection_data);
gint          gtk_selection_data_get_length    (const GtkSelectionData *selection_data);
const guchar *gtk_selection_data_get_data_with_length
                                               (const GtkSelectionData *selection_data,
                                                gint                   *length);

GdkDisplay   *gtk_selection_data_get_display   (const GtkSelectionData *selection_data);

void     gtk_selection_data_set      (GtkSelectionData     *selection_data,
                                      GdkAtom               type,
                                      gint                  format,
                                      const guchar         *data,
                                      gint                  length);
gboolean gtk_selection_data_set_text (GtkSelectionData     *selection_data,
                                      const gchar          *str,
                                      gint                  len);
guchar * gtk_selection_data_get_text (const GtkSelectionData     *selection_data);
gboolean gtk_selection_data_set_pixbuf   (GtkSelectionData  *selection_data,
                                          GdkPixbuf         *pixbuf);
GdkPixbuf *gtk_selection_data_get_pixbuf (const GtkSelectionData  *selection_data);
gboolean gtk_selection_data_set_uris (GtkSelectionData     *selection_data,
                                      gchar               **uris);
gchar  **gtk_selection_data_get_uris (const GtkSelectionData     *selection_data);

gboolean gtk_selection_data_get_targets          (const GtkSelectionData  *selection_data,
                                                  GdkAtom          **targets,
                                                  gint              *n_atoms);
gboolean gtk_selection_data_targets_include_text (const GtkSelectionData  *selection_data);
gboolean gtk_selection_data_targets_include_rich_text (const GtkSelectionData *selection_data,
                                                       GtkTextBuffer    *buffer);
gboolean gtk_selection_data_targets_include_image (const GtkSelectionData  *selection_data,
                                                   gboolean           writable);
gboolean gtk_selection_data_targets_include_uri  (const GtkSelectionData  *selection_data);
gboolean gtk_targets_include_text                (GdkAtom       *targets,
                                                  gint           n_targets);
gboolean gtk_targets_include_rich_text           (GdkAtom       *targets,
                                                  gint           n_targets,
                                                  GtkTextBuffer *buffer);
gboolean gtk_targets_include_image               (GdkAtom       *targets,
                                                  gint           n_targets,
                                                  gboolean       writable);
gboolean gtk_targets_include_uri                 (GdkAtom       *targets,
                                                  gint           n_targets);


GType             gtk_selection_data_get_type (void) G_GNUC_CONST;
GtkSelectionData *gtk_selection_data_copy     (const GtkSelectionData *data);
void              gtk_selection_data_free     (GtkSelectionData *data);

GType             gtk_target_entry_get_type    (void) G_GNUC_CONST;
GtkTargetEntry   *gtk_target_entry_new        (const gchar    *target,
                                               guint           flags,
                                               guint           info);
GtkTargetEntry   *gtk_target_entry_copy       (GtkTargetEntry *data);
void              gtk_target_entry_free       (GtkTargetEntry *data);

G_END_DECLS

#endif /* __GTK_SELECTION_H__ */
