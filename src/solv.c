/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solv.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexzudin <alexzudin@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 15:44:24 by alexzudin         #+#    #+#             */
/*   Updated: 2020/10/30 16:38:14 by alexzudin        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_pathsolver	*createpathsolver(int index)
{
	t_pathsolver *pathsolver;

	pathsolver = NULL;
	pathsolver = (t_pathsolver*)malloc(sizeof(t_pathsolver));
	pathsolver->pathtosolve = NULL;
	pathsolver->len_path = 214748364;
	pathsolver->path = NULL;
	pathsolver->index = index;
	return (pathsolver);
}

t_queue *createqueue()
{
	t_queue *queue;

	queue = NULL;
	if (!(queue = (t_queue*)malloc(sizeof(t_queue))))
		return (NULL);
	queue->next = NULL;
	return (queue);
}

void queueadd(t_queue	*queue, t_pathsolver *pathsolver)
{
	if (queue == NULL)
		return ;
	while(queue->next != NULL)
		queue = queue->next;
	queue->next = createqueue();
	queue->next->path_solver = pathsolver;
}

t_path	*solv_path(t_lemin *lemin)
{
	t_queue			*queue;
	t_pathsolver	*pathsolver;
	int				*massvisit;
	t_path			*path;

	path = NULL;
	massvisit = massvisited(lemin);
	queue = createqueue();
	pathsolver = createpathsolver(lemin->start->index);
	queue->path_solver = pathsolver;
	processqueue(lemin, &queue, massvisit);
	makeshort(pathsolver, lemin);
	path = pathsolver->path;
	pathsolver->path = NULL;
	cleanpathsolver(&pathsolver);
	free(massvisit);
	return (path);
}

void mainsolver(t_lemin *lemin)
{
	t_solution *solution_head;
	t_solution *new;
	//t_paths *now;
	int i;

	i = 1;
	solution_head = createsolution(createpaths(solv_path(lemin)));
	solution_head->movements = getmovements(solution_head->headpaths, lemin->ants_count);
	lemin->head_solution = solution_head;
	//правильное решение всегда лежит в new!)
	lemin->bestsolution = findbest(lemin);
	new = lemin->bestsolution;
	/*
	ft_printf("%d\n", new->movements);
	ft_printf("%d\n", getcountofpathsswithpathin(new->headpaths));
	now = new->headpaths;
	while (now != NULL)
	{
		ft_printf("path %d\n", i);
		ft_printf("ants to go %d\n", now->ants_go);
		ft_printf("len of path %d\n", now->len_path);
		printpath(now->headpath, lemin);
		now = now->next;
		i++;
	}*/
}