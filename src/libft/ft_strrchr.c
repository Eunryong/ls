/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunrlee <eunrlee@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 13:12:04 by eunrlee           #+#    #+#             */
/*   Updated: 2022/11/12 13:15:19 by eunrlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;

	i = ft_strlen(s);
	if ((unsigned char)c == '\0')
		return ((char *)&s[i]);
	if (s[0] == '\0')
		return (0);
	while (--i > 0)
	{
		if (s[i] == (unsigned char)c)
			return ((char *)&s[i]);
	}
	if (s[i] == (unsigned char)c)
		return ((char *)&s[i]);
	else
		return (0);
}
