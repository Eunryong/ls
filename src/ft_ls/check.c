#include "ft_ls.h"

bool flag_check(char *av, t_flag *flag) {
    if (av[0] == '-') {
        for (size_t i = 1; i < ft_strlen(av); i++) {
            switch (av[i]) {
                case 'l':
                    flag->long_list = true;
                    break;
                case 'R':
                    flag->recursive = true;
                    break;
                case 'a':
                    flag->all = true;
                    break;
                case 'r':
                    flag->reverse = true;
                    break;
                case 't':
                    flag->time = true;
                    break;
                default:
                    return false;
            }
            flag->flag++;
        }
    }
    return true;
}

bool check_argv(int ac, char **av, t_flag *flag) {
    if (ac == 1) return true;
    for (int i = 1; i < ac; i++) {
        if (av[i][0] != '-') break;
        if (flag_check(av[i], flag) == 0)
            return false;
    }
    return true;
}