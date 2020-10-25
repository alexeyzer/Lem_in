/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solv_p4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexzudin <alexzudin@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 18:31:07 by alexzudin         #+#    #+#             */
/*   Updated: 2020/10/25 23:44:07 by alexzudin        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	processqueue(t_lemin *lem, t_queue **queue, int *visit)
{
	t_queue *old;

	while (*queue != NULL)
	{
		addpaths(lem, *queue, visit, (*queue)->path_solver);
		old = (*queue);
		(*queue) = (*queue)->next;
		old->next = NULL;
		old->path_solver = NULL;
		free(old);
	}
}

char *namebyindex(t_room *rooms, int index)
{
	if (rooms->index == index)
		return (rooms->name);
	else
		return namebyindex(rooms->next, index);
	
}