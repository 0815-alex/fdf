/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_lst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 19:33:36 by astein            #+#    #+#             */
/*   Updated: 2023/05/26 01:49:40 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

/**
 * @brief	basic linked list function specified for struct 't_node'
 * 			-> see: 'ft_lstlast'
 * 
 * @param	node	pointer to the first node of the list
 * @return t_node*	pointer to the last node of the list 'lst'
 */
static t_node	*node_last(t_node *node)
{
	if (!node)
		return (NULL);
	while (node->next)
	{
		node = node->next;
	}
	return (node);
}

/**
 * @brief	basic linked list function specified for struct 't_node'
 * 			-> see: 'ft_lstadd_front'
 * 
 * @param	lst	double pointer to the first node of the list
 * @param	new	node to be added to the list 'lst'
 */
void	node_add_front(t_node **lst, t_node *new)
{
	new->next = *lst;
	*lst = new;
}

/**
 * @brief	basic linked list function specified for struct 't_node'
 * 			-> see: 'ft_lstadd_back'
 * 
 * @param	lst	double pointer to the first node of the list
 * @param	new	node to be added to the list 'lst'
 */
void	node_add_back(t_node **lst, t_node *new)
{
	if (!*lst)
		node_add_front(lst, new);
	else
		node_last(*lst)->next = new;
}

/**
 * @brief	frees all the nodes linked to the given node 'node'
 * 
 * @param	node	pointer to the first node of the list
 */
void	free_node_lst(t_node *node)
{
	t_node	*current;
	t_node	*next;

	current = node;
	while (current != NULL)
	{
		next = current->next;
		free(current->pnt);
		free(current);
		current = next;
	}
}
