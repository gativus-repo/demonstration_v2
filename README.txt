git clone https://github.com/gativus-repo/demonstration_v2

gcc -g -o quadratic_solver variables.c window.c quadratic_equation.c `pkg-config --cflags --libs gtk4` -lm -T linker.ld -no-pie

// Lock ALSR for predictive allocation
echo 0 | sudo tee /proc/sys/kernel/randomize_va_space

// VMA values
objdump -t quadratic_solver | grep '.v_component'




