/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunrlee <eunrlee@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 15:17:42 by eunrlee           #+#    #+#             */
/*   Updated: 2022/11/16 15:50:27 by eunrlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

static size_t	ft_checkidx(char const *s1, char const *set, size_t idx)
{
	if (idx == 0)
	{
		while (s1[idx] != '\0' && ft_strchr(set, s1[idx]))
			idx++;
		return (idx);
	}
	else
	{
		while (s1[idx - 1] != '\0' && ft_strchr(set, s1[idx - 1])
			&& idx >= 2)
			idx--;
		return (idx);
	}
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	s1_len;
	size_t	end;
	size_t	start;
	char	*str;

	if (!s1)
		return (0);
	if (!set)
		return (ft_strdup(s1));
	s1_len = ft_strlen(s1);
	start = ft_checkidx(s1, set, 0);
	end = ft_checkidx(s1, set, s1_len);
	if (start > end)
		return (ft_strdup(""));
	str = (char *)malloc(sizeof(char) * (end - start + 1));
	if (!str)
		return (0);
	str = ft_memcpy(str, &s1[start], end - start);
	str[end - start] = '\0';
	return (str);
}
