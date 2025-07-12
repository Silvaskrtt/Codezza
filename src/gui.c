#include <gtk/gtk.h>  // Inclusão da biblioteca GTK

int main(int argc, char *argv[]) {
    GtkWidget *window;  // Ponteiro para o widget da janela

    gtk_init(&argc, &argv);  // Inicializa o GTK

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);  // Cria a janela principal
    gtk_window_set_title(GTK_WINDOW(window), "Codezza");  // Define o título da janela
    gtk_window_set_default_size(GTK_WINDOW(window), 1000, 720);  // Define tamanho padrão
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER); // Centralizando a Janela
    gtk_widget_show(window);

    GdkPixbuf *create_pixbuf(const gchar * filename) {

        GdkPixbuf *GdkPixbuf;
        GError *error = NULL;
        pixbuf = gdk_pixbuf_new_from_file(filename, &error);

        if (!pixbuf) {

            fprintf(stderr, "%s\n", error->message);
            g_error_free(error);
        }

        return pixbuf;
    }

    // Conecta o evento de fechar janela ao encerramento do programa
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_widget_show_all(window);  // Exibe todos os widgets da janela
    gtk_main();  // Inicia o loop principal (aguarda eventos)
~~
    return 0;
}