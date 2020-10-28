/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathsandsolutions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexzudin <alexzudin@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 12:08:53 by aguiller          #+#    #+#             */
/*   Updated: 2020/10/28 18:03:05 by alexzudin        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_paths     *createpaths(t_path *head)
{
    t_paths *head_paths;

    head_paths = NULL;
    if (!(head_paths = (t_paths*)malloc(sizeof(t_paths))))
        return (NULL);
    head_paths->headpath = head;
    head_paths->len_path = getlenpath(head);
    head_paths->ants_go = 0;
    head_paths->next = NULL;
    return (head_paths);
}

void        addpathtopaths(t_paths *wheretoadd ,t_path *path_toadd)
{
    while (wheretoadd->next != NULL)
        wheretoadd = wheretoadd->next;
    wheretoadd->next = createpaths(path_toadd);
}

t_solution  *createsolution(t_paths *head)
{
    t_solution *head_solution;

    head_solution = NULL;
    if (!(head_solution = (t_solution*)malloc(sizeof(t_solution))))
        return (NULL);
    head_solution->headpaths = head;
    head_solution->movements = 214748364;
    head_solution->next = NULL;
    return (head_solution);
}

void addsolution(t_solution *headsolution, t_paths *head_ofpaths)
{
    while (headsolution->next != NULL)
        headsolution = headsolution->next;
    headsolution->next = createsolution(head_ofpaths);
}