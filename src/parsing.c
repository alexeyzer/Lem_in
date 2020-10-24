/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexzudin <alexzudin@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 16:29:08 by alexzudin         #+#    #+#             */
/*   Updated: 2020/10/21 20:53:28 by alexzudin        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	parsing(int fd, t_lemin **lemin)
{
	char *line;
	int status;

	line = NULL;
	antscheck(fd, &line, lemin);
	while (get_next_line(fd, &line) > 0)
    {
        if (*line == '\0')
			exitlem(lemin, "Error empty line\n", &line);
		if(line[0] == '#' && line[1] != '#')
			ft_strdel(&line);
		else
			if ((status = isitroom(&line, lemin)) > 0)
				parstostruct(fd, lemin, &line, status);
		ft_strdel(&line);
    }
}

void	parstostruct(int fd, t_lemin **lemin, char **str, int status)
{
	int old_status;

	old_status = status;
	if ((status == 1 || status == 2) && (*lemin)->connection == 0)
	{
		if (status == 1 && (*lemin)->start != NULL)
			exitlem(lemin, "Error 2 starts\n", str);
		if (status == 2 && (*lemin)->end != NULL)
			exitlem(lemin, "Error 2 ends\n", str);
		startend(fd, lemin, str, status);
	}
	else
		parstostruct2(fd, lemin, str, status);
}

void	parstostruct2(int fd, t_lemin **lemin, char **str, int status)
{
	fd = 0;
	if (status == 3 && (*lemin)->connection == 0)
		add(lemin, status, str);
	else if (status == 4)
		connection(lemin, str);
	else
		exitlem(lemin, "Error\n", str);
	
}

int		isitroom(char **str, t_lemin **lemin)
{
	int i;
	int probel;

	probel = 0;
	i = 0;
	if (ft_strcmp((*str), "##start") == 0)
		return (1);
	else if (ft_strcmp((*str), "##end") == 0)
		return (2);
	else if ((*str)[0] == '#' && (*str)[1] == '#')
		return (-1);
	else
		return (isitroom2(str, lemin, 0));
}

int		isitroom2(char **str, t_lemin **lemin, int i)
{
	int	probel;

	probel = 0;
	while ((*str)[i++] != '\0')
		if ((*str)[i] == ' ')
			probel++;
	if (probel >= 2)
	{
		i = 0;
		while ((*str)[i] != ' ')
			i++;
		i++;
		if (ft_isnb(&((*str)[i])) == 0)
			exitlem(lemin,"Error param room\n", str);
		while ((*str)[i] != ' ')
			i++;
		i++;
		if (ft_isnb(&((*str)[i])) == 0)
			exitlem(lemin,"Error param room\n", str);
		return (3);
	}
	else if (probel == 0)
		return (4);
	exitlem(lemin, "param Error\n", str);
	return (0);
}
