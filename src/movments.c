/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movments.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexzudin <alexzudin@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 12:45:47 by aguiller          #+#    #+#             */
/*   Updated: 2020/10/28 17:58:00 by alexzudin        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int getmovements(t_paths *head_ofpaths, int n)
{
    int movements;
    t_paths *now;

    now = head_ofpaths;
    getants(head_ofpaths, n);
    movements = 0;
    while (now != NULL)
    {
        movements = movements + getlenpath(now->headpath) + (now->ants_go) - 1;
        now = now->next;
    }
    return (movements / getcountofpathsswithpathin(head_ofpaths));
}

void getantsmany(t_paths *head_ofpaths, int n, t_paths *now, t_paths *compareto)
{
    while (n > 0)
    {
        if (now->ants_go + getlenpath(now->headpath) <= compareto->ants_go + getlenpath(compareto->headpath))
        {
            if (head_ofpaths->ants_go + getlenpath(head_ofpaths->headpath) <= compareto->ants_go + getlenpath(compareto->headpath) && head_ofpaths->ants_go + getlenpath(head_ofpaths->headpath) <= now->ants_go + getlenpath(now->headpath) && now != head_ofpaths)
                now = head_ofpaths;
            else
            {
                now->ants_go = now->ants_go + 1;
                n--;
            }
        }
        else
        {
            now = now->next;
            if (now->next != NULL)
                compareto = now->next;
        }
    }
}

void getants(t_paths *head_ofpaths, int n)
{
    t_paths *now;
    t_paths *compareto;

    now = head_ofpaths;
    if (getcountofpathsswithpathin(head_ofpaths) > 1)
    {
        compareto = now->next;
        getantsmany(head_ofpaths, n, now, compareto);
    }
    else
        head_ofpaths->ants_go = n;
}

int getcountofpathsswithpathin(t_paths *head_ofpaths)
{
    int i;
    i = 0;
    while (head_ofpaths != NULL)
    {
        i++;
        head_ofpaths = head_ofpaths->next;
    }
    return (i);
}