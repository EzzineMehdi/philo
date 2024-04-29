/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezzine <mezzine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 17:54:02 by mezzine           #+#    #+#             */
/*   Updated: 2024/02/04 13:35:53 by mezzine          ###   ########.fr       */
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
				pthread_mutex_destroy(&t->meal_lock);
				pthread_mutex_destroy(&t->fork);
				pthread_mutex_destroy(&t->last_meal.lock);
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
	pthread_mutex_init(&n->fork, NULL);
	pthread_mutex_init(&n->last_meal.lock, NULL);
	pthread_mutex_init(&n->meal_lock, NULL);
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
