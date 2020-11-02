/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrew <andrew@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 11:11:25 by alexzudin         #+#    #+#             */
/*   Updated: 2020/11/02 09:59:52 by andrew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	clearmass(int **mass, int count)
{
	int i;

	i = 0;
	while (i < count)
	{
		free(mass[i]);
		i++;
	}
	free(mass);
	mass = NULL;
}

void	initmass(t_lemin **lemin)
{
	int **massive;
	int i;
	int j;

	i = 0;
	j = 0;
	massive = NULL;
	massive = (int**)malloc(sizeof(int*) * (*lemin)->rooms_count);
	while (i < (*lemin)->rooms_count)
	{
		massive[i] = (int*)malloc(sizeof(int) * (*lemin)->rooms_count);
		i++;
	}
	i = 0;
	while (i < (*lemin)->rooms_count)
	{
		j = 0;
		while (j < (*lemin)->rooms_count)
		{
			massive[i][j] = 0;
			j++;
		}
		i++;
	}
	(*lemin)->mass = massive;
}

void	addconnect(t_lemin **lemin, char *str)
{
	int i;
	int index1;
	int index2;

	i = 0;
	while (str[i] && str[i] != '-')
		i++;
	index1 = getindex(lemin, str);
	index2 = getindex(lemin, str + i + 1);
	(*lemin)->mass[index1][index2] = 1;
	(*lemin)->mass[index2][index1] = 1;
}

int		getindex(t_lemin **lemin, char *str)
{
	t_room	*rooms;
	int		i;

	i = 0;
	rooms = (*lemin)->rooms;
	while (str[i] && str[i] != '-')
		i++;
	while (rooms != NULL)
	{
		if (ft_strncmp(rooms->name, str, i) == 0)
			return (rooms->index);
		rooms = rooms->next;
	}
	return (-1);
}

void	antscheck(int fd, char **line, t_lemin **lemin)
{
	while (specialgetnextlin(fd, &(*line), *lemin))
	{
		if ((*line)[0] == '#' && (*line)[1] != '#')
			exitlem(lemin, "ERROR: no ants\n", line);
		else if (ft_strcmp(*line, "##start") == 0)
			exitlem(lemin, "ERROR: no ants\n", line);
		else if (ft_strcmp(*line, "##end") == 0)
			exitlem(lemin, "ERROR: no ants\n", line);
		else if ((*line)[0] == '#' && (*line)[1] == '#')
			ft_strdel(line);
		else if (ft_isnb(*line) > 0)
			break ;
		else
			exitlem(lemin, "ERROR: no ants\n", line);
		ft_strdel(line);
	}
	if (*line == NULL || **line == '\0')
		exitlem(lemin, "ERROR\n", line);
	(*lemin)->ants_count = ft_atoi(*line);
	if ((*lemin)->ants_count <= 0 || (*lemin)->ants_count > 2147483647)
		exitlem(lemin, "ERROR: with ants\n", line);
	ft_strdel(line);
}
