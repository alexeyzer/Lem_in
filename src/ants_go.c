/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants_go.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguiller <aguiller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 11:49:16 by andrew            #+#    #+#             */
/*   Updated: 2020/11/02 15:22:44 by aguiller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

char	*find_room(t_room *room, int index)
{
	while (room->index != index)
		room = room->next;
	return (room->name);
}

void	push(t_path *current, t_lemin *lemin)
{
	char *room;

	room = find_room(lemin->rooms, current->next->to);
	ft_printf("L%d-%s ", current->ant, room);
	current->next->ant = current->ant;
	current->ant = 0;
}

void	move_ants_second(t_lemin *lemin, t_path *path)
{
	t_path	*current;

	current = getlustpath(path);
	while (current != NULL)
	{
		if (current->ant && current->next)
			push(current, lemin);
		current = current->prev;
	}
}

void	ant_to_path(t_lemin *lemin, t_paths *paths, int *ant)
{
	char	*room;

	move_ants_second(lemin, paths->headpath);
	if (paths->ants_go && (!paths->headpath->ant || \
	paths->headpath->to == lemin->end->index))
	{
		paths->headpath->ant = *ant;
		room = find_room(lemin->rooms, paths->headpath->to);
		ft_printf("L%d-%s ", *ant, room);
		paths->ants_go--;
		*ant = *ant + 1;
	}
}

void	ants_go(t_lemin *lemin)
{
	int		ant;
	t_paths *paths;

	paths = lemin->head_solution->headpaths;
	ant = 1;
	while (ant <= lemin->ants_count)
	{
		while (paths)
		{
			ant_to_path(lemin, paths, &ant);
			paths = paths->next;
		}
		ft_printf("\n");
		paths = lemin->head_solution->headpaths;
	}
	while (!is_path_clear(lemin->head_solution->headpaths))
	{
		paths = lemin->head_solution->headpaths;
		while (paths != NULL)
		{
			move_ants_second(lemin, paths->headpath);
			paths = paths->next;
		}
		ft_printf("\n");
	}
}
