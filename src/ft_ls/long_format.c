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
    write(1, "  ", 2);
}

void print_nlink(nlink_t nlink) {
    if (nlink < 10) write(1, " ", 1);
    ft_putnbr_fd(nlink, 1); // link
    write(1, " ", 1);
}

void print_pw(uid_t uid) {
    struct passwd *pw;
    pw = getpwuid(uid);
    write(1, pw ? pw->pw_name : "???", pw ? ft_strlen(pw->pw_name): 3);
    write(1, "  ", 2);
}

void print_gr(gid_t gid) {
    struct group *gr;
    gr = getgrgid(gid);
    write(1, gr ? gr->gr_name : "???", gr ? ft_strlen(gr->gr_name): 3);
    write(1, "  ", 2);
}

void print_size(off_t size) {
    int tmp = 10000;
    while (tmp > size) {
        write(1, " ", 1);
        tmp = tmp > 10 ? tmp / 10 : 0;
    }
    ft_putllnbr_fd((long long)size, 1);
    write(1, " ", 1);
}

void print_time(time_t time) {
    char *time_str = ctime(&time);
    char *sub_time = ft_substr(time_str, 4, 13);
    if (sub_time == NULL) {
        perror("malloc");
        exit(1);
    }
    sub_time[12] = 0;
    write(1, sub_time, ft_strlen(sub_time));
    write(1, " ", 1);
    free(sub_time);
}

void print_name(char *name, uint16_t name_len, bool is_link, char *path) {
    write(1, name, name_len);
    char buf[1024];
    if (is_link) {
        ssize_t len;
        if (path) {
            name = ft_strjoin(path, name);
        }
        if ((len = readlink(name, buf, sizeof(buf))) == -1) {
            perror(name);
            exit(1);
        }
        buf[len] = 0;
        write(1, " -> ", 4);
        write(1, buf, ft_strlen(buf));
        if (path) {
            free(name);
        }
    }
    write(1, "\n", 1);
}


void print_long_format(t_file file, char *path) {
    print_type(file.stat.st_mode);// type
    print_permission(file.stat.st_mode); // permission
    print_nlink(file.stat.st_nlink);// link
    print_pw(file.stat.st_uid);// user
    print_gr(file.stat.st_gid);// group
    print_size(file.stat.st_size);// size
    print_time(file.stat.st_ctimespec.tv_sec);// time
    print_name(file.name, file.name_len, S_ISLNK(file.stat.st_mode), path);// name
}