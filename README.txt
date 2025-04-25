git clone https://github.com/gativus-repo/demonstration_v2

gcc -g -o quadratic_solver variables.c window.c calculate_discriminant.c quadratic_equation.c `pkg-config --cflags --libs gtk4` -lm -T linker.ld -no-pie


// VMA values
objdump -t quadratic_solver | grep '.v_component'




