#include "ft_ls.h"

void leak() {
    system("leaks ft_ls");
}

int main(int ac, char **av) {
    ft_ls(ac, av);
    // atexit(leak);
    return 0;
}
