/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movments.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguiller <aguiller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 12:45:47 by aguiller          #+#    #+#             */
/*   Updated: 2020/10/27 22:44:58 by aguiller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int getmovements(t_paths *head_ofpaths, int n)
{
    int movements;

    getants(head_ofpaths, n);
    movements = 0;
    while (head_ofpaths != NULL)
    {
        movements = movements + getlenpath(head_ofpaths->headpath) + (head_ofpaths->ants_go) - 1;
        head_ofpaths = head_ofpaths->next;
    }
    return (movements);
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
            compareto = now->next;
        }
    }
}

void getants(t_paths *head_ofpaths, int n)
{
    t_paths *now;
    t_paths *compareto;

    now = head_ofpaths;
    compareto = now->next;
    if (getcountofpathsswithpathin(head_ofpaths) > 1)
        getantsmany(head_ofpaths, n, now, compareto);
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