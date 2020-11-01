/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   findbest.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexzudin <alexzudin@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 14:45:09 by alexzudin         #+#    #+#             */
/*   Updated: 2020/11/01 09:27:30 by alexzudin        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void    findbest(t_lemin *lemin)
{
        t_solution *now_sol;

        now_sol = lemin->head_solution;
        addpathtomass(lemin, now_sol->headpaths->headpath);
        while (findspecial(lemin))
                newsolution(lemin, now_sol);
        now_sol->movements = getmovements(now_sol->headpaths, lemin->ants_count);
}

void newsolution(t_lemin *lemin, t_solution *lastsolution)
{
        t_path *newpath;
		int i;

        newpath = solv_path(lemin);
        if (newpath == NULL)
                return ;
        addpathtomass(lemin, newpath);
        if (checksamerooms(lemin) >= 0)
		{
            cleanpath(&newpath);
		}
        else if (checksamerooms(lemin) < 0)
        {
            if ((i = checkperesech(lemin)) == -1)
                addpathtopaths(lastsolution->headpaths, newpath);
        }
}

void addpathtomass(t_lemin *lemin, t_path *solved_path)
{
    while (solved_path != NULL)
    {
        lemin->mass[solved_path->from][solved_path->to] = 2;
        lemin->mass[solved_path->to][solved_path->from] = 3;
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
                return (i);
            j++;
        }
        i++;
    }
    return (-1);
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
                                count++;
                        j++;
                }
                if (count > 1)
                        return (i);
                i++;
        }
        return (-1);
}
