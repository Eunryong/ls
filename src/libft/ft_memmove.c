/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunrlee <eunrlee@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 22:05:21 by eunrlee           #+#    #+#             */
/*   Updated: 2022/11/16 15:49:38 by eunrlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

static void	set_dst(unsigned char *c_dst, unsigned char *c_src, size_t len)
{
	size_t			i;

	i = 0;
	if (c_dst < c_src)
	{
		while (i < len)
		{
			c_dst[i] = c_src[i];
			i++;
		}
	}
	else
	{
		while (len--)
			c_dst[len] = c_src[len];
	}
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{	
	unsigned char	*c_dst;
	unsigned char	*c_src;

	if (!src && !dst)
		return (0);
	c_dst = (unsigned char *)dst;
	c_src = (unsigned char *)src;
	set_dst(c_dst, c_src, len);
	return (dst);
}
