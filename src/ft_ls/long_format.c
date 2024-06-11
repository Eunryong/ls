#include "ft_ls.h"

void print_total(int block) {
    write(1, "total ", 6);
    ft_putnbr_fd(block, 1);
    write(1, "\n", 1);
}

char *make_type(mode_t mode) {
    char *ret = malloc(sizeof(char) * 2);
    if (!ret) {
        perror("malloc");
        exit(1);
    }
    ret[1] = 0;
    ret[0] = '-';
    if (S_ISDIR(mode)) ret[0] = 'd';
    if (S_ISLNK(mode)) ret[0] = 'l';
    if (S_ISCHR(mode)) ret[0] = 'c';
    if (S_ISBLK(mode)) ret[0] = 'b';
    if (S_ISFIFO(mode)) ret[0] = 'p';
    if (S_ISSOCK(mode)) ret[0] = 's';
    return ret;
}

char *make_permission(mode_t mode) {
    char *ret = malloc(sizeof(char) * 10);
    if (!ret) {
        perror("malloc");
        exit(1);
    }
    ret[9] = 0;
    int permission[3] = {256, 128, 64};
    char rwx[3] = {'r', 'w', 'x'};
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            ret[i * 3 + j] = mode & permission[j] ? rwx[j] : '-';
            permission[j] >>= 3;
        }
    }
    if (mode & S_ISUID) {
        ret[2] = (mode & S_IXUSR) ? 's' : 'S';
    }
    if (mode & S_ISGID) {
        ret[5] = (mode & S_IXGRP) ? 's' : 'S';
    }
    if (mode & S_ISVTX) {
        ret[8] = (mode & S_IXOTH) ? 't' : 'T';
    }
    return ret;
}

char *make_nlink(nlink_t nlink, size_t *len) {
    char *ret = ft_itoa(nlink);
    if (!ret) {
        perror("malloc");
        exit(1);
    }
    *len = max(*len, ft_strlen(ret));
    return ret;
}

char *make_pw(uid_t uid, size_t *len) {
    struct passwd *pw;
    char *ret = NULL;
    pw = getpwuid(uid);
    ret  = ft_strdup(pw ? pw->pw_name : "???");
    if (!ret) {
        perror("malloc");
        exit(1);
    }
    *len = max(*len, pw ? ft_strlen(pw->pw_name) : 3);
    return ret;
}

char *make_gr(gid_t gid, size_t *len) {
    struct group *gr;
    char *ret = NULL;
    gr = getgrgid(gid);
    ret  = ft_strdup(gr ? gr->gr_name : "???");
    if (!ret) {
        perror("malloc");
        exit(1);
    }
    *len = max(*len, gr ? ft_strlen(gr->gr_name) : 3);
    return ret;
}

char *make_size(off_t size, size_t *len) {
    char *ret = ft_lltoa(size);
    if (!ret) {
        perror("malloc");
        exit(1);
    }
    *len = max(*len, ft_strlen(ret));
    return ret;
}

char *make_time(time_t time) {
    char *time_str = ctime(&time);
    char *ret = ft_substr(time_str, 4, 13);
    if (ret == NULL) {
        perror("malloc");
        exit(1);
    }
    ret[12] = 0;
    return ret;
}

char *make_name(char *name, bool is_link, char *path) {
    char *ret = ft_strdup(name);
    if (!ret) {
        perror("malloc");
        return 0;
    }
    char buf[1024];
    if (is_link) {
        ssize_t len;
        if (path) {
            name = ft_strjoin(path, name);
            if (!name) {
                perror("malloc");
                return 0;
            }
        }
        if ((len = readlink(name, buf, sizeof(buf))) == -1) {
            perror(name);
            exit(1);
        }
        buf[len] = 0;
        char *tmp = ret;
        ret = ft_strjoin(ret, " -> ");
        if (!ret) {
            perror("malloc");
            return 0;
        }
        free(tmp);
        tmp = ret;
        ret = ft_strjoin(ret, buf);
        if (!ret) {
            perror("malloc");
            return 0;
        }
        if (path) {
            free(name);
        }
        free(tmp);
    }
    return ret;
}

t_long_format make_long_format(t_file file, char *path, t_len *lens) {
    t_long_format format;
    format.type = make_type(file.stat.st_mode);// type
    format.permission = make_permission(file.stat.st_mode); // permission
    format.nlink = make_nlink(file.stat.st_nlink, &lens->link);// link
    format.pw = make_pw(file.stat.st_uid, &lens->pw);// user
    format.gr = make_gr(file.stat.st_gid, &lens->gr);// group
    format.size = make_size(file.stat.st_size, &lens->size);// size
    format.time = make_time(file.stat.st_ctimespec.tv_sec);// time
    format.name = make_name(file.name, S_ISLNK(file.stat.st_mode), path);// name
    return format;
}

void print_long_formats(t_long_format *formats, int size, t_len lens) {
    for (int i = 0; i < size; i++) {
        write(1, formats[i].type, 1);
        write(1, formats[i].permission, 9);
        free(formats[i].type);
        free(formats[i].permission);
        print_space(2);

        print_space(lens.link - ft_strlen(formats[i].nlink));
        write(1, formats[i].nlink, ft_strlen(formats[i].nlink));
        free(formats[i].nlink);

        print_space(1);

        write(1, formats[i].pw, ft_strlen(formats[i].pw));
        print_space(lens.pw - ft_strlen(formats[i].pw));
        free(formats[i].pw);

        print_space(2);

        write(1, formats[i].gr, ft_strlen(formats[i].gr));
        print_space(lens.gr - ft_strlen(formats[i].gr));
        free(formats[i].gr);

        print_space(2);

        print_space(lens.size - ft_strlen(formats[i].size));
        write(1, formats[i].size, ft_strlen(formats[i].size));
        free(formats[i].size);

        print_space(1);
        write(1, formats[i].time, ft_strlen(formats[i].time));
        free(formats[i].time);

        print_space(1);
        write(1, formats[i].name, ft_strlen(formats[i].name));
        free(formats[i].name);
        write(1, "\n", 1);
    }
}