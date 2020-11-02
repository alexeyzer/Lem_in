/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   short.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrew <andrew@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 21:33:56 by alexzudin         #+#    #+#             */
/*   Updated: 2020/11/02 12:11:12 by andrew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			connectpath(t_pathsolver *pathsolver, t_lemin *lemin)
{
	if (pathsolver->pathtosolve->path_solver->len_path == 2147483647)
		pathsolver->len_path = 2147483647;
	else
		pathsolver->len_path = lemin->mass[pathsolver->index]\
		[pathsolver->pathtosolve->path_solver->index]\
		+ pathsolver->pathtosolve->path_solver->len_path;
	pathsolver->path = createpath(pathsolver->index, \
	pathsolver->pathtosolve->path_solver->index);
	pathsolver->path->next = pathsolver->pathtosolve->path_solver->path;
	if (pathsolver->path->next != NULL)
		pathsolver->path->next->prev = pathsolver->path;
	pathsolver->pathtosolve->path_solver->path = NULL;
	cleanpathtosolve(&(pathsolver->pathtosolve));
}

void			chosebest(t_pathsolver *pathsolver, t_lemin *lemin)
{
	t_pathtosolve	*pathtosolve;

	pathtosolve = pathsolver->pathtosolve;
	while (pathtosolve != NULL)
	{
		makeshort(pathtosolve->path_solver, lemin);
		pathtosolve = pathtosolve->next;
	}
	pathtosolve = getshortpath(pathsolver);
	if (pathtosolve->path_solver->len_path == 2147483647)
		pathsolver->len_path = 2147483647;
	else
		pathsolver->len_path = lemin->mass[pathsolver->index]\
		[pathsolver->pathtosolve->path_solver->index] + \
		pathtosolve->path_solver->len_path;
	pathsolver->path = createpath(pathsolver->index, \
	pathtosolve->path_solver->index);
	pathsolver->path->next = pathtosolve->path_solver->path;
	if (pathsolver->path->next != NULL)
		pathsolver->path->next->prev = pathsolver->path;
	pathtosolve->path_solver->path = NULL;
	cleanpathtosolve(&(pathsolver->pathtosolve));
}

t_pathtosolve	*getpath(t_pathtosolve *head, int len)
{
	if (head->path_solver->len_path == len)
		return (head);
	else
		return (getpath(head->next, len));
}

int				getcountofpaths(t_pathtosolve *pathtosolve)
{
	int i;

	i = 0;
	while (pathtosolve != NULL)
	{
		i++;
		pathtosolve = pathtosolve->next;
	}
	return (i);
}
