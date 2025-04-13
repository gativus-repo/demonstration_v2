#include <gtk/gtk.h>

void calculate_roots (gdouble a, gdouble b, gdouble c, gdouble *x1, gdouble *x2, gint *flag, gdouble *D);
gdouble __attribute__((section(".v_component"))) a,b,c,D,x1,x2;

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
    a = g_ascii_strtod(a_text, NULL);
    b = g_ascii_strtod(b_text, NULL);
    c = g_ascii_strtod(c_text, NULL);
    
    // gdouble x1,x2,D;
    gint flag;
    
    // Решаем квадратное уравнение
    if (a == 0) {
        gtk_label_set_text(result_label, "Ошибка: a не может быть 0!");
        return;
    }
    
    calculate_roots(a,b,c,&x1,&x2,&flag,&D);
    
    void update_var_log(const gchar *var_name, void *adress) {
      // Формируем ключи для доступа к меткам
      gchar *addr_key = g_strdup_printf("%s_address_label", var_name);
      
      // Получаем метки из данных окна
      GtkLabel *addr_label = g_object_get_data(G_OBJECT(data), addr_key);
      
      // Формируем строки для отображения
      gchar *addr_str = g_strdup_printf("%s: %.2f; LOCN: %p",var_name, *(gdouble*)adress, adress);
      
      // Обновляем метки
      gtk_label_set_text(addr_label, addr_str);
      
      // Освобождаем ресурсы
      g_free(addr_str);
      g_free(addr_key);
  }
    
    update_var_log("a", &a);
    update_var_log("b", &b);
    update_var_log("c", &c);
    update_var_log("x1", &x1);
    update_var_log("x2", &x2);
    update_var_log("D", &D);
    
    
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
    
    gchar *a_normal = g_strdup_printf("%.10f", a);
    
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
    
    // Разделитель и лог
    GtkWidget *separator = gtk_separator_new(GTK_ORIENTATION_HORIZONTAL);
    gtk_box_append(GTK_BOX(vbox), separator);

    GtkWidget *log_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_box_append(GTK_BOX(vbox), log_box);

    // Создание строк лога для каждой переменной
    GtkWidget* create_log_row(GtkWidget* parent, const char* name) {
        GtkWidget *hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
        GtkWidget *log_label = gtk_label_new(name);
        GtkWidget *address_label = gtk_label_new("");
        gtk_box_append(GTK_BOX(hbox), log_label);
        gtk_box_append(GTK_BOX(hbox), address_label);
        gtk_box_append(GTK_BOX(parent), hbox);
        return address_label;
    }
    
    // Сохраняем указатели на виджеты для использования в обработчике
    g_object_set_data(G_OBJECT(window), "a-entry", a_entry);
    g_object_set_data(G_OBJECT(window), "b-entry", b_entry);
    g_object_set_data(G_OBJECT(window), "c-entry", c_entry);
    g_object_set_data(G_OBJECT(window), "result-label", result_label);

    // Добавление переменных в лог
    GtkWidget *a_address = create_log_row(log_box, "(a): ");
    GtkWidget *b_address = create_log_row(log_box, "(b): ");
    GtkWidget *c_address = create_log_row(log_box, "(c): ");
    GtkWidget *D_address = create_log_row(log_box, "(D): ");
    GtkWidget *x1_address = create_log_row(log_box, "(x1): ");
    GtkWidget *x2_address = create_log_row(log_box, "(x2): ");

    // Сохранение указателей на метки адресов
    g_object_set_data(G_OBJECT(window), "a_address_label", a_address);
    g_object_set_data(G_OBJECT(window), "b_address_label", b_address);
    g_object_set_data(G_OBJECT(window), "c_address_label", c_address);
    g_object_set_data(G_OBJECT(window), "D_address_label", D_address);
    g_object_set_data(G_OBJECT(window), "x1_address_label", x1_address);
    g_object_set_data(G_OBJECT(window), "x2_address_label", x2_address);

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
