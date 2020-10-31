/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants_go.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguiller <aguiller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 11:49:16 by andrew            #+#    #+#             */
/*   Updated: 2020/10/31 15:04:08 by aguiller         ###   ########.fr       */
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
			if(current->ant && current->next->ant && !current->next->next)
				push(current, lemin);
			//printf("b=%d, f=%d\n", ant_scan_b(current), ant_scan_f(current));
			if(!ant_scan_b(current) && !current->next->ant && ant_scan_f(current))
				push(current, lemin);
			current = current->next;
		}
	}
}

t_path *getpathbyparam(t_path *path, int to, int from)
{
	while (path)
	{
		if (path->from == from && path->to == to)
			return (path);
		path = path->next;
	}
	return (NULL);
}

t_path *getlustpath(t_path *path)
{
	t_path *now;
	int to;
	int from;
	
	now = path;
	while (now != NULL)
	{
		if (now->ant && now->next != NULL)
		{
			to = now->to;
			from = now->from;
		}
		now = now->next;
	}
	now = getpathbyparam(path, to ,from);
	return (now);
}

void	move_ants_second(t_lemin *lemin, t_path *path)
{
	t_path	*current;

	current = getlustpath(path);
	while (current != NULL)
	{
		if (current->ant && current->next)
		{
			if (!current->next->ant)
				push(current, lemin);
		}
		else if (current->ant)
			push(current, lemin);
		current = current->prev;
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

void 	ant_to_path(t_lemin *lemin, t_paths *paths, int ant)
{
	char 	*room;
	
	move_ants(lemin, paths->headpath);
	if (paths->ants_go && !paths->headpath->ant)
	{
		paths->headpath->ant = ant;
		room = find_room(lemin->rooms, paths->headpath->to);
		ft_printf("L%d-%s ", ant, room);
		paths->ants_go--;
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

int isallpathsclear(t_paths *headpaths)
{
	int result;

	result = 0;
	while (headpaths != NULL)
	{
		result = result + is_path_clear(headpaths);
		headpaths = headpaths->next;
	}
	return (result);
}

void 	ants_go(t_lemin *lemin)
{
	int		ant;
	t_paths *paths;
	
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
	while (!isallpathsclear(paths))
	{
		paths = lemin->bestsolution->headpaths;
		while (paths != NULL)
		{
			move_ants_second(lemin, paths->headpath);
			paths = paths->next;
		}
		ft_printf("\n");
	}
}