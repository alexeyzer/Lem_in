/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants_go2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrew <andrew@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 13:08:50 by andrew            #+#    #+#             */
/*   Updated: 2020/11/02 13:10:06 by andrew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		ant_scan_f(t_path *path)
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

int		ant_scan_b(t_path *path)
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
			if (current->ant && !current->next->ant \
			&& (!current->prev || current->prev->ant))
				push(current, lemin);
			if (current->ant && current->next->ant \
			&& !current->next->next)
				push(current, lemin);
			if (!ant_scan_b(current) && !current->next->ant \
			&& ant_scan_f(current))
				push(current, lemin);
			current = current->next;
		}
	}
}

int		is_path_clear(t_paths *paths)
{
	t_path	*p;
	t_paths *ps;

	ps = paths;
	while (ps)
	{
		p = ps->headpath;
		while (p)
		{
			if (p->ant > 0 && p->next)
				return (0);
			p = p->next;
		}
		ps = ps->next;
	}
	return (1);
}

int		isallpathsclear(t_paths *headpaths)
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
