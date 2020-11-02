/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants_go2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguiller <aguiller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 13:08:50 by andrew            #+#    #+#             */
/*   Updated: 2020/11/02 15:26:33 by aguiller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

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

t_path	*getpathbyparam(t_path *path, int to, int from)
{
	while (path != NULL)
	{
		if (path->from == from && path->to == to)
			return (path);
		path = path->next;
	}
	return (NULL);
}

t_path	*getlustpath(t_path *path)
{
	t_path	*now;
	int		to;
	int		from;

	now = path;
	to = -1;
	from = -1;
	while (now != NULL)
	{
		if (now->ant && now->next != NULL)
		{
			to = now->to;
			from = now->from;
		}
		now = now->next;
	}
	now = getpathbyparam(path, to, from);
	return (now);
}
