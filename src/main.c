/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexzudin <alexzudin@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 09:50:12 by andrew            #+#    #+#             */
/*   Updated: 2020/11/03 15:13:57 by alexzudin        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_lemin	*init_lemin(void)
{
	t_lemin *lemin;

	lemin = NULL;
	if (!(lemin = (t_lemin*)malloc(sizeof(t_lemin))))
		return (NULL);
	lemin->ants_count = 0;
	lemin->rooms_count = 0;
	lemin->rooms = NULL;
	lemin->mass = NULL;
	lemin->start = NULL;
	lemin->head_solution = NULL;
	lemin->head_file = NULL;
	lemin->connection = 0;
	lemin->end = NULL;
	return (lemin);
}

int		main(int argc, char **argv)
{
	int		fd;
	t_lemin	*lemin;

	lemin = NULL;
	fd = 0;
	if (argc == 2 || argc == 3)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd < 0)
		{
			ft_printf("ERROR: Invalid file\n");
			return (0);
		}
	}
	lemin = init_lemin();
	parsing(fd, &lemin);
	isvalid(&lemin);
	mainsolver(lemin);
	fileprint(lemin);
	if (argc == 3 && argv[2][0] == '-' && argv[2][1] == 'p')
		visual(lemin);
	ants_go(lemin);
	exitlem(&lemin, NULL, NULL);
	return (0);
}

void	exitlem(t_lemin **lemin, char *str, char **str_tofree)
{
	t_room *head;

	head = NULL;
	ft_strdel(str_tofree);
	if (str != NULL)
		ft_printf("%s", str);
	if (*lemin != NULL)
	{
		clearsolution(*lemin);
		cleanfile(((*lemin)->head_file));
		head = (*lemin)->rooms;
		(*lemin)->rooms = NULL;
		if (head != NULL)
			c_clear(head);
		if ((*lemin)->mass != NULL)
			clearmass((*lemin)->mass, (*lemin)->rooms_count);
		(*lemin)->mass = NULL;
		free(*lemin);
		*lemin = NULL;
	}
	exit(0);
}

void	c_clear(t_room *head)
{
	while (head->next != NULL)
	{
		c_clear(head->next);
		head->next = NULL;
	}
	ft_strdel(&(head->name));
	free(head);
	head = NULL;
}

void	visual(t_lemin *lemin)
{
	t_paths	*now;
	int		i;

	i = 1;
	now = lemin->head_solution->headpaths;
	while (now != NULL)
	{
		ft_printf("path %d\n", i);
		ft_printf("ants to go %d\n", now->ants_go);
		ft_printf("len of path %d\n", now->len_path);
		printpath(now->headpath, lemin);
		now = now->next;
		i++;
	}
}
