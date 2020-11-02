/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants_go3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrew <andrew@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 12:39:27 by andrew            #+#    #+#             */
/*   Updated: 2020/11/02 12:39:43 by andrew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_path	*getpathbyparam(t_path *path, int to, int from)
{
	while (path)
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
