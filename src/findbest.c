/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   findbest.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexzudin <alexzudin@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 14:45:09 by alexzudin         #+#    #+#             */
/*   Updated: 2020/10/31 23:34:17 by alexzudin        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_solution *findbest(t_lemin *lemin)
{
        t_solution *now_sol;

        now_sol = lemin->head_solution;
        addpathtomass(lemin, now_sol->headpaths->headpath);
        while (findspecial(lemin))
                newsolution(lemin, now_sol);
        now_sol->movements = getmovements(now_sol->headpaths, lemin->ants_count);
        //min = minmovementsfromsolutions(lemin->head_solution);
        //now_sol = getsolfromsoltns(min, lemin->head_solution);
        return (now_sol);
}

void newsolution(t_lemin *lemin, t_solution *lastsolution)
{
        t_path *newpath;
		//t_paths *peresechs;
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
            else
            {
                //ft_printf("prikl\n");
				addpathtopaths(lastsolution->headpaths, newpath);
				//peresechs = findcurrentpath(lastsolution->headpaths, i);
			    //be3(peresechs->headpath, lemin);
				//be3(newpath, lemin);
				//delete(&(lastsolution->headpaths),  peresechs);
                //dellperesech(lemin);
				//addspec(lastsolution->headpaths, givepaths(lemin));
            }
        }
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

void clear(t_lemin *lemin,t_path *newpath ,int roomto)
{
        t_path *path;

        path = newpath;
        while (path != NULL && path->to != roomto)
        {
                lemin->mass[path->from][path->to] = 1;
                lemin->mass[path->to][path->from] = 1;
                path = path->next;
        }
        cleanpath(&newpath);
}

t_paths *findcurrentpath(t_paths *head, int i)
{
	t_path *path;
	while(head != NULL)
	{
		path = head->headpath;
		while (path != NULL)
		{
			if (path->to == i)
				return (head);
			path = path->next;
		}
		head = head->next;
	}
	return (NULL);
}

void be3(t_path *path, t_lemin *lemin)
{
	while (path != NULL)
    {
        if (lemin->mass[path->to][path->from] == 2 || lemin->mass[path->to][path->from] == 4)
		{
			lemin->mass[path->from][path->to] = 4;
            lemin->mass[path->to][path->from] = 4;
		}
		else
		{
			lemin->mass[path->from][path->to] = 3;
			lemin->mass[path->from][path->to] = -1;
		}
        path = path->next;
    }
}

void delete(t_paths **head, t_paths *todelete)
{
	t_paths *now;
	t_path *current;
	t_paths *delete;


	now = *head;
	if (now == todelete)
	{
		current = now->headpath;
		now->next->headpath = NULL;
		delete = now;
		(*head) = (*head)->next;
		cleanpath(&current);
		free(delete);
		return ;
	}
	deletep2(head, todelete);
}

void deletep2(t_paths **head, t_paths *todelete)
{
	t_paths *now;
	int flag;
	t_path *current;
	t_paths *delete;

	flag = 1;
	now = *head;
	while (now != NULL && now->next != NULL && flag == 1)
	{
		if (now->next == todelete)
			flag = 0;
		if (flag == 1)
			now = now->next;
	}
	if (flag == 0)
	{
		current = now->next->headpath;
		now->next->headpath = NULL;
		delete = now->next;
		now->next = now->next->next;
		cleanpath(&current);
		free(delete);
	}
}

void addspec(t_paths *head, t_paths *new)
{
	if (head == NULL)
		return ;
	while (head->next != NULL)
		head = head->next;
	head->next = new;
}
