/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezzine <mezzine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 17:54:08 by mezzine           #+#    #+#             */
/*   Updated: 2024/02/10 21:42:36 by mezzine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	killer(t_philo *h)
{
	int	n;
	int	i;

	n = h->prog_satus->philo_num;
	i = 1;
	while (i <= n)
	{
		kill(h->pid, SIGKILL);
		h = h->next;
		i++;
	}
}

void	wait_processes(t_prog_status *prog, t_philo *h)
{
	size_t	i;
	int		s;

	i = 1;
	while (i <= prog->philo_num)
	{
		waitpid(-1, &s, 0);
		if (s)
		{
			killer(h);
			break ;
		}
		i++;
	}
}

void	free_all(t_philo **h)
{
	sem_close((*h)->prog_satus->print);
	sem_close((*h)->prog_satus->forks);
	ft_lstclear(h, (*h)->prog_satus->philo_num);
	sem_unlink("/lock");
	sem_unlink("/print");
	sem_unlink("/forks");
	sem_unlink("/last_meal_lock");
	sem_unlink("/meal_lock");
}

void	*one_philo(void *ph)
{
	t_philo	*p;

	p = (t_philo *)ph;
	p->prog_satus->start = current_time();
	p->last_meal.last_meal = current_time();
	_7day(p);
	return (NULL);
}
