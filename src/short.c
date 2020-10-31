/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   short.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcolossu <bcolossu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 21:33:56 by alexzudin         #+#    #+#             */
/*   Updated: 2020/10/31 17:16:09 by bcolossu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	makeshort(t_pathsolver *pathsolver, t_lemin *lemin)
{
	int count;

	count = getcountofpaths(pathsolver->pathtosolve);
	while (pathsolver->pathtosolve != NULL && pathsolver->path == NULL)
	{
		if (pathsolver->pathtosolve != NULL && pathsolver->path == NULL)
		{
			if (count > 1)
				chosebest(pathsolver, lemin);
			else if (count == 1)
			{
				if (pathsolver->pathtosolve->path_solver->path != NULL && pathsolver->pathtosolve->path_solver->pathtosolve == NULL)
					connectpath(pathsolver, lemin);
				else if (pathsolver->pathtosolve->path_solver->len_path == 2147483647)
				{
					pathsolver->len_path = 2147483647;
					break ;
				}
				else
					makeshort(pathsolver->pathtosolve->path_solver, lemin);
			}
		}
	}
	if (pathsolver->pathtosolve == NULL && pathsolver->path == NULL)
		pathsolver->len_path = 2147483647;
}

void	connectpath(t_pathsolver *pathsolver, t_lemin *lemin)
{
	if (pathsolver->pathtosolve->path_solver->len_path == 2147483647)
		pathsolver->len_path = 2147483647;
	else
		pathsolver->len_path = lemin->mass[pathsolver->index][pathsolver->pathtosolve->path_solver->index] + pathsolver->pathtosolve->path_solver->len_path;
	pathsolver->path = createpath(pathsolver->index, pathsolver->pathtosolve->path_solver->index);
	pathsolver->path->next = pathsolver->pathtosolve->path_solver->path;
	if (pathsolver->path->next != NULL)
		pathsolver->path->next->prev = pathsolver->path;
	pathsolver->pathtosolve->path_solver->path = NULL;
	cleanpathtosolve(&(pathsolver->pathtosolve));
}

void	chosebest(t_pathsolver *pathsolver, t_lemin *lemin)
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
		pathsolver->len_path = lemin->mass[pathsolver->index][pathsolver->pathtosolve->path_solver->index] + pathtosolve->path_solver->len_path;
	pathsolver->path = createpath(pathsolver->index, pathtosolve->path_solver->index);
	pathsolver->path->next = pathtosolve->path_solver->path;
	if (pathsolver->path->next != NULL)
		pathsolver->path->next->prev = pathsolver->path;
	pathtosolve->path_solver->path = NULL;
	cleanpathtosolve(&(pathsolver->pathtosolve));
}

t_pathtosolve *getpath(t_pathtosolve *head, int len)
{
	if (head->path_solver->len_path == len)
		return head;
	else 
		return (getpath(head->next, len));
}

int getcountofpaths(t_pathtosolve *pathtosolve)
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