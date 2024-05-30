#ifndef FT_LS_H
#define FT_LS_H

#include <pwd.h>
#include <grp.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/xattr.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <stdlib.h>
#include <dirent.h>
#include "libft.h"

#define ARG_ERROR "Error: Invalid error\n"
#define max(x, y) (x) > (y) ? (x) : (y)
typedef struct s_flag {
    bool long_list; // format
    bool recursive; // print
    bool all;       // print
    bool reverse;   // sort
    bool time;      // sort
    bool flag;
}   t_flag;

typedef struct s_file {
    char        *name;
    uint16_t    name_len;
    int         type;
    struct stat stat;
}   t_file;

void* ft_realloc(void* src, size_t size);
void q_sort(t_file *file_list, int start, int end);
void ft_ls(int ac, char **av);
void	ft_putllnbr_fd(long long n, int fd);
#endif