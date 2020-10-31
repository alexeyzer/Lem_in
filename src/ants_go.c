/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants_go.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrew <andrew@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 11:49:16 by andrew            #+#    #+#             */
/*   Updated: 2020/10/30 14:13:23 by andrew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

char	*find_room(t_room *room, int index)
{
	while (room->index != index)
		room = room->next;
	return (room->name);
}

void push(t_path *current, t_lemin *lemin)
{
	char *room;
	
	room = find_room(lemin->rooms, current->next->to);
	ft_printf("L%d-%s ", current->ant, room);
	current->next->ant = current->ant;
	current->ant = 0;
}

int ant_scan_f(t_path *path)
{
	t_path *p;

	p = path->next;
	while (p)
	{
		if (p->ant)
			return (1);
		p = p->next;
	}
	return (0);
}

int ant_scan_b(t_path *path)
{
	t_path *p;

	p = path->prev;
	while (p)
	{
		if (p->ant)
			return (1);
		p = p->prev;
	}
	return (0);
}

void	move_ants(t_lemin *lemin, t_path *path)
{
	t_path	*current;

	while (path->ant)
	{
		current = path;
		while (current->next)
		{
			//if(current->prev)
			//	ft_printf("ant=%d, path =%s,  prev->ant=%d, prec->path=%s\n", current->ant, find_room(lemin->rooms, current->to), current->next->ant, find_room(lemin->rooms, current->next->to));
			if (current->ant && !current->next->ant && (!current->prev || current->prev->ant))
				push(current, lemin);
			getchar();
			if(current->ant && current->next->ant && !current->next->next)
				push(current, lemin);
			getchar();
			//printf("b=%d, f=%d\n", ant_scan_b(current), ant_scan_f(current));
			if(!ant_scan_b(current) && !current->next->ant && ant_scan_f(current))
				push(current, lemin);
			getchar();
			current = current->next;
		}
	}
}

void print_path(t_path *p)
{
	while(p)
	{
		ft_printf("%d\n", p->ant);
		p = p->next;
	}
}

void 	ant_to_path(t_lemin *lemin, t_paths *path, int ant)
{
	char 	*room;
	
	move_ants(lemin, path->headpath);
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
			if(p->ant > 0 && p->next)
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
	
	paths = lemin->bestsolution->headpaths;
	ant = 1;
	while (ant <= lemin->ants_count)
	{
		while (paths)
		{
			ant_to_path(lemin, paths, ant++);
			paths = paths->next;
		}
		ft_printf("\n");
		paths = lemin->bestsolution->headpaths;
	}
	while (!is_path_clear(paths))
	{
		path = paths->headpath;
		while(path->next)
		{
			//print_path(paths->headpath);
			//getchar();
			move_ants(lemin, path);
			path = path->next;
			ft_printf("\n");
			getchar();
		}
		paths = paths->next;
	}
}