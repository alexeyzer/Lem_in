/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movments.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguiller <aguiller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 12:45:47 by aguiller          #+#    #+#             */
/*   Updated: 2020/10/27 13:35:17 by aguiller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int getmovements(t_paths *head_ofpaths, int n)
{
    int number_new;
    int lenpath;

    lenpath = getlenpath(head_ofpaths->headpath);
    if (getcountofpathsswithpathin(head_ofpaths) > 1)
    {
        if (n > lenpath)
        {
            number_new = n - lenpath;
            head_ofpaths->ants_go = lenpath + (lenpath - 1);
            return (lenpath + (lenpath - 1) + getmovements(head_ofpaths->next, n));
        }
        else
        {
            head_ofpaths->ants_go = lenpath + (n - 1);
            return (lenpath + (n - 1)); 
        }
    }
    else
    {
        head_ofpaths->ants_go = lenpath + (n - 1);
        return (lenpath + (n - 1));
    }
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