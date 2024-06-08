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
#include <time.h>
#include "libft.h"

#define ARG_ERROR "Error: Invalid error\n"
#define max(x, y) (x) > (y) ? (x) : (y)

typedef struct s_flag {
    bool    long_list; // format
    bool    recursive; // print
    bool    all;       // print
    bool    reverse;   // sort
    bool    time;      // sort
    bool    flag; 
    int     depth;
}   t_flag;

typedef struct s_long_format {
    char *type;
    char *permission;
    char *nlink;
    char *pw;
    char *gr;
    char *size;
    char *time;
    char *name;
} t_long_format;

typedef struct s_file {
    char        *name;
    uint16_t    name_len;
    int         type;
    struct stat stat;
}   t_file;

typedef struct s_len {
    size_t link;
    size_t pw;
    size_t gr;
    size_t size;
}   t_len;
// ft_ls
void            ft_ls(int ac, char **av);

// utils
void            *ft_realloc(void* src, size_t cur_size, size_t size, size_t elem_size);
void            q_sort(t_file *file_list, int start, int end, t_flag flag);
void            q_sort_str(char **str, int start, int end, t_flag flag);
char	        *ft_lltoa(long long n);
void            print_space(int len);
bool            check_root(char *path);

// long format
t_long_format   make_long_format(t_file file, char *path, t_len *lens);
void            print_long_formats(t_long_format *formats, int size, t_len lens);
void            print_total(int block);
// check
bool            check_argv(int ac, char **av, t_flag *flag);

// print
void            print_dir(char *path, t_flag flag);

#endif