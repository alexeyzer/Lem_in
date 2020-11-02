/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ants.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrew <andrew@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 12:32:43 by andrew            #+#    #+#             */
/*   Updated: 2020/11/02 12:32:46 by andrew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	getantsmany(int n, t_paths *head)
{
	t_paths *now;

	while (n > 0)
	{
		now = getthelitlest(head);
		now->ants_go++;
		n--;
	}
}

void	getants(t_paths *head_ofpaths, int n)
{
	if (getcountofpathsswithpathin(head_ofpaths) > 1)
		getantsmany(n, head_ofpaths);
	else
		head_ofpaths->ants_go = n;
}
