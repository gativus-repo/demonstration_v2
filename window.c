#include <gtk/gtk.h>

void calculate_roots (gdouble a, gdouble b, gdouble c, gdouble *x1, gdouble *x2, gint *flag, gdouble *D);

// Функция-обработчик нажатия кнопки
static void solve_equation(GtkWidget *widget, gpointer data) {
    GtkEntry *a_entry = g_object_get_data(G_OBJECT(data), "a-entry");
    GtkEntry *b_entry = g_object_get_data(G_OBJECT(data), "b-entry");
    GtkEntry *c_entry = g_object_get_data(G_OBJECT(data), "c-entry");
    GtkLabel *result_label = g_object_get_data(G_OBJECT(data), "result-label");

    // Получаем текст из полей ввода
    const gchar *a_text = gtk_editable_get_text(GTK_EDITABLE(a_entry));
    const gchar *b_text = gtk_editable_get_text(GTK_EDITABLE(b_entry));
    const gchar *c_text = gtk_editable_get_text(GTK_EDITABLE(c_entry));

    // Преобразуем в числа
    gdouble a = g_ascii_strtod(a_text, NULL);
    gdouble b = g_ascii_strtod(b_text, NULL);
    gdouble c = g_ascii_strtod(c_text, NULL);
    
    gdouble x1,x2,D;
    gint flag;
    
    // Решаем квадратное уравнение
    if (a == 0) {
        gtk_label_set_text(result_label, "Ошибка: a не может быть 0!");
        return;
    }
    
    calculate_roots(a,b,c,&x1,&x2,&flag,&D);
    gchar *result = g_strdup_printf("Нет действительных корней");
    if (flag == 0){
      result = g_strdup_printf("Нет действительных корней, т.к. D = %.2f", D);
    } else if (flag == 1){
      result = g_strdup_printf("Корень единственный: x₁ = x₂ = %.2f", x1);
    } else if (flag == 2){
      result = g_strdup_printf("Корни: x₁ = %.2f, x₂ = %.2f", x1, x2);
    }
    gtk_label_set_text(result_label, result);
    g_free(result);
}

int main(int argc, char **argv) {
    // Инициализация GTK
    gtk_init();

    // Создание главного окна
    GtkWidget *window = gtk_window_new();
    gtk_window_set_title(GTK_WINDOW(window), "Квадратное уравнение");
    gtk_window_set_default_size(GTK_WINDOW(window), 640, 480);

    // Создание вертикального контейнера для элементов
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_widget_set_valign(vbox, GTK_ALIGN_CENTER);
    gtk_window_set_child(GTK_WINDOW(window), vbox);

    // Метка для отображения результата
    GtkWidget *result_label = gtk_label_new("Введите коэффициенты a, b, c");
    gtk_box_append(GTK_BOX(vbox), result_label);

    // Создание полей ввода с метками
    GtkWidget *a_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    GtkWidget *a_label = gtk_label_new("a:");
    GtkWidget *a_entry = gtk_entry_new();
    gtk_box_append(GTK_BOX(a_box), a_label);
    gtk_widget_set_margin_end(a_label, 10);
    gtk_box_append(GTK_BOX(a_box), a_entry);
    gtk_widget_set_halign(a_box, GTK_ALIGN_CENTER);
    gtk_box_append(GTK_BOX(vbox), a_box);

    GtkWidget *b_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    GtkWidget *b_label = gtk_label_new("b:");
    gtk_widget_set_margin_end(b_label, 10);
    GtkWidget *b_entry = gtk_entry_new();
    gtk_box_append(GTK_BOX(b_box), b_label);
    gtk_box_append(GTK_BOX(b_box), b_entry);
    gtk_widget_set_halign(b_box, GTK_ALIGN_CENTER);
    gtk_box_append(GTK_BOX(vbox), b_box);

    GtkWidget *c_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    GtkWidget *c_label = gtk_label_new("c:");
    gtk_widget_set_margin_end(c_label, 10);
    GtkWidget *c_entry = gtk_entry_new();
    gtk_box_append(GTK_BOX(c_box), c_label);
    gtk_box_append(GTK_BOX(c_box), c_entry);
    gtk_widget_set_halign(c_box, GTK_ALIGN_CENTER);
    gtk_box_append(GTK_BOX(vbox), c_box);

    // Кнопка для решения уравнения
    GtkWidget *solve_button = gtk_button_new_with_label("Решить уравнение");
    gtk_widget_set_halign(solve_button, GTK_ALIGN_CENTER);
    gtk_box_append(GTK_BOX(vbox), solve_button);

    // Сохраняем указатели на виджеты для использования в обработчике
    g_object_set_data(G_OBJECT(window), "a-entry", a_entry);
    g_object_set_data(G_OBJECT(window), "b-entry", b_entry);
    g_object_set_data(G_OBJECT(window), "c-entry", c_entry);
    g_object_set_data(G_OBJECT(window), "result-label", result_label);

    // Подключаем обработчик нажатия кнопки
    g_signal_connect(solve_button, "clicked", G_CALLBACK(solve_equation), window);

    // Подключаем обработчик закрытия окна
    g_signal_connect(window, "close-request", G_CALLBACK(gtk_window_destroy), NULL);

    // Отображаем все виджеты
    gtk_window_present(GTK_WINDOW(window));

    // Запуск главного цикла GTK
    while (g_list_model_get_n_items(gtk_window_get_toplevels()) > 0) {
        g_main_context_iteration(NULL, TRUE);
    }

    return 0;
}
