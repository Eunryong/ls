#include "ft_ls.h"

void print_total(int block) {
    write(1, "total ", 6);
    ft_putnbr_fd(block, 1);
    write(1, "\n", 1);
}

ssize_t print_type(mode_t mode) {
    if (S_ISDIR(mode)) return write(1, "d", 1);
    if (S_ISLNK(mode)) return write(1, "l", 1);
    if (S_ISCHR(mode)) return write(1, "c", 1);
    if (S_ISBLK(mode)) return write(1, "b", 1);
    if (S_ISFIFO(mode)) return write(1, "p", 1);
    if (S_ISSOCK(mode)) return write(1, "s", 1);
    return write(1, "-", 1);
}

void print_permission(mode_t mode) {
    int permission[3] = {256, 128, 64};
    char *rwx[3] = {"r", "w", "x"};
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            write(1, (mode & permission[j] ? rwx[j] : "-"), 1);
            permission[j] /= 8;
        }
    }
}

void print_long_format(t_file file) {
    struct passwd *pw;
    struct group *gr;
    print_type(file.stat.st_mode);
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
    int tmp = 10000;
    while (tmp > file.stat.st_size) {
        write(1, " ", 1);
        tmp = tmp > 10 ? tmp / 10 : 0;
    }
    ft_putllnbr_fd((long long)file.stat.st_size, 1);
    write(1, " ", 1);
    char *time_str = ctime(&file.stat.st_ctimespec.tv_sec);
    char *sub_time = ft_substr(time_str, 4, 13);
    sub_time[12] = 0;
    write(1, sub_time, ft_strlen(sub_time));
    write(1, " ", 1);
    write(1, file.name, file.name_len);
    if (S_ISLNK(file.stat.st_mode)) {
        char buf[1024];
        ssize_t len;
        if ((len = readlink(file.name, buf, sizeof(buf))) == -1) {
            perror("readlink");
            exit(1);
        }
        buf[len] = 0;
        write(1, " -> ", 4);
        write(1, buf, ft_strlen(buf));
    }
    write(1, "\n", 1);
    free(sub_time);
}