/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunrlee <eunrlee@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 20:37:18 by eunrlee           #+#    #+#             */
/*   Updated: 2022/11/12 17:04:36 by eunrlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*arr;

	if (size != 0 && count > SIZE_MAX / size)
		return (0);
	arr = malloc(size * count);
	if (!arr)
		return (0);
	ft_bzero(arr, size * count);
	return ((void *)arr);
}
