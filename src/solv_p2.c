/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solv_p2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexzudin <alexzudin@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 17:19:32 by alexzudin         #+#    #+#             */
/*   Updated: 2020/10/28 20:01:58 by alexzudin        ###   ########.fr       */
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

int	createitog(int to, t_pathsolver *now, t_queue **queue, t_lemin *lemin)
{
	if (now->pathtosolve != NULL)
		cleanpathtosolve(&(now->pathtosolve));
	now->len_path = 1;
	now->path = createpath(now->index, to);
	if (now->index == lemin->start->index)
		scpecialclearqueue(queue);
	return (0);
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

void addpaths(t_lemin *l, t_queue **queue, int *v, t_pathsolver *now)
{
	int i;
	int run;

	i = 0;
	run = 1;
	while (i < l->rooms_count && run)
	{
		if ((l->mass[now->index][i] == 1 || l->mass[now->index][i] == -1)
			&& v[i] == 0)
		{
			if (i == l->end->index)
				run = createitog(i, now, queue, l);
			else
			{
				v[i] = 1;
				if (now->pathtosolve == NULL)
					now->pathtosolve = createpathtosolve(i, *queue);
				else
					addpathstosolve(now->pathtosolve, i, *queue);
			}
		}
		i++;
	}
}