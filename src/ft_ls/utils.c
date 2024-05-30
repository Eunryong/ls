#include "ft_ls.h"

void* ft_realloc(void* src, size_t size) {
    void* ret = malloc(size);
    if (src == NULL) return ret;
    ft_memcpy(ret, src, size);
    free(src);
    return ret;
}

void swap(t_file *a, t_file *b) {
    t_file tmp = *a;
    *a = *b;
    *b = tmp;
}

void q_sort(t_file *file_list, int start, int end) {
    if (start >= end) return;
    int i = start + 1, j = end;
    while (i <= j) {
        while (i <= end && ft_strncmp(file_list[i].name, file_list[start].name, max(file_list[i].name_len, file_list[start].name_len)) <= 0) i++;
        while (j > start && ft_strncmp(file_list[j].name, file_list[start].name, max(file_list[j].name_len, file_list[start].name_len)) >= 0) j--;
        
        if (i > j) swap(&file_list[start], &file_list[j]);
        else swap(&file_list[i], &file_list[j]);
    }

    q_sort(file_list, start, j - 1);
    q_sort(file_list, j + 1, end);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunrlee <eunrlee@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 22:42:01 by eunrlee           #+#    #+#             */
/*   Updated: 2022/11/12 12:11:17 by eunrlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

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
