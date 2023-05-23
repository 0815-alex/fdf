/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 19:33:36 by astein            #+#    #+#             */
/*   Updated: 2023/05/23 22:34:16 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

t_node	*node_last(t_node *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
	{
		lst = lst->next;
	}
	return (lst);
}

void	node_add_front(t_node **lst, t_node *new)
{
	new->next = *lst;
	*lst = new;
}

void	node_add_back(t_node **lst, t_node *new)
{
	if (!*lst)
		node_add_front(lst, new);
	else
		node_last(*lst)->next = new;
}

void	free_list(t_node *head)
{
	t_node	*current;
	t_node	*next;

	current = head;
	while (current != NULL)
	{
		next = current->next;
		free(current->pnt);
		free(current);
		current = next;
	}
}
