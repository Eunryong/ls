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

long compare(t_file a, t_file b, t_flag flag) {
	long ret;
	if (flag.time == false) {
		ret = ft_strncmp(a.name, b.name, max(a.name_len, b.name_len));
	} else {
		ret = (b.stat.st_mtimespec.tv_sec * 100000000 + b.stat.st_mtimespec.tv_nsec) - (a.stat.st_mtimespec.tv_sec * 100000000 + a.stat.st_mtimespec.tv_nsec);
		if (ret == 0) {
			ret = ft_strncmp(a.name, b.name, max(a.name_len, b.name_len));
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

int compare_str(char *a, char *b, t_flag flag) {
	int ret = ft_strncmp(a, b, max(ft_strlen(a), ft_strlen(b)));
	if (flag.reverse) ret *= -1;
	return ret;
}

void swap_str(char **a, char **b) {
	char *tmp = *a;
	*a = *b;
	*b = tmp;
}

void q_sort_str(char **str, int start, int end, t_flag flag) {
	if (start >= end) return;
    int i = start + 1, j = end;
    while (i <= j) {
        while (i <= end && compare_str(str[i], str[start], flag) <= 0) i++;
        while (j > start && compare_str(str[j], str[start], flag) >= 0) j--;
        
        if (i > j) swap_str(&str[start], &str[j]);
        else swap_str(&str[i], &str[j]);
    }

    q_sort_str(str, start, j - 1, flag);
    q_sort_str(str, j + 1, end, flag);
}



static size_t	ft_lltoalen(long long n)
{
	size_t	len;

	len = 0;
	if (n < 0)
	{
		len++;
		n *= -1;
	}
	while (n > 0)
	{
		len++;
		n /= 10;
	}
	return (len);
}

static void	set_str(char *str, long long n, size_t len)
{
	if (n < 0)
	{
		str[0] = '-';
		n *= -1;
	}
	str[len] = '\0';
	while (n > 0)
	{
		str[len - 1] = (n % 10) + '0';
		n /= 10;
		len--;
	}
}

char	*ft_lltoa(long long n)
{
	size_t	len;
	char	*str;

	if (n == LLONG_MIN)
		return (ft_strdup("-9223372036854775808"));
	if (n == 0)
		return (ft_strdup("0"));
	len = ft_lltoalen(n);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (0);
	set_str(str, n, len);
	return (str);
}

void print_space(int len) {
	for (int i = 0; i < len; i++) {
		write(1, " ", 1);
	}
}