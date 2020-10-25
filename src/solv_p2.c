/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solv_p2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexzudin <alexzudin@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 17:19:32 by alexzudin         #+#    #+#             */
/*   Updated: 2020/10/25 22:59:24 by alexzudin        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_pathtosolve *createpathtosolve(int index, t_queue *queue)
{
	t_pathtosolve *head_paths;

	head_paths = NULL;
	if (!(head_paths = (t_pathtosolve*)malloc(sizeof(t_pathtosolve))))
		return (NULL);
	head_paths->next = NULL;
	head_paths->path_solver = createpathsolver(index);
	queueadd(queue, head_paths->path_solver);
	return (head_paths);
}

void	createitog(int to, t_pathsolver *now)
{
	if (now->pathtosolve != NULL)
		cleanpathtosolve(&(now->pathtosolve));
	now->len_path = 1;
	now->path = createpath(now->index, to);
}

void cleanpathtosolve(t_pathtosolve **head)
{
	if (*head == NULL)
		return ;
	while((*head)->next != NULL)
    {
        cleanpathtosolve(&((*head)->next));
        (*head)->next = NULL;
    }
	cleanpathsolver(&((*head)->path_solver));
    free(*head);
    *head = NULL;
}

void addpathstosolve(t_pathtosolve *paths, int index, t_queue *queue)
{
	if (paths == NULL)
		return ;
	while (paths->next != NULL)
		paths = paths->next;
	paths->next = createpathtosolve(index, queue);
}

void addpaths(t_lemin *lem, t_queue *queue, int *visit, t_pathsolver *now)
{
	int i;
	int run;

	i = 0;
	run = 1;
	while (i < lem->rooms_count && run)
	{
		if (lem->mass[now->index][i] == 1 && visit[i] == 0)
		{
			if (i == lem->end->index)
			{
				run = 0;
				createitog(i, now);
			}
			else
			{
				visit[i] = 1;
				if (now->pathtosolve == NULL)
					now->pathtosolve = createpathtosolve(i, queue);
				else
					addpathstosolve(now->pathtosolve, i, queue);
			}
		}
		i++;
	}
}