/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   findbest_p2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguiller <aguiller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 16:00:40 by alexzudin         #+#    #+#             */
/*   Updated: 2020/11/02 15:29:31 by aguiller         ###   ########.fr       */
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

void	cleanpaths(t_paths *pathsheader)
{
	while (pathsheader->next != NULL)
	{
		cleanpaths(pathsheader->next);
		pathsheader->next = NULL;
	}
	cleanpath(&(pathsheader->headpath));
	pathsheader->headpath = NULL;
	free(pathsheader);
}

void	clearsolution(t_lemin *lemin)
{
	t_solution *sol;

	if (lemin->head_solution != NULL)
	{
		sol = lemin->head_solution;
		lemin->head_solution = NULL;
		cleanpaths(sol->headpaths);
		sol->headpaths = NULL;
		free(sol);
	}
}
