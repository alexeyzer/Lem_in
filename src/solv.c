/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solv.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguiller <aguiller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 15:44:24 by alexzudin         #+#    #+#             */
/*   Updated: 2020/10/27 22:37:08 by aguiller         ###   ########.fr       */
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

	solution_head = createsolution(createpaths(solv_path(lemin)));
	solution_head->movements = getmovements(solution_head->headpaths, lemin->ants_count);
	lemin->head_solution = solution_head;
	if (getlenpath(solution_head->headpaths->headpath) < lemin->ants_count)
	{
		ft_printf("hey looking for new solution");
		return ;
	}
	else
	{
		ft_printf("%d\n", getlenpath(solution_head->headpaths->headpath));
		ft_printf("%d\n", solution_head->movements);
		printpath(solution_head->headpaths->headpath, lemin);
		//solved;
		//printantsmoves();
		//free all
		//end
	}
	//cleanpath(&fastestpath);
}