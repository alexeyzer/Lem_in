/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   findbest.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexzudin <alexzudin@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 14:45:09 by alexzudin         #+#    #+#             */
/*   Updated: 2020/10/28 18:18:29 by alexzudin        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_solution *findbest(t_lemin *lemin)
{
	t_solution *now_sol;
	int min;

	now_sol = lemin->head_solution;
	addpathtomass(lemin, now_sol->headpaths->headpath);
	while (findspecial(lemin))
	{
		now_sol->next = newsolution(lemin, now_sol);
		if (now_sol->next == NULL)
			break;
		else
		{
			now_sol->next->movements = getmovements(now_sol->next->headpaths, lemin->ants_count);
			now_sol = now_sol->next;
		}
	}
	min = minmovementsfromsolutions(lemin->head_solution);
	now_sol = getsolfromsoltns(min, lemin->head_solution);
	return (now_sol);
}

t_solution *newsolution(t_lemin *lemin, t_solution *lastsolution)
{
	t_path *newpath;
	t_solution *new;

	newpath = solv_path(lemin);
	if (newpath == NULL)
		return (NULL);
	addpathtomass(lemin, newpath);
	if (checksamerooms(lemin) == 1)
		cleanpath(&newpath);
	else
	{
		if (checkperesech(lemin) == 0)
		{
			new = createsolution(copypahs(lastsolution->headpaths));
			addpathtopaths(new->headpaths, newpath);
			return (new);
		}
		else
		{
			dellperesech(lemin);
			new = createsolution(givepaths(lemin));
			return (new);
		}
	}
	return (NULL);
}

void addpathtomass(t_lemin *lemin, t_path *solved_path)
{
	while (solved_path != NULL)
	{
		lemin->mass[solved_path->from][solved_path->to] = 2;
		if (lemin->mass[solved_path->to][solved_path->from] != 2)
			lemin->mass[solved_path->to][solved_path->from] = -1;
		solved_path = solved_path->next;
	}
}

int checkperesech(t_lemin *lemin)
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
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int checksamerooms(t_lemin *lemin)
{
	int i;
	int j;
	int count;

	i = 0;
	while (i < lemin->rooms_count && i != lemin->end->index)
	{
		count = 0;
		j = 0;
		while (j < lemin->rooms_count)
		{
			if (lemin->mass[i][j] == -1)
			{
				ft_printf("%d->%d", i, j);
				count++;
			}
			j++;
		}
		if (count > 1)
			return (1);
		i++;
	}
	return (0);
}