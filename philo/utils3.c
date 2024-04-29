/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezzine <mezzine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 17:54:08 by mezzine           #+#    #+#             */
/*   Updated: 2024/02/10 21:04:51 by mezzine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	last_meal_check(t_philo *p)
{
	while (1)
	{
		pthread_mutex_lock(&p->last_meal.lock);
		if (p->last_meal.last_meal > 0)
		{
			pthread_mutex_unlock(&p->last_meal.lock);
			break ;
		}
		pthread_mutex_unlock(&p->last_meal.lock);
	}
	return (1);
}

void	wait_threads(t_prog_status *prog, pthread_t *tid)
{
	size_t	i;

	i = 0;
	while (i < prog->philo_num)
	{
		pthread_join(tid[i], NULL);
		i++;
	}
	free(tid);
}

void	free_all(t_philo **h)
{
	pthread_mutex_destroy(&(*h)->prog_satus->lock);
	pthread_mutex_destroy(&(*h)->prog_satus->print);
	ft_lstclear(h, (*h)->prog_satus->philo_num);
}

int	one_philo_check(t_philo *h)
{
	pthread_t	tid;

	if (h->prog_satus->philo_num != 1)
		return (0);
	pthread_create(&tid, NULL, one_philo, h);
	pthread_join(tid, NULL);
	free_all(&h);
	return (1);
}

void	*one_philo(void *ph)
{
	t_philo	*p;

	p = (t_philo *)ph;
	p->prog_satus->start = current_time();
	p->last_meal.last_meal = current_time();
	pthread_mutex_lock(&p->fork);
	message_printer(p, 'f');
	_7day(p);
	pthread_mutex_unlock(&p->fork);
	return (NULL);
}
