/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movments.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexzudin <alexzudin@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 12:45:47 by aguiller          #+#    #+#             */
/*   Updated: 2020/10/30 16:33:13 by alexzudin        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int getmovements(t_paths *head_ofpaths, int n)
{
    int movements;
    t_paths *now;

    now = head_ofpaths;
    if (getcountofpathsswithpathin(head_ofpaths) > 1)
        sortpaths(head_ofpaths);
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

    t_paths *wait;

    while (n > 0)
    {
        if (now->ants_go + getlenpath(now->headpath) <= compareto->ants_go + getlenpath(compareto->headpath))
        {
            if ((wait = compare(head_ofpaths, now, compareto)))
                now = wait;
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

void sortpaths(t_paths *head)
{
    int count;
    t_paths *now;
    t_path *swap;
    int swapnbr;
    int i;

    i = 0;
    count = getcountofpathsswithpathin(head);
    while (i < count)
    {
        now = head;
        while (now != NULL)
        {
            if (now->next != NULL)
                if (now->len_path > now->next->len_path)
                {
                    swap = now->headpath;
                    swapnbr = now->len_path;
                    now->headpath = now->next->headpath;
                    now->len_path = now->next->len_path;
                    now->next->headpath = swap;
                    now->next->len_path = swapnbr;
                }
            now = now->next;
        }
        i++;
    }
}

t_paths *compare(t_paths *head_ofpaths, t_paths *now, t_paths *compareto)
{
    t_paths *nowiter;
    int prev;

    nowiter = head_ofpaths;
    while (nowiter != now)
    {
        prev = nowiter->ants_go + getlenpath(nowiter->headpath);
        if (prev <= compareto->ants_go + getlenpath(compareto->headpath)
            && prev <= now->ants_go + getlenpath(now->headpath))
            return (nowiter);
        nowiter = nowiter->next;
    }
    return (NULL);
}