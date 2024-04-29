/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezzine <mezzine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 14:33:53 by mezzine           #+#    #+#             */
/*   Updated: 2024/02/09 19:03:48 by mezzine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	check_prog_status(t_prog_status *prog)
{
	int	i;

	i = 1;
	pthread_mutex_lock(&prog->lock);
	if (!prog->p_status)
		i = 0;
	pthread_mutex_unlock(&prog->lock);
	return (i);
}

int	full_check(t_philo *p)
{
	int	i;

	pthread_mutex_lock(&p->meal_lock);
	i = p->meal_eaten >= p->prog_satus->meal_to_eat;
	pthread_mutex_unlock(&p->meal_lock);
	return (i);
}

int	all_full(t_philo *h)
{
	int	n;
	int	c;
	int	philo;

	if (h->prog_satus->meal_to_eat == -1)
		return (0);
	n = 1;
	c = 0;
	philo = h->prog_satus->philo_num;
	while (n <= philo)
	{
		if (full_check(h))
			c++;
		n++;
		h = h->next;
	}
	if (c == philo)
		return (1);
	return (0);
}

size_t	current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	message_printer(t_philo *p, char c)
{
	pthread_mutex_lock(&p->prog_satus->print);
	if (c == 'f' && check_prog_status(p->prog_satus))
		printf("%zu %i has taken a fork\n", current_time()
			- p->prog_satus->start, p->num);
	else if (c == 'e' && check_prog_status(p->prog_satus))
		printf("%zu %d is eating\n", current_time() - p->prog_satus->start,
			p->num);
	else if (c == 's' && check_prog_status(p->prog_satus))
		printf("%zu %d is sleeping\n", current_time() - p->prog_satus->start,
			p->num);
	else if (c == 't' && check_prog_status(p->prog_satus))
		printf("%zu %d is thinking\n", current_time() - p->prog_satus->start,
			p->num);
	else if (c == 'd')
		printf("%zu %d died\n", current_time() - p->prog_satus->start, p->num);
	pthread_mutex_unlock(&p->prog_satus->print);
}
