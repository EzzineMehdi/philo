/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezzine <mezzine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 14:33:53 by mezzine           #+#    #+#             */
/*   Updated: 2024/02/10 21:46:06 by mezzine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	full_check(t_philo *p)
{
	int	i;

	if (p->prog_satus->meal_to_eat == -1)
		return (0);
	sem_wait(p->meal_lock);
	i = p->meal_eaten >= p->prog_satus->meal_to_eat;
	sem_post(p->meal_lock);
	return (i);
}

size_t	current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	message_printer(t_philo *p, char c)
{
	sem_wait(p->prog_satus->print);
	if (c == 'f')
		printf("%zu %i has taken a fork\n", current_time()
			- p->prog_satus->start, p->num);
	else if (c == 'e')
		printf("%zu %d is eating\n", current_time() - p->prog_satus->start,
			p->num);
	else if (c == 's')
		printf("%zu %d is sleeping\n", current_time() - p->prog_satus->start,
			p->num);
	else if (c == 't')
		printf("%zu %d is thinking\n", current_time() - p->prog_satus->start,
			p->num);
	else if (c == 'd')
	{
		printf("%zu %d died\n", current_time() - p->prog_satus->start, p->num);
		return ;
	}
	sem_post(p->prog_satus->print);
}
