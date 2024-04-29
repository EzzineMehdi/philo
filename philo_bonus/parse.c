/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezzine <mezzine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 19:41:40 by mezzine           #+#    #+#             */
/*   Updated: 2024/02/07 22:43:14 by mezzine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	valid_number(char *s)
{
	if (*s == '+')
		s++;
	if (!*s)
		return (0);
	while (*s)
	{
		if (!(*s >= '0' && *s <= '9'))
			return (0);
		s++;
	}
	return (1);
}

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	if (*s == '+')
		s++;
	while (*s == '0')
		s++;
	while (*s)
	{
		i++;
		s++;
	}
	return (i);
}

int	parse(int ac, char **av)
{
	int	i;

	i = 1;
	while (i < ac)
	{
		if (!valid_number(av[i]) || ft_strlen(av[i]) > 10
			|| ft_atoi(av[i]) > INT_MAX)
			return (0);
		i++;
	}
	return (1);
}
