#include "ft_ls.h"

void* ft_realloc(void* src, size_t cur_size, size_t size, size_t elem_size) {
    void* ret = malloc(size * elem_size);
	if (ret == NULL) {
		perror("malloc");
		exit(1);
	}
    if (src == 0) return ret;
    ft_memcpy(ret, src, (cur_size > size ? size : cur_size) * elem_size);
    free(src);
    return ret;
}

bool check_root(char *path) {
	if (ft_strncmp(path, "./", 3) == 3) return true;
	return false;
}

long compare(t_file a, t_file b, t_flag flag) {
	long ret;
	if (flag.time == false) {
		ret = ft_strncmp(check_root(a.name) == true ? "" : a.name, check_root(b.name) == true ? "" : b.name, max(a.name_len, b.name_len));
	} else {
		ret = b.stat.st_mtimespec.tv_sec - a.stat.st_mtimespec.tv_sec;
		if (ret == 0) {
			ret = ft_strncmp(check_root(a.name) == true ? "" : a.name, check_root(b.name) == true ? "" : b.name, max(a.name_len, b.name_len));
		}
	}
	if (flag.reverse) ret *= -1;
	return ret;
}

void swap(t_file *a, t_file *b) {
    t_file tmp = *a;
    *a = *b;
    *b = tmp;
}

void q_sort(t_file *file_list, int start, int end, t_flag flag) {
    if (start >= end) return;
    int i = start + 1, j = end;
    while (i <= j) {
        while (i <= end && compare(file_list[i], file_list[start], flag) <= 0) i++;
        while (j > start && compare(file_list[j], file_list[start], flag) >= 0) j--;
        
        if (i > j) swap(&file_list[start], &file_list[j]);
        else swap(&file_list[i], &file_list[j]);
    }

    q_sort(file_list, start, j - 1, flag);
    q_sort(file_list, j + 1, end, flag);
}

int compare_str(char *a, char *b) {
	return ft_strncmp(check_root(a) == true ? "" : a, check_root(b) == true ? "" : b, max(ft_strlen(a), ft_strlen(b)));
}

void swap_str(char **a, char **b) {
	char *tmp = *a;
	*a = *b;
	*b = tmp;
}

void q_sort_str(char **str, int start, int end) {
	if (start >= end) return;
    int i = start + 1, j = end;
    while (i <= j) {
        while (i <= end && compare_str(str[i], str[start]) <= 0) i++;
        while (j > start && compare_str(str[j], str[start]) >= 0) j--;
        
        if (i > j) swap_str(&str[start], &str[j]);
        else swap_str(&str[i], &str[j]);
    }

    q_sort_str(str, start, j - 1);
    q_sort_str(str, j + 1, end);
}

void	ft_putllnbr_fd(long long n, int fd)
{
	char	c;

	if (n == LLONG_MIN)
		write(fd, "-9223372036854775808", 20);
	else if (n < 0)
	{
		n *= -1;
		write(fd, "-", 1);
		ft_putnbr_fd(n, fd);
	}
	else if (n < 10)
	{
		c = n % 10 + '0';
		write(fd, &c, 1);
	}
	else
	{
		ft_putnbr_fd(n / 10, fd);
		ft_putnbr_fd(n % 10, fd);
	}
}
