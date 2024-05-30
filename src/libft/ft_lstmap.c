/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunrlee <eunrlee@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 18:26:51 by eunrlee           #+#    #+#             */
/*   Updated: 2022/11/16 15:49:24 by eunrlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

static t_list	*del_lst(t_list *ret, void *tmp, void (*del)(void *))
{
	del(tmp);
	ft_lstclear(&ret, del);
	return (0);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*ret;
	void	*tmp;

	if (lst == NULL || !f || !del)
		return (0);
	tmp = f(lst->content);
	ret = ft_lstnew(tmp);
	if (!ret)
		return (del_lst(ret, tmp, del));
	new = ret;
	lst = lst -> next;
	while (lst)
	{
		tmp = f(lst->content);
		new -> next = ft_lstnew(tmp);
		if (!(new->next))
			return (del_lst(ret, tmp, del));
		new = new -> next;
		lst = lst -> next;
	}
	return (ret);
}
