/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   findbest_p3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexzudin <alexzudin@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 17:19:13 by alexzudin         #+#    #+#             */
/*   Updated: 2020/10/28 18:16:17 by alexzudin        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int minmovementsfromsolutions(t_solution *head)
{
	int min;
	t_solution *now;

	min = head->movements;
	now = head->next;
	while (now != NULL)
	{
		if (now->movements < min)
			min = now->movements;
		now = now->next;
	}
	return (min);
}

t_solution *getsolfromsoltns(int i, t_solution *head)
{
	if (head == NULL)
		return (NULL);
	if (head->movements == i)
		return (head);
	else
		return (getsolfromsoltns(i, head->next));
	
}

t_paths *copypahs(t_paths *head_tocopy)
{
	t_paths *newhead;

	newhead = createpaths(head_tocopy->headpath);
	head_tocopy = head_tocopy->next;
	while(head_tocopy != NULL)
	{
		addpathtopaths(newhead, head_tocopy->headpath);
		head_tocopy = head_tocopy->next;
	}
	return (newhead);
}