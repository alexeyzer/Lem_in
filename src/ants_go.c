/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants_go.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrew <andrew@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 11:49:16 by andrew            #+#    #+#             */
/*   Updated: 2020/10/30 11:58:12 by andrew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

char	*find_room(t_room *room, int index)
{
	while (room->index != index)
		room = room->next;
	return (room->name);
}


void	move_ant(t_lemin *lemin, t_path *path)
{
	t_path	*current;
	char 	*room;

	while (path->ant)
	{
		current = path;
		while (current->next)
		{
			if (current->ant && !current->next->ant)
			{
				room = find_room(lemin->rooms, current->next->to);
				ft_printf("L%d-%s ", current->ant, room);
				current->next->ant = current->ant;
				current->ant = 0;
				current = current->next;
			}
		}
	}
}

void 	ant_to_path(t_lemin *lemin, t_paths *path, int ant)
{
	char 	*room;
	
	move_ant(lemin, path->headpath);
	if (path->ants_go && !path->headpath->ant)
	{
		path->headpath->ant = ant;
		room = find_room(lemin->rooms, path->headpath->to);
		ft_printf("L%d-%s ", ant, room);
		path->ants_go--;
	}
}

int		is_path_clear(t_paths *paths)
{
	t_path *p;
	t_paths *ps;

	ps = paths;
	while(ps)
	{
		p = ps->headpath;
		while(p)
		{
			if(p->ant > 0)
				return(0);
			p = p->next;
		}
		ps = ps->next;
	}
	return(1);
}

void 	ants_go(t_lemin *lemin)
{
	int		ant;
	t_paths *paths;
	t_path	*path;
	
	paths = lemin->head_solution->headpaths;
	ant = 1;
	while (ant <= lemin->ants_count)
	{
		while (paths)
		{
			ant_to_path(lemin, paths, ant++);
			paths = paths->next;
		}
		ft_printf("\n");
		paths = lemin->head_solution->headpaths;
	}
	while (is_path_clear(paths))
	{
		path = paths->headpath;
		while(path)
		{
			move_ant(lemin, path);
			path = path->next;
		}
		paths = paths->next;
	}
}