#include "ft_ls.h"

void print_dir(char *path, t_flag flag) {
    DIR             *dir = NULL;
    struct dirent   *file = NULL;
    t_file          *file_list = NULL;
    int             size = 0;
    int             block = 0;
    char            *tmp = NULL;
    t_long_format   *formats = NULL;
    t_len           lens = {0, 0, 0, 0};

    if ((dir = opendir(path)) == NULL) {
        perror(path);
        return;
    }
    
    if (flag.depth == 1) {
        write(1, path, ft_strlen(path));
        write(1, ":\n", 2);
    }

    if (path[ft_strlen(path) - 1] != '/') {
        path = ft_strjoin(path, "/");
        if (path == NULL) {
            perror("malloc");
            exit(1);
        }
        tmp = path;
    }

    while ((file = readdir(dir)) != NULL) {
        if (flag.all == false && file->d_name[0] == '.') {
            continue;
        }
        size++;
        file_list = ft_realloc(file_list, size - 1, size, sizeof(t_file));
        char *path_file = ft_strjoin(path, file->d_name);
        if (path_file == NULL) {
            perror("malloc");
            exit(1);
        }
        if (lstat(path_file, &file_list[size - 1].stat) == -1) {
            perror(path_file);
            free(path_file);
            return;
        }
        file_list[size - 1].name = ft_strdup(file->d_name);
        if (file_list[size - 1].name == NULL) {
            perror("malloc");
            exit(1);
        }
        file_list[size - 1].name_len = file->d_namlen;
        block += file_list[size - 1].stat.st_blocks;
        free(path_file);
    }
    q_sort(file_list, 0, size - 1, flag);
    if (flag.long_list) {
        print_total(block);
        formats = (t_long_format *)malloc(size * sizeof(t_long_format));
    }
    for (int i = 0; i < size; i++) {
        if (flag.long_list == true) {
            formats[i] = make_long_format(file_list[i], path, &lens);
        } else {
            write(1, file_list[i].name, ft_strlen(file_list[i].name));
            if (i == size - 1) {
                write(1, "\n", 1);
            } else {
                write(1, "  ", 2);
            }
        }
    }
    if (formats != NULL) {
        print_long_formats(formats, size, lens);
        free(formats);
    }
    if (flag.recursive == true) {
        for (int i = 0; i < size; i++) {
            if (ft_strncmp(file_list[i].name, ".", 2) == 0 || ft_strncmp(file_list[i].name, "..", 3) == 0) continue;
            if (S_ISDIR(file_list[i].stat.st_mode)) {
                flag.depth = 1;
                write(1, "\n", 1);
                char *new_path = ft_strjoin(path, file_list[i].name);
                if (new_path == NULL) {
                    perror("malloc");
                    exit(1);
                }
                print_dir(new_path, flag);
                free(new_path);
            }
        }
    }
    if (tmp) free(tmp);
    for (int i = 0; i < size; i++) {
        free(file_list[i].name);
    }
    if (file_list) free(file_list);
    closedir(dir);
}