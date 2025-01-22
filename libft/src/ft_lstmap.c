/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keomalima <keomalima@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 14:19:36 by kricci-d          #+#    #+#             */
/*   Updated: 2025/01/01 17:27:20 by keomalima        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*node;
	t_list	*new_list;

	new_list = NULL;
	if (!f || !del || !lst)
		return (NULL);
	while (lst)
	{
		node = malloc(sizeof(t_list));
		if (!node)
		{
			ft_lstclear(&new_list, del);
			return (NULL);
		}
		node->content = f(lst->content);
		node->next = NULL;
		ft_lstadd_back(&new_list, node);
		lst = lst->next;
	}
	return (new_list);
}
