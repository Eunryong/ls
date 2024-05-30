/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunrlee <eunrlee@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 21:44:28 by eunrlee           #+#    #+#             */
/*   Updated: 2022/11/10 16:35:48 by eunrlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*c_b;

	c_b = (unsigned char *)b;
	i = 0;
	while (i < len)
	{
		c_b[i] = (unsigned char)c;
		i++;
	}
	return (b);
}
