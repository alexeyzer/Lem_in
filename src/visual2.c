/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrew <andrew@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 15:02:23 by andrew            #+#    #+#             */
/*   Updated: 2020/11/05 23:08:03 by andrew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	print_room(t_lemin *l)
{
	t_room *room;

	room = l->rooms;
	ft_printf(GREEN" ****Rooms****\n"NO);
	ft_printf(BLUE"----------------\n");
	ft_printf("|index |  NAME |\n");
	ft_printf("----------------\n"NO);
	while (room)
	{
		ft_printf(BLUE"| %4d | %5s |\n", room->index, room->name);
		room = room->next;
	}
	ft_printf("----------------\n\n"NO);
}

int		calc_width(t_lemin *l)
{
	t_paths	*path;
	t_path	*p;
	int		max_len;
	int		max_name;

	path = l->head_solution->headpaths;
	max_len = 0;
	max_name = 0;
	while (path)
	{
		if (path->len_path > max_len)
			max_len = path->len_path;
		path = path->next;
	}
	p = l->head_solution->headpaths->headpath;
	while (p)
	{
		if ((int)ft_strlen(find_room(l->rooms, p->from)) > max_name)
			max_name = ft_strlen(find_room(l->rooms, p->from));
		p = p->next;
	}
	return (max_len * (max_name + 7));
}

void	print_line(int len, char *s)
{
	while (len--)
		ft_printf("%s-", s);
	ft_printf("\n");
}

void	print_path2(t_paths *paths, t_lemin *l)
{
	t_path	*path;

	while (paths)
	{
		ft_printf("|%4d  |", paths->ants_go);
		path = paths->headpath;
		ft_printf("  %s->%s", find_room(l->rooms, path->from), \
		find_room(l->rooms, path->to));
		while (path->next)
		{
			path = path->next;
			ft_printf("->%s", find_room(l->rooms, path->to));
		}
		printf("\n"NO);
		paths = paths->next;
	}
}

void	print_path(t_lemin *l)
{
	int	len;

	if ((len = calc_width(l)) > 200)
	{
		ft_printf(RED"Too long path for print :(\n"NO);
		return ;
	}
	ft_printf(GREEN" ****Paths****\n"BLUE);
	print_line(len + 11, BLUE);
	ft_printf(BLUE"| ants |  %-*s|\n", len, "Path");
	print_line(len + 11, BLUE);
	print_path2(l->head_solution->headpaths, l);
	print_line(len + 11, BLUE);
}
