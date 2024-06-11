#include "ft_ls.h"

void exec(int ac, char **av, t_flag flag) {
    t_file  *dir_list = NULL;
    int     dir_size = 0;
    t_file  *file_list = NULL;
    int     file_size = 0;
    t_long_format *formats = NULL;
    t_len   lens = {0, 0, 0, 0};

    if (ac == flag.flag + 1) return print_dir("./", flag); // default
    
    for (int i = flag.flag + 1; i < ac; i++) {
        struct stat buf;
        if (lstat(av[i], &buf) == -1) {
            perror(av[i]);
            continue;
        }
        if (S_ISDIR(buf.st_mode)) {
            dir_size++;
            dir_list = ft_realloc(dir_list, dir_size - 1, dir_size, sizeof(t_file));
            dir_list[dir_size - 1].name = ft_strdup(av[i]);
            if (dir_list[dir_size - 1].name == NULL) {
                perror("malloc");
                exit(1);
            }
        } else {
            file_size++;
            file_list = ft_realloc(file_list, file_size - 1, file_size, sizeof(t_file));
            file_list[file_size - 1].name = ft_strdup(av[i]);
            if (file_list[file_size - 1].name == NULL) {
                perror("malloc");
                exit(1);
            }
            file_list[file_size - 1].name_len = ft_strlen(file_list[file_size - 1].name);
            file_list[file_size - 1].stat = buf;
        }
    }
    q_sort(file_list, 0, file_size - 1, flag);
    q_sort(dir_list, 0, dir_size - 1, flag);
    if (flag.long_list) {
        formats = (t_long_format *)malloc(file_size * sizeof(t_long_format));
    }
    for (int i = 0; i < file_size; i++) {
        if (flag.long_list == true) {
            formats[i] = make_long_format(file_list[i], NULL, &lens);
        } else {
            write(1, file_list[i].name, file_list[i].name_len);
            if (i == file_size - 1) {
                write(1, "\n", 1);
            } else {
                write(1, "  ", 2);
            }
        }
    }
    if (formats != NULL) {
        print_long_formats(formats, file_size, lens);
        free(formats);
    }
    for (int i = 0; i < dir_size; i++) {
        if (flag.depth) write(1, "\n", 1);
        if (dir_size != 1) flag.depth = 1;
        print_dir(dir_list[i].name, flag);
    }
    for (int i = 0; i < file_size || i < dir_size; i++) {
        if (i < file_size) free(file_list[i].name);
        if (i < dir_size) free(dir_list[i].name);
    }
    if (file_list) free(file_list);
    if (dir_list) free(dir_list);
}

void ft_ls(int ac, char **av) {
    t_flag flag = {0, 0, 0, 0, 0, 0, 0};
    
    if (check_argv(ac, av, &flag) == false) {
        write(2, ARG_ERROR, sizeof(ARG_ERROR));
        exit(1);
    }
    q_sort_str(av, flag.flag + 1, ac - 1, flag);
    exec(ac, av, flag);
}