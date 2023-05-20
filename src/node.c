/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 18:50:54 by astein            #+#    #+#             */
/*   Updated: 2023/05/20 16:45:16 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	print_net(t_model *model)
{
	t_node	*cur_node;

	dbg_printf(model, start_block, "print_net");
	cur_node = model->net;
	while (cur_node)
	{
		print_node(model, cur_node);
		(cur_node) = (cur_node)->next;
	}
	dbg_printf(model, end_block, "print_net");
}

void	print_node(t_model *model, t_node *node)
{
	if (node == NULL)
		dbg_printf(model, no_block, "(no node)");
	else
	{
		dbg_printf(model, no_block, "(%i|%i|%i)", node->x, node->y, node->z);
	}
}

char	*node2str(t_model *model, t_node *node)
{
	char	*str;

	if (node == NULL)
		return ("(no node)");
	else
	{
		str = ft_strjoin("(", ft_itoa(node->x));
		str = ft_strjoin(str, "|");
		str = ft_strjoin(str, ft_itoa(node->y));
		str = ft_strjoin(str, "|");
		str = ft_strjoin(str, ft_itoa(node->z));
		str = ft_strjoin(str, ")");
		return (str);
	}
}

t_node	*node_last(t_node *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
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
