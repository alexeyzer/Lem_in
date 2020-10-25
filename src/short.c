/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   short.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexzudin <alexzudin@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 21:33:56 by alexzudin         #+#    #+#             */
/*   Updated: 2020/10/25 23:33:47 by alexzudin        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	makeshort(t_pathsolver *pathsolver)
{
	int count;

	count = getcountofpaths(pathsolver->pathtosolve);
	while (pathsolver->pathtosolve != NULL && pathsolver->path == NULL)
	{
		if (pathsolver->pathtosolve != NULL && pathsolver->path == NULL)
		{
			if (count > 1)
				chosebest(pathsolver);
			else if (count == 1)
			{
				if (pathsolver->pathtosolve->path_solver->path != NULL && pathsolver->pathtosolve->path_solver->pathtosolve == NULL)
					connectpath(pathsolver);
				else if (pathsolver->pathtosolve->path_solver->len_path == 2147483647)
				{
					pathsolver->len_path = 2147483647;
					break;
				}
				else
					makeshort(pathsolver->pathtosolve->path_solver);
			}
		}
	}
	if (pathsolver->pathtosolve == NULL && pathsolver->path == NULL)
		pathsolver->len_path = 2147483647;
}

void connectpath(t_pathsolver *pathsolver)
{
	pathsolver->len_path = 1 + pathsolver->pathtosolve->path_solver->len_path;
	pathsolver->path = createpath(pathsolver->index, pathsolver->pathtosolve->path_solver->index);
	pathsolver->path->next = pathsolver->pathtosolve->path_solver->path;
	pathsolver->pathtosolve->path_solver->path = NULL;
	cleanpathtosolve(&(pathsolver->pathtosolve));
}

void chosebest(t_pathsolver *pathsolver)
{
	int min;
	t_pathtosolve *pathtosolve;

	pathtosolve = pathsolver->pathtosolve;
	while (pathtosolve != NULL)
	{
		if (pathtosolve->path_solver->path == NULL)
			makeshort(pathtosolve->path_solver);
		pathtosolve = pathtosolve->next;
	}
	pathtosolve = pathsolver->pathtosolve;
	min = pathtosolve->path_solver->len_path;
	pathtosolve = pathtosolve->next;
	while (pathtosolve != NULL)
	{
		if (pathtosolve->path_solver->len_path < min)
			min = pathtosolve->path_solver->len_path;
		pathtosolve = pathtosolve->next;
	}
	pathtosolve = getpath(pathsolver->pathtosolve, min);
	pathsolver->len_path = 1 + pathtosolve->path_solver->len_path;
	pathsolver->path = createpath(pathsolver->index, pathtosolve->path_solver->index);
	pathsolver->path->next = pathtosolve->path_solver->path;
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