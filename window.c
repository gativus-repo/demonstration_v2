#include <gtk/gtk.h>

void calculate_roots (double a, double b, double c, double *x1, double *x2, int *flag, double *D);
extern double a, b, c, D, x1, x2;


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
      gchar *addr_str = g_strdup_printf("LOCN(%s): %p, type: double, value: %.2f;",var_name,*(gdouble*)adress, adress);
      
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
    GtkCssProvider *cssProvider = gtk_css_provider_new();
    gtk_css_provider_load_from_path(cssProvider, "main.css");
    gtk_style_context_add_provider_for_display(gdk_display_get_default(),     GTK_STYLE_PROVIDER(cssProvider), GTK_STYLE_PROVIDER_PRIORITY_USER);
    
    gtk_window_set_title(GTK_WINDOW(window), "NDDI - квадратное уравнение");
    gtk_window_set_default_size(GTK_WINDOW(window), 1280, 1024);
  
    // Создание вертикального контейнера для элементов
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 15);
    GtkWidget *abox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 15);
    GtkWidget *grid = gtk_grid_new();
    
    gtk_grid_set_column_homogeneous (GTK_GRID(grid), TRUE);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 0);
    gtk_widget_set_name(grid, "grid");
    gtk_widget_set_name(vbox, "vbox");
    gtk_widget_set_name(abox, "abox");
    gtk_widget_set_valign(abox, GTK_ALIGN_CENTER);
    gtk_widget_set_halign(abox, GTK_ALIGN_CENTER);
    
    gtk_widget_set_valign(grid, GTK_ALIGN_CENTER);
    gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
    gtk_window_set_child(GTK_WINDOW(window), grid);
    gtk_widget_set_valign(vbox, GTK_ALIGN_CENTER);
    gtk_widget_set_halign(vbox, GTK_ALIGN_CENTER);
    
    GtkWidget *v_section_label = gtk_label_new("V - section");
    gtk_widget_set_name(v_section_label, "v_section_label");
    gtk_grid_attach(GTK_GRID(grid), v_section_label, 0, 0, 2, 1);
    gtk_grid_set_row_spacing(GTK_GRID(grid), 15);
    gtk_grid_attach(GTK_GRID(grid), vbox, 0, 1, 1, 1);
    
    GtkWidget *imageView = gtk_image_new_from_file ("NDDI.png");
    gtk_image_set_pixel_size (GTK_IMAGE(imageView), 200);
    GtkWidget *result_label_nddi = gtk_label_new("UNON - 95.161.61.217");

    gtk_box_append(GTK_BOX(vbox), result_label_nddi);
    gtk_box_append(GTK_BOX(vbox), imageView);
    
    gtk_widget_set_name(imageView, "image");
    gtk_widget_set_name(result_label_nddi, "label_nddi");
    
    GtkWidget *separator = gtk_separator_new(GTK_ORIENTATION_HORIZONTAL);
    gtk_box_append(GTK_BOX(vbox), separator);
    
    // Метка для отображения результата
    // GtkWidget *v_comp_label = gtk_label_new("V - компоненты:");
    //  gtk_box_append(GTK_BOX(abox), v_comp_label);
    GtkWidget *abox_label = gtk_label_new("Окно ввода");
    gtk_box_append(GTK_BOX(abox), abox_label);
    gtk_widget_set_name(abox_label, "abox_label");
    GtkWidget *result_label = gtk_label_new("Введите коэффициенты a, b, c");
    gtk_box_append(GTK_BOX(abox), result_label);

    // Создание полей ввода с метками
    GtkWidget *a_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    GtkWidget *a_label = gtk_label_new("a:");
    GtkWidget *a_entry = gtk_entry_new();
    gtk_box_append(GTK_BOX(a_box), a_label);
    gtk_widget_set_margin_end(a_label, 10);
    gtk_box_append(GTK_BOX(a_box), a_entry);
    gtk_widget_set_halign(a_box, GTK_ALIGN_CENTER);
    gtk_box_append(GTK_BOX(abox), a_box);

    GtkWidget *b_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    GtkWidget *b_label = gtk_label_new("b:");
    gtk_widget_set_margin_end(b_label, 10);
    GtkWidget *b_entry = gtk_entry_new();
    gtk_box_append(GTK_BOX(b_box), b_label);
    gtk_box_append(GTK_BOX(b_box), b_entry);
    gtk_widget_set_halign(b_box, GTK_ALIGN_CENTER);
    gtk_box_append(GTK_BOX(abox), b_box);

    GtkWidget *c_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    GtkWidget *c_label = gtk_label_new("c:");
    gtk_widget_set_margin_end(c_label, 10);
    GtkWidget *c_entry = gtk_entry_new();
    gtk_box_append(GTK_BOX(c_box), c_label);
    gtk_box_append(GTK_BOX(c_box), c_entry);
    gtk_widget_set_halign(c_box, GTK_ALIGN_CENTER);
    
    gtk_box_append(GTK_BOX(abox), c_box);
    gtk_grid_attach(GTK_GRID(grid), abox, 1, 1, 1, 1);
    //gtk_box_append(GTK_BOX(vbox), abox);
    // Кнопка для решения уравнения
    GtkWidget *solve_button = gtk_button_new_with_label("Решить уравнение");
    gtk_widget_set_halign(solve_button, GTK_ALIGN_CENTER);
    
    gtk_widget_set_name(solve_button, "btn");
    
    gtk_box_append(GTK_BOX(abox), solve_button);
    
    // Разделитель и лог
    gtk_box_append(GTK_BOX(vbox), separator);

    GtkWidget *log_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_box_append(GTK_BOX(vbox), log_box);

    // Создание строк лога для каждой переменной
    GtkWidget* create_log_row(GtkWidget* parent, const char* name) {
        GtkWidget *hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
        GtkWidget *log_label = gtk_label_new(name);
        GtkWidget *address_label = gtk_label_new("");
        gtk_box_append(GTK_BOX(hbox), log_label);
        
        if (name == "Values:"){
           gtk_widget_set_name(log_label, "log_name");
        }
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
    GtkWidget *log_name = create_log_row(log_box, "Values:");
    GtkWidget *a_address = create_log_row(log_box, "");
    GtkWidget *b_address = create_log_row(log_box, "");
    GtkWidget *c_address = create_log_row(log_box, "");
    GtkWidget *D_address = create_log_row(log_box, "");
    GtkWidget *x1_address = create_log_row(log_box, "");
    GtkWidget *x2_address = create_log_row(log_box, "");

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
