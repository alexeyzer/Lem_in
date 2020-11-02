/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguiller <aguiller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 15:21:51 by alexzudin         #+#    #+#             */
/*   Updated: 2020/11/02 13:24:49 by aguiller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	isvalid(t_lemin **lemin)
{
	if ((*lemin)->start == NULL || (*lemin)->end == NULL)
		exitlem(lemin, "ERROR: no start or end\n", NULL);
	findpathtoend(lemin);
}

void	findpathtoend(t_lemin **lemin)
{
	int *massive;

	massive = massvisited(*lemin);
	if (find(&massive, (*lemin)->start->index, *lemin) == 0)
	{
		free(massive);
		exitlem(lemin, "ERROR: no path from start to end\n", NULL);
	}
	free(massive);
}

int		find(int **massive, int index, t_lemin *lemin)
{
	int i;
	int result;

	i = 0;
	result = 0;
	while (i < lemin->rooms_count)
	{
		if ((lemin->mass[index][i] == 1 || lemin->mass[index][i] == -1) \
		&& (*massive)[i] == 0)
		{
			if (i == lemin->end->index)
				return (1);
			else
			{
				(*massive)[i] = 1;
				result = result + find(massive, i, lemin);
			}
		}
		i++;
	}
	return (result);
}

int		*massvisited(t_lemin *lemin)
{
	int i;
	int *massive;

	massive = NULL;
	if (!(massive = (int*)(malloc(sizeof(int) * lemin->rooms_count))))
		return (NULL);
	i = 0;
	while (i < lemin->rooms_count)
	{
		massive[i] = 0;
		i++;
	}
	massive[lemin->start->index] = 1;
	return (massive);
}
