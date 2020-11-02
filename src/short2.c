/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   short2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrew <andrew@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 21:33:56 by alexzudin         #+#    #+#             */
/*   Updated: 2020/11/02 12:11:07 by andrew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			makeshort2(t_pathsolver *pathsolver, t_lemin *lemin, int count)
{
	while (pathsolver->pathtosolve != NULL && pathsolver->path == NULL)
	{
		if (pathsolver->pathtosolve != NULL && pathsolver->path == NULL)
		{
			if (count > 1)
				chosebest(pathsolver, lemin);
			else if (count == 1)
			{
				if (pathsolver->pathtosolve->path_solver->path != NULL && \
				pathsolver->pathtosolve->path_solver->pathtosolve == NULL)
					connectpath(pathsolver, lemin);
				else if (pathsolver->pathtosolve->path_solver->len_path\
				== 2147483647)
				{
					pathsolver->len_path = 2147483647;
					break ;
				}
				else
					makeshort(pathsolver->pathtosolve->path_solver, lemin);
			}
		}
	}
}

void			makeshort(t_pathsolver *pathsolver, t_lemin *lemin)
{
	int count;
	int flag;

	flag = 1;
	count = getcountofpaths(pathsolver->pathtosolve);
	makeshort2(pathsolver, lemin, count);
	if (pathsolver->pathtosolve == NULL && pathsolver->path == NULL)
		pathsolver->len_path = 2147483647;
}
