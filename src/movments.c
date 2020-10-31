/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movments.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguiller <aguiller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 12:45:47 by aguiller          #+#    #+#             */
/*   Updated: 2020/10/31 19:59:58 by aguiller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int getmovements(t_paths *head_ofpaths, int n)
{
    int movements;
    t_paths *now;
	int count;

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
	count = getcountofpathsswithpathin(head_ofpaths);
    return ((movements / count) + (movements % count));
}

t_paths *getpathsbyparam(t_paths *head, int i)
{
    while (head != NULL)
    {
        if ((head->ants_go) + head->len_path == i)
            return (head);
        head = head->next;
    }
    return (NULL);
}

t_paths *getthelitlest(t_paths *head)
{
    int min;
    t_paths *now;

    now = head;
    min = now->ants_go + now->len_path;
    now = now->next;
    while (now != NULL)
    {
        if (now->ants_go + now->len_path < min)
            min = now->ants_go + now->len_path;
        now = now->next;
    }
    return (getpathsbyparam(head, min));
}

void getantsmany(int n, t_paths *head)
{

    t_paths *now;

    while (n > 0)
    {
        now = getthelitlest(head);
        now->ants_go++;
        n--;
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
        getantsmany(n, now);
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