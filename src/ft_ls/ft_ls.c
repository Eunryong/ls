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
            flag->flag = true;
        }
    }
    return true;
}

bool check_argv(int ac, char **av, t_flag *flag) {
    if (ac == 1) return true;
    if (flag_check(av[1], flag) == 0)
        return false;
    return true;
}

void print_total(int block) {
    write(1, "total: ", 7);
    ft_putnbr_fd(block, 1);
    write(1, "\n", 1);
}

char get_type(mode_t mode) {
    if (S_ISDIR(mode)) return 'd';
    if (S_ISLNK(mode)) return 'l';
    if (S_ISCHR(mode)) return 'c';
    if (S_ISBLK(mode)) return 'b';
    if (S_ISFIFO(mode)) return 'p';
    if (S_ISSOCK(mode)) return 's';
    return '-';
}

void print_permission(mode_t mode) {
    int permission[3] = {400, 200, 100};
    char *rwx[3] = {"r", "w", "x"};
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            write(1, (mode & permission[i] ? rwx[j] : "-"), 1);
            permission[i] /= 10;
        }
    }
}

void print_long_format(t_file file) {
    char type[1];
    struct passwd *pw;
    struct group *gr;
    type[0] = get_type(file.stat.st_mode);
    write(1, type, 1); // file type
    print_permission(file.stat.st_mode); // permission
    write(1, " ", 1);
    if (file.stat.st_nlink < 10) write(1, " ", 1);
    ft_putnbr_fd(file.stat.st_nlink, 1); // link
    write(1, " ", 1);
    pw = getpwuid(file.stat.st_uid);
    write(1, pw ? pw->pw_name : "???", pw ? ft_strlen(pw->pw_name): 3);
    write(1, "  ", 2);
    gr = getgrgid(file.stat.st_gid);
    write(1, gr ? gr->gr_name : "???", gr ? ft_strlen(gr->gr_name): 3);
    write(1, "  ", 2);
    long long tmp = (long long)file.stat.st_size == 0 ? 1 : (long long)file.stat.st_size;
    while (tmp < 10000) {
        write(1, " ", 1);
        tmp *= 10;
    }
    ft_putllnbr_fd((long long)file.stat.st_size, 1);
    return ;
}

void print_list(char *path, t_flag flag) {
    DIR             *dir = NULL;
    struct dirent   *file = NULL;
    t_file          *file_list = NULL;
    int             size = 0;
    int             block = 0;
    if ((dir = opendir(path)) == NULL) {
        perror("No such file or directory\n");
        return;
    }
    while ((file = readdir(dir)) != NULL) {
        if (flag.all == false && (ft_strncmp(file->d_name, "..", 2) == 0 || ft_strncmp(file->d_name, ".", 3) == 0)) {
            continue;
        }
        struct stat buf;
        stat(file->d_name, &buf);
        size++;
        file_list = ft_realloc(file_list, (size) * sizeof(t_file));
        file_list[size - 1].name = ft_strdup(file->d_name);
        file_list[size - 1].stat = buf;
        block += buf.st_blocks;
    }
    q_sort(file_list, 0, size - 1);
    if (flag.long_list) print_total(block);
    for (int i = 0; i < size; i++) {
        if (flag.long_list == true) {
            print_long_format(file_list[i]);
            write(1, "\n", 1);
        } else {
            write(1, file_list[i].name, ft_strlen(file_list[i].name));
            write(1, "  ", 1);
        }
    }
    if (flag.recursive == true) {
        for (int i = 1; i < size; i++)
            print_list(file_list[i].name, flag);
    }
    closedir(dir);
    for (int i = 0; i < size; i++) {
        free(file_list[i].name);
    }
    free(file_list);
}

void exec(int ac, char **av, t_flag flag) {
    t_file  *dir_list = NULL;
    int     dir_size = 0;
    t_file  *file_list = NULL;
    int     file_size = 0;

    if (ac == 1 || (ac == 2 && flag.flag)) return print_list("./", flag);
    for (int i = flag.flag == true ? 2 : 1; i < ac; i++) {
        struct stat buf;
        stat(av[i], &buf);
        if (S_ISDIR(buf.st_mode)) {
            dir_size++;
            dir_list = ft_realloc(dir_list, (dir_size + 1) * sizeof(t_file));
            dir_list[dir_size - 1].name = ft_strdup(av[i]);
        } else {
            file_size++;
            file_list = ft_realloc(file_list, (file_size + 1) * sizeof(t_file));
            file_list[file_size - 1].name = ft_strdup(av[i]);
            file_list[file_size - 1].name_len = ft_strlen(file_list[file_size - 1].name);
            file_list[file_size - 1].stat = buf;
        }
    }
    q_sort(file_list, 0, file_size - 1);
    for (int i = 0; i < file_size; i++) {
        if (flag.long_list == true) {
            print_long_format(file_list[i]);
            write(1, "\n", 1);
        } else {
            write(1, file_list[i].name, file_list[i].name_len);
            write(1, "  ", 1);
        }
    }
    q_sort(dir_list, 0, dir_size - 1);
    for (int i = 0; i < dir_size; i++) {
        print_list(dir_list[i].name, flag);
    }
}

void ft_ls(int ac, char **av) {
    t_flag flag = {0, 0, 0, 0, 0, 0};
    if (check_argv(ac, av, &flag) == false) {
        write(2, ARG_ERROR, sizeof(ARG_ERROR));
        exit(1);
    }
    exec(ac, av, flag);
}