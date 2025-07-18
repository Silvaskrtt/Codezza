#include <gtk/gtk.h>  // Inclusão da biblioteca GTK

// Função para criar o pixbuf a partir de um arquivo de imagem
GdkPixbuf *create_pixbuf(const gchar *filename) {
    GdkPixbuf *pixbuf;
    GError *error = NULL;

    pixbuf = gdk_pixbuf_new_from_file(filename, &error);

    if (!pixbuf) {
        fprintf(stderr, "Erro ao carregar imagem: %s\n", error->message);
        g_error_free(error);
    }

    return pixbuf;
}

int main(int argc, char *argv[]) {
    GtkWidget *window;  // Ponteiro para o widget da janela

    gtk_init(&argc, &argv);  // Inicializa o GTK

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);  // Cria a janela principal
    gtk_window_set_title(GTK_WINDOW(window), "Codezza");  // Define o título
    gtk_window_set_default_size(GTK_WINDOW(window), 1000, 720);  // Define tamanho padrão
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER); // Centraliza

    // Define o ícone da janela
    GdkPixbuf *icon = create_pixbuf("C:/Users/Murilo/Downloads/codezza.png");
    if (icon) {
        gtk_window_set_icon(GTK_WINDOW(window), icon);
        g_object_unref(icon);  // Libera a memória do ícone
    }

    // Conecta o evento de fechar a janela com a função gtk_main_quit
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_widget_show_all(window);  // Exibe a janela e seus elementos
    gtk_main();  // Entra no loop principal do GTK

    return 0;
}