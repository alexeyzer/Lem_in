/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solv_p3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexzudin <alexzudin@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 17:51:30 by alexzudin         #+#    #+#             */
/*   Updated: 2020/10/25 23:06:16 by alexzudin        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	cleanpath(t_path **head)
{
	if (head == NULL)
		return ;
	while((*head)->next != NULL)
    {
        cleanpath(&((*head)->next));
        (*head)->next = NULL;
    }
    free(*head);
    *head = NULL;
}

t_path *createpath(int from, int to)
{
	t_path *head;

	head = NULL;
	if (!(head = (t_path*)malloc(sizeof(t_path))))
		return (NULL);
	head->from = from;
	head->to = to;
	head->next = NULL;
	return (head);
}

void	cleanpathsolver(t_pathsolver **pathsolver)
{
	if (*pathsolver != NULL)
	{
		if ((*pathsolver)->path != NULL)
			cleanpath(&((*pathsolver)->path));
		if ((*pathsolver)->pathtosolve != NULL)
			cleanpathtosolve(&((*pathsolver)->pathtosolve));
		free((*pathsolver));
		*pathsolver = NULL;
	}
}