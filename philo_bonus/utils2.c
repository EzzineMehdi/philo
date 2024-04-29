/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezzine <mezzine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 16:36:45 by mezzine           #+#    #+#             */
/*   Updated: 2024/02/12 14:49:29 by mezzine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

pid_t	fork_error(t_philo *h)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		free_all(&h);
		exit (1);
	}
	return (pid);
}

void	time_to_sleep(size_t time)
{
	size_t	start;

	if (time == 0)
		return ;
	start = current_time();
	while (current_time() - start < time)
		usleep(500);
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
	sem_unlink("print");
	sem_unlink("forks");
	sem_unlink("last_meal_lock");
	sem_unlink("meal_lock");
	if (ac < 5 || ac > 6)
		return (-1);
	if (!parse(ac, av))
		return (-1);
	prog->start = 0;
	prog->p_status = 1;
	prog->print = sem_open("print", O_CREAT, 0666, 1);
	prog->philo_num = ft_atoi(av[1]);
	prog->forks = sem_open("forks", O_CREAT, 0666, prog->philo_num);
	prog->time_to_die = ft_atoi(av[2]);
	prog->time_to_eat = ft_atoi(av[3]);
	prog->time_to_sleep = ft_atoi(av[4]);
	prog->meal_to_eat = -1;
	if (ac == 6)
		prog->meal_to_eat = ft_atoi(av[5]);
	return (0);
}
