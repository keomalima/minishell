/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lthan <lthan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 14:07:23 by kricci-d          #+#    #+#             */
/*   Updated: 2025/03/05 09:57:10 by lthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_lstclear(t_list **lst)
{
	t_list	*temp;

	if (lst)
	{
		while (*lst)
		{
			temp = *lst;
			*lst = (*lst)->next;
			if (temp->content)
			{
				free(temp->content);
				temp->content = NULL;
			}
			free(temp);
			temp = NULL;
		}
	}
}
