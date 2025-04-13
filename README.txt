git clone https://github.com/gativus-repo/demonstration_v2

gcc -o nddi quadratic_equation.o window.o `pkg-config --cflags --libs gtk4` -lm

// VMA values
objdump -t quadratic_solver | grep '.v_component'




