/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrew <andrew@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 20:59:30 by aguiller          #+#    #+#             */
/*   Updated: 2020/11/02 12:18:03 by andrew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_file	*createfile(char *str)
{
	t_file *head;

	head = NULL;
	if (!(head = (t_file*)malloc(sizeof(t_file))))
		return (NULL);
	head->line = ft_strdup(str);
	head->next = NULL;
	return (head);
}

void	addtofile(t_file *head, char *str)
{
	while (head->next != NULL)
		head = head->next;
	head->next = createfile(str);
}

int		specialgetnextlin(const int fd, char **line, t_lemin *lemin)
{
	int status;

	status = get_next_line(fd, line);
	if (lemin->head_file == NULL)
		lemin->head_file = createfile(*line);
	else
		addtofile(lemin->head_file, *line);
	return (status);
}

void	cleanfile(t_file *head)
{
	while (head->next != NULL)
	{
		cleanfile(head->next);
		head->next = NULL;
	}
	ft_strdel(&(head->line));
	free(head);
	head = NULL;
}

void	littlehelpfunc(t_path *now_path, int index, int i)
{
	now_path->next = createpath(index, i);
	if (now_path->next != NULL)
		now_path->next->prev = now_path;
}
