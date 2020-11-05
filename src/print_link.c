/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_link.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrew <andrew@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 22:06:07 by andrew            #+#    #+#             */
/*   Updated: 2020/11/05 23:09:08 by andrew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	print_link2(t_lemin *l)
{
	int	x;
	int	y;

	x = 0;
	while (x < l->rooms_count)
	{
		y = 0;
		ft_printf(BLUE"|%2d %s", x, GREEN"|"BLUE);
		while (y < l->rooms_count)
		{
			ft_printf(" %s|", l->mass[x][y] > 0 ? GREEN"*"BLUE : " ");
			y++;
		}
		ft_printf("\n");
		x++;
	}
}

void	print_link(t_lemin *l)
{
	int x;

	x = 0;
	if (l->rooms_count > 50)
	{
		ft_printf(RED"Too many rooms fo print :(\n"NO);
		return ;
	}
	ft_printf(GREEN" ****Links****\n"BLUE);
	print_line(l->rooms_count * 3.6, BLUE);
	ft_printf("|   ");
	while (x < l->rooms_count)
		ft_printf("|%2d", x++);
	ft_printf("|\n");
	print_line(l->rooms_count * 3.6, GREEN);
	print_link2(l);
	print_line(l->rooms_count * 3.6, BLUE);
	ft_printf("\n"NO);
}
