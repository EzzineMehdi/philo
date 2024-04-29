/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   roles.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezzine <mezzine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 13:35:57 by mezzine           #+#    #+#             */
/*   Updated: 2024/02/10 15:21:00 by mezzine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	eat(t_philo *p)
{
	pthread_mutex_lock(&p->fork);
	message_printer(p, 'f');
	pthread_mutex_lock(&p->next->fork);
	message_printer(p, 'f');
	pthread_mutex_lock(&p->last_meal.lock);
	p->last_meal.last_meal = current_time();
	pthread_mutex_unlock(&p->last_meal.lock);
	message_printer(p, 'e');
	time_to_sleep(p->prog_satus->time_to_eat, p);
	pthread_mutex_lock(&p->meal_lock);
	p->meal_eaten++;
	pthread_mutex_unlock(&p->meal_lock);
	pthread_mutex_unlock(&p->fork);
	pthread_mutex_unlock(&p->next->fork);
}

void	sleep_m(size_t time, t_philo *p)
{
	message_printer(p, 's');
	time_to_sleep(time, p);
}

int	time_check(t_philo *p)
{
	int	d;

	pthread_mutex_lock(&p->last_meal.lock);
	d = current_time() - p->last_meal.last_meal > p->prog_satus->time_to_die;
	pthread_mutex_unlock(&p->last_meal.lock);
	return (d);
}

void	waitp(t_philo *h)
{
	size_t	i;
	size_t	n;

	i = 0;
	n = h->prog_satus->philo_num;
	while (i < n)
	{
		if (last_meal_check(h))
			i++;
		h = h->next;
	}
}

void	_7day(t_philo *h)
{
	t_prog_status	*prog;
	size_t			n;

	prog = h->prog_satus;
	n = prog->meal_to_eat;
	waitp(h);
	while (1)
	{
		if (all_full(h))
		{
			pthread_mutex_lock(&prog->lock);
			prog->p_status = 0;
			pthread_mutex_unlock(&prog->lock);
			return ;
		}
		if (time_check(h))
			break ;
		h = h->next;
	}
	pthread_mutex_lock(&prog->lock);
	prog->p_status = 0;
	pthread_mutex_unlock(&prog->lock);
	message_printer(h, 'd');
	return ;
}
