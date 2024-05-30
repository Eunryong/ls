/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunrlee <eunrlee@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 20:36:34 by eunrlee           #+#    #+#             */
/*   Updated: 2022/11/12 13:18:00 by eunrlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	needle_len;

	needle_len = ft_strlen(needle);
	i = 0;
	if (needle[0] == '\0')
		return ((char *)haystack);
	while (i < len && haystack[i])
	{
		if (needle_len > len - i)
			return (0);
		if (haystack[i] == needle[0])
		{
			if (ft_memcmp(&haystack[i], needle, needle_len) == 0)
				return ((char *)&haystack[i]);
		}
		i++;
	}
	return (0);
}
