/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunrlee <eunrlee@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 15:22:02 by eunrlee           #+#    #+#             */
/*   Updated: 2022/11/16 15:50:02 by eunrlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

static void	ft_free(char **str, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size && str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

static size_t	check_size(char const *s, char c)
{
	size_t	i;
	size_t	size;

	i = 0;
	size = 0;
	while (s[i] == c && c != '\0')
		i++;
	if (s[i] == '\0')
		return (0);
	while (s[i] != '\0')
	{
		while (s[i] != '\0' && s[i] != c)
			i++;
		size++;
		while (s[i] == c && s[i] != '\0')
			i++;
	}
	return (size);
}

static int	str_set(char const *s, char c, char **str, size_t size)
{
	size_t	len;
	size_t	i;
	size_t	j;
	size_t	start;

	j = 0;
	i = 0;
	while (j < size)
	{
		while (s[i] != '\0' && s[i] == c)
			i++;
		start = i;
		while (s[i] != '\0' && s[i] != c)
			i++;
		len = i - start;
		str[j] = (char *)malloc(sizeof(char) * (len + 1));
		if (!str[j])
		{
			ft_free(str, size);
			return (0);
		}
		ft_strlcpy(str[j], s + start, len + 1);
		j++;
	}
	return (1);
}

char	**ft_split(char const *s, char c)
{
	size_t	size;
	char	**str;

	size = check_size(s, c);
	str = (char **)malloc(sizeof(char *) * (size + 1));
	if (!str)
		return (0);
	str[size] = 0;
	if (!str_set(s, c, str, size))
		return (0);
	return (str);
}
