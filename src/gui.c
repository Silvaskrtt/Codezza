#include <gtk/gtk.h>  // Inclusão da biblioteca GTK

// Função para criar o pixbuf
GdkPixbuf *create_pixbuf(const gchar * filename) {

    GdkPixbuf *pixbuf;
    GError *error = NULL;
    pixbuf = gdk_pixbuf_new_from_file(filename, &error);

    if (!pixbuf) {
        fprintf(stderr, "%s\n", error->message);
        g_error_free(error);
    }

    return pixbuf;

}

int main(int argc, char *argv[]) {
    GtkWidget *window;  // Ponteiro para o widget da janela

    gtk_init(&argc, &argv);  // Inicializa o GTK

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);  // Cria a janela principal
    gtk_window_set_title(GTK_WINDOW(window), "Codezza");  // Define o título da janela
    gtk_window_set_default_size(GTK_WINDOW(window), 1000, 720);  // Define tamanho padrão
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER); // Centralizando a Janela

        // icone da janela
        GdkPixbuf *icon = create_pixbuf("C:/Users/Murilo/Downloads/codezza.png");
        if (icon) {
        gtk_window_set_icon(GTK_WINDOW(window), icon);

        gtk_widget_show(window);

        g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

        g_object_unref(icon); // Libera a meria do icone
    }
    
    // Conecta o evento de fechar janela ao encerramento do programa
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_widget_show_all(window);  // Exibe todos os widgets da janela
    gtk_main();  // Inicia o loop principal (aguarda eventos)

    return 0;
}