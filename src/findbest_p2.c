/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   findbest_p2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexzudin <alexzudin@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 16:00:40 by alexzudin         #+#    #+#             */
/*   Updated: 2020/11/01 09:32:47 by alexzudin        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int findspecial(t_lemin *lemin)
{
	int *massive;
	int result;

	result = 0;
	massive = massvisited(lemin);
	result = find(&massive, lemin->start->index, lemin);
	free(massive);
	return (result);
}

void scpecialclearqueue(t_queue **head)
{
	 while((*head)->next != NULL)
    {
        scpecialclearqueue(&((*head)->next));
        (*head)->next = NULL;
    }
    free(*head);
    *head = NULL;
}