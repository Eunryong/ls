/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunrlee <eunrlee@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 20:36:25 by eunrlee           #+#    #+#             */
/*   Updated: 2022/11/10 16:34:14 by eunrlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	a;
	unsigned char	*s2;

	a = c;
	s2 = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (s2[i] == a)
			return ((void *)&s[i]);
		i++;
	}
	return (0);
}
