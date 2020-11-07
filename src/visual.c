/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguiller <aguiller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 15:02:23 by andrew            #+#    #+#             */
/*   Updated: 2020/11/07 12:24:26 by aguiller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	print_help(void)
{
	ft_printf("enter: [file] - print input file\n");
	ft_printf("       [room] - rooms table\n");
	ft_printf("       [link] - links table\n");
	ft_printf("       [path] - paths table\n");
	ft_printf("       [all]  - print all\n");
	ft_printf("       [go]   - ants launch and exit\n\n");
}

int		parseline(char *line, t_visual *v)
{
	v->all = 0;
	v->file = 0;
	v->link = 0;
	v->go = 0;
	v->path = 0;
	v->room = 0;
	if (!ft_strcmp("file", line))
		v->file = 1;
	else if (!ft_strcmp("room", line))
		v->room = 1;
	else if (!ft_strcmp("link", line))
		v->link = 1;
	else if (!ft_strcmp("path", line))
		v->path = 1;
	else if (!ft_strcmp("all", line))
		v->all = 1;
	else if (!ft_strcmp("go", line))
		v->go = 1;
	else
	{
		print_help();
		return (1);
	}
	return (0);
}

int		print(t_lemin *lemin, t_visual *v)
{
	v->file ? fileprint(lemin) : 0;
	v->room ? print_room(lemin) : 0;
	v->link ? print_link(lemin) : 0;
	v->path ? print_path(lemin) : 0;
	if (v->go)
		return (0);
	if (v->all)
	{
		fileprint(lemin);
		print_room(lemin);
		print_link(lemin);
		print_path(lemin);
	}
	return (1);
}

void	visual(t_lemin *lemin)
{
	int			flag;
	char		*line;
	t_visual	*v;

	v = NULL;
	(v = ft_memalloc(sizeof(t_visual))) ? 0 : exit(0);
	flag = 1;
	print_help();
	while (flag)
	{
		if (!(flag = get_next_line(0, &line)))
			break ;
		if (!parseline(line, v))
			flag = print(lemin, v);
		if (line)
			free(line);
	}
	free(v);
}
