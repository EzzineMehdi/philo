/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   roles.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezzine <mezzine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 13:35:57 by mezzine           #+#    #+#             */
/*   Updated: 2024/02/12 13:57:28 by mezzine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	eat(t_philo *p)
{
	t_prog_status	*prog;

	prog = p->prog_satus;
	sem_wait(prog->forks);
	message_printer(p, 'f');
	sem_wait(prog->forks);
	message_printer(p, 'f');
	sem_wait(p->last_meal.lock);
	p->last_meal.last_meal = current_time();
	sem_post(p->last_meal.lock);
	message_printer(p, 'e');
	time_to_sleep(p->prog_satus->time_to_eat);
	sem_wait(p->meal_lock);
	p->meal_eaten++;
	sem_post(p->meal_lock);
	sem_post(prog->forks);
	sem_post(prog->forks);
}

void	sleep_m(size_t time, t_philo *p)
{
	message_printer(p, 's');
	time_to_sleep(time);
}

int	time_check(t_philo *p)
{
	int	d;

	sem_wait(p->last_meal.lock);
	d = current_time() - p->last_meal.last_meal > p->prog_satus->time_to_die;
	sem_post(p->last_meal.lock);
	return (d);
}

void	*_7day(void *ph)
{
	t_prog_status	*prog;
	size_t			n;
	t_philo			*h;

	h = (t_philo *)ph;
	prog = h->prog_satus;
	n = prog->meal_to_eat;
	while (1)
	{
		if (full_check(h))
			return (NULL);
		if (time_check(h))
			break ;
		usleep(500);
	}
	message_printer(h, 'd');
	ft_lstclear(&h, h->prog_satus->philo_num);
	exit(1);
}
