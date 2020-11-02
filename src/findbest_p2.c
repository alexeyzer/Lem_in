/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   findbest_p2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrew <andrew@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 16:00:40 by alexzudin         #+#    #+#             */
/*   Updated: 2020/11/02 09:52:44 by andrew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		findspecial(t_lemin *lemin)
{
	int *massive;
	int result;

	result = 0;
	massive = massvisited(lemin);
	result = find(&massive, lemin->start->index, lemin);
	free(massive);
	return (result);
}

void	scpecialclearqueue(t_queue **head)
{
	while ((*head)->next != NULL)
	{
		scpecialclearqueue(&((*head)->next));
		(*head)->next = NULL;
	}
	free(*head);
	*head = NULL;
}

void	fileprint(t_lemin *lemin)
{
	t_file *now;

	now = lemin->head_file;
	while (now != NULL)
	{
		ft_printf("%s\n", now->line);
		now = now->next;
	}
}
