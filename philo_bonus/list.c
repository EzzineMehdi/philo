/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezzine <mezzine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 17:54:02 by mezzine           #+#    #+#             */
/*   Updated: 2024/02/11 15:44:59 by mezzine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_philo	*ft_lstlast(t_philo *lst)
{
	while (lst)
	{
		if (!lst->next)
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

void	ft_lstclear(t_philo **lst, size_t num)
{
	t_philo	*l;
	t_philo	*t;
	size_t	i;

	i = 1;
	if (lst)
	{
		if (*lst)
		{
			l = *lst;
			while (i <= num)
			{
				t = l;
				l = t->next;
				free(t);
				i++;
			}
			*lst = NULL;
		}
	}
}

t_philo	*ft_lstnew(int i, t_prog_status *prog)
{
	t_philo	*n;

	n = malloc(sizeof(t_philo));
	if (!n)
		return (NULL);
	n->last_meal.lock = sem_open("last_meal_lock", O_CREAT, 0666, 1);
	n->meal_lock = sem_open("meal_lock", O_CREAT, 0666, 1);
	n->prog_satus = prog;
	n->meal_eaten = 0;
	n->last_meal.last_meal = 0;
	n->num = i;
	n->next = NULL;
	return (n);
}

void	ft_lstadd_back(t_philo **lst, t_philo *new)
{
	t_philo	*last;

	if (lst)
	{
		if (!*lst)
		{
			*lst = new;
			return ;
		}
		last = ft_lstlast(*lst);
		last->next = new;
	}
}
