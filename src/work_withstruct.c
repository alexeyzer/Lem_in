/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_withstruct.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrew <andrew@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 16:09:53 by alexzudin         #+#    #+#             */
/*   Updated: 2020/11/02 12:27:02 by andrew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_room	*addrooms(t_lemin **lemin, char **str)
{
	t_room	*rooms;
	t_room	*first;

	rooms = (*lemin)->rooms;
	while (rooms->next != NULL)
		rooms = rooms->next;
	first = createroom(str, lemin, 0);
	rooms->next = first;
	return (first);
}

t_room	*createroom(char **str, t_lemin **lemin, int i)
{
	t_room *first;

	while ((*str)[i] != ' ')
		i++;
	if (!(first = malloc(sizeof(t_room))))
		return (NULL);
	first->name = ft_strsub((*str), 0, i);
	i++;
	first->coord_x = ft_atoi((*str) + i);
	while ((*str)[i] != ' ')
		i++;
	i++;
	first->coord_y = ft_atoi((*str) + i);
	if ((checkroom(lemin, first->coord_x, first->coord_y, first->name) < 0))
	{
		free(first);
		exitlem(lemin, "Error wrong room params", str);
	}
	if ((*lemin)->rooms == NULL)
		first->index = 0;
	else
		first->index = lastroom((*lemin)->rooms)->index + 1;
	first->next = NULL;
	return (first);
}

int		checkroom(t_lemin **lemin, int cx, int cy, char *n)
{
	t_room *rooms;

	rooms = (*lemin)->rooms;
	if (cx > 2147483647 || cx < -2147483648)
		return (-1);
	if (cy > 2147483647 || cy < -2147483648)
		return (-1);
	if (n[0] == 'L')
		return (-1);
	if (rooms != NULL)
	{
		if (ft_strcmp(n, rooms->name) == 0 || \
		(rooms->coord_x == cx && rooms->coord_y == cy))
			return (-1);
		rooms = rooms->next;
	}
	return (1);
}

t_room	*lastroom(t_room *rooms)
{
	while (rooms->next != NULL)
		rooms = rooms->next;
	return (rooms);
}
