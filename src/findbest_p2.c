/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   findbest_p2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexzudin <alexzudin@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 16:00:40 by alexzudin         #+#    #+#             */
/*   Updated: 2020/10/29 20:13:11 by alexzudin        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void dellperesech(t_lemin	*lemin)
{
	int i;
	int j;

	i = 0;
	while (i < lemin->rooms_count)
	{
		j = 0;
		while (j < lemin->rooms_count)
		{
			if (lemin->mass[i][j] == 2 && lemin->mass[j][i] == 2)
			{
				lemin->mass[i][j] = 0;
				lemin->mass[j][i] = 0;
			}
			j++;
		}
		i++;
	}
}

t_paths *givepaths(t_lemin *lemin)
{
	t_path *new;
	t_paths *head;
	int index;
	int i;

	i = 0;
	head = NULL;
	index = lemin->start->index;
	while (i < lemin->rooms_count)
	{
		if (lemin->mass[index][i] == 2)
		{
			new = createpath(index, i);
			connectpathspecial(lemin, i, new);
			if (head == NULL)
				head = createpaths(new);
			else
				addpathtopaths(head, new);
		}
		i++;
	}
	return (head);
}

int connectpathspecial(t_lemin *lemin, int index, t_path *now_path)
{
	int i;

	i = 0;
	while (i < lemin->rooms_count)
	{
		if (lemin->mass[index][i] == 2)
		{
			if (i == lemin->end->index)
			{
				littlehelpfunc(now_path, index, i);
				return (1);
			}
			else
			{
				littlehelpfunc(now_path, index, i);
				connectpathspecial(lemin, i, now_path->next);
				return (1);
			}
		}
		i++;
	}
	return (0);
}

t_paths *becomelastpaths(t_paths *head)
{
	while (head->next != NULL)
		head = head->next;
	return (head);
}

int findspecial(t_lemin *lemin)
{
	int *massive;
	int result;

	result = 0;
	massive = massvisited(lemin);
	result = find(&massive, lemin->start->index, lemin);
	free(massive);
	return (result);
}