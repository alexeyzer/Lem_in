/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_p2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguiller <aguiller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 16:57:06 by alexzudin         #+#    #+#             */
/*   Updated: 2020/11/02 13:40:17 by aguiller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	startend(int fd, t_lemin **lemin, char **str, int status)
{
	int old_status;

	old_status = status;
	ft_strdel(str);
	while (specialgetnextlin(fd, str, *lemin) > 0)
	{
		if ((*str)[0] == '#' && (*str)[1] != '#')
			ft_strdel(str);
		else if (ft_strcmp(*str, "##start") == 0)
			old_status = 1;
		else if (ft_strcmp(*str, "##end") == 0)
			old_status = 2;
		else if ((*str)[0] == '#' && (*str)[1] == '#')
			ft_strdel(str);
		else
			break ;
		ft_strdel(str);
	}
	if (*str == NULL || **str == '\0')
		exitlem(lemin, "ERROR: empty line\n", str);
	status = isitroom2(str, lemin, 0);
	if (status == 1 || status == 2 || status == 4)
		exitlem(lemin, "ERROR: wrong format\n", str);
	else
		add(lemin, old_status, str);
}

void	add(t_lemin **lemin, int status, char **str)
{
	if (status == 1)
	{
		if ((*lemin)->rooms == NULL)
		{
			(*lemin)->rooms = createroom(str, lemin, 0);
			(*lemin)->start = (*lemin)->rooms;
		}
		else
			(*lemin)->start = addrooms(lemin, str);
	}
	else if (status == 2)
	{
		if ((*lemin)->rooms == NULL)
		{
			(*lemin)->rooms = createroom(str, lemin, 0);
			(*lemin)->end = (*lemin)->rooms;
		}
		else
			(*lemin)->end = addrooms(lemin, str);
	}
	else if (status == 3 && (*lemin)->rooms != NULL)
		addrooms(lemin, str);
	else if (status == 3 && (*lemin)->rooms == NULL)
		(*lemin)->rooms = createroom(str, lemin, 0);
}

void	connection(t_lemin **lemin, char **str)
{
	if ((*lemin)->connection == 0)
	{
		if ((*lemin)->rooms == NULL)
			exitlem(lemin, "ERROR\n", str);
		(*lemin)->rooms_count = lastroom((*lemin)->rooms)->index + 1;
		checkconnect(lemin, str);
		initmass(lemin);
		addconnect(lemin, *str);
		(*lemin)->connection = 1;
	}
	else
	{
		checkconnect(lemin, str);
		addconnect(lemin, *str);
	}
}

void	checkconnect(t_lemin **lemin, char **str)
{
	int		i;
	int		i_start;
	char	*name1;
	char	*name2;

	i = 0;
	while ((*str)[i] && (*str)[i] != '-')
		i++;
	name1 = ft_strsub(*str, 0, i);
	i_start = ++i;
	while ((*str)[i] && (*str)[i] != '\0')
		i++;
	name2 = ft_strsub(*str, i_start, i);
	if (isroom(lemin, name1) < 0 || isroom(lemin, name2) < 0)
	{
		ft_strdel(&name1);
		ft_strdel(&name2);
		exitlem(lemin, "ERROR: connection\n", str);
	}
	else
	{
		ft_strdel(&name1);
		ft_strdel(&name2);
	}
}

int		isroom(t_lemin **lemin, char *str)
{
	t_room *rooms;

	rooms = (*lemin)->rooms;
	if (str == NULL)
		return (-1);
	while (rooms != NULL)
	{
		if (ft_strcmp(str, rooms->name) == 0)
			return (1);
		rooms = rooms->next;
	}
	return (-1);
}
