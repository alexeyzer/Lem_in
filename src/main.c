/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrew <andrew@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 09:50:12 by andrew            #+#    #+#             */
/*   Updated: 2020/11/05 23:11:25 by andrew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_lemin	*init_lemin(int fd)
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
	lemin->fd = fd;
	return (lemin);
}

void	error(void)
{
	ft_printf("ERROR: Invalid file\n");
	exit(0);
}

int		main(int argc, char **argv)
{
	int		fd;
	t_lemin	*lemin;

	fd = 0;
	lemin = NULL;
	if ((argc == 3 && argv[1][0] == '-' && argv[1][1] == 'p') || argc == 2)
	{
		fd = open(argv[argc == 3 ? 2 : 1], O_RDONLY);
		if (fd < 0)
			error();
	}
	else
		exitlem(&lemin, argc == 1 ? "ERROR: no args\n" \
		: "ERROR: too many args\n", NULL);
	lemin = init_lemin(fd);
	parsing(fd, &lemin);
	isvalid(&lemin);
	mainsolver(lemin);
	if (argc == 3 && argv[1][0] == '-' && argv[1][1] == 'p')
		visual(lemin);
	fileprint(lemin);
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
