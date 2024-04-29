/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezzine <mezzine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 16:36:45 by mezzine           #+#    #+#             */
/*   Updated: 2024/02/09 19:06:55 by mezzine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	time_to_sleep(size_t time, t_philo *p)
{
	size_t	start;

	if (time == 0)
		return ;
	start = current_time();
	while (current_time() - start < time && check_prog_status(p->prog_satus))
		usleep(500);
}

int	meal_eaten_check(t_philo *p, int n)
{
	int	d;

	pthread_mutex_lock(&p->meal_lock);
	d = p->meal_eaten == n;
	pthread_mutex_unlock(&p->meal_lock);
	return (d);
}

long	ft_atoi(const char *str)
{
	int				s;
	unsigned long	n;

	n = 0;
	s = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-')
	{
		s = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (*str && *str >= '0' && *str <= '9')
	{
		n *= 10;
		n += *str - '0';
		str++;
	}
	return (n * s);
}

int	prog_init(int ac, char **av, t_prog_status *prog)
{
	if (ac < 5 || ac > 6)
		return (-1);
	if (!parse(ac, av))
		return (-1);
	prog->start = 0;
	prog->p_status = 1;
	pthread_mutex_init(&prog->lock, NULL);
	pthread_mutex_init(&prog->print, NULL);
	prog->philo_num = ft_atoi(av[1]);
	prog->time_to_die = ft_atoi(av[2]);
	prog->time_to_eat = ft_atoi(av[3]);
	prog->time_to_sleep = ft_atoi(av[4]);
	prog->meal_to_eat = -1;
	if (ac == 6)
		prog->meal_to_eat = ft_atoi(av[5]);
	return (0);
}
