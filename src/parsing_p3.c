/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_p3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguiller <aguiller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 19:25:17 by aguiller          #+#    #+#             */
/*   Updated: 2020/11/02 19:28:34 by aguiller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		isroomspecial(t_lemin **lemin, char *str, size_t end)
{
	t_room *rooms;

	rooms = (*lemin)->rooms;
	if (str == NULL)
		return (-1);
	while (rooms != NULL)
	{
		if (ft_strncmp(str, rooms->name, end) == 0 &&
			ft_strlen(rooms->name) == end)
			return (1);
		rooms = rooms->next;
	}
	return (-1);
}

int		roomspec(char *strisxod, t_lemin **lemin, int plus)
{
	int		i;
	int		sp;
	int		len;
	char	*str;

	str = strisxod + plus;
	i = 0;
	sp = 0;
	len = ft_strlen(str);
	while (i < len)
	{
		if (str[i] == '-')
			sp++;
		i++;
	}
	if (sp == 1)
		return (basic(strisxod, plus));
	i = 1;
	while (i <= len)
	{
		if (isroomspecial(lemin, str, i) == 1)
			break ;
		i++;
	}
	return (i);
}

int		basic(char *strisxod, int plus)
{
	int		i;
	char	*str;

	str = strisxod + plus;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '-')
			return (i);
		i++;
	}
	return (i);
}
