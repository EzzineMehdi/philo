/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezzine <mezzine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 18:17:52 by mezzine           #+#    #+#             */
/*   Updated: 2024/04/30 00:26:08 by mezzine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_philo	*philo_creator(t_prog_status *prog)
{
	t_philo	*h;
	size_t	n;

	n = 1;
	h = NULL;
	while (n <= prog->philo_num)
	{
		ft_lstadd_back(&h, ft_lstnew(n, prog));
		n++;
	}
	ft_lstlast(h)->next = h;
	return (h);
}

void	hange_prog(t_prog_status *prog)
{
	while (1)
	{
		pthread_mutex_lock(&prog->lock);
		if (prog->start != 0)
		{
			pthread_mutex_unlock(&prog->lock);
			break ;
		}
		pthread_mutex_unlock(&prog->lock);
	}
}

void	*role_giver(void *ph)
{
	t_philo	*p;

	p = (t_philo *)ph;
	hange_prog(p->prog_satus);
	pthread_mutex_lock(&p->last_meal.lock);
	p->last_meal.last_meal = current_time();
	pthread_mutex_unlock(&p->last_meal.lock);
	if (p->num % 2 == 0)
		time_to_sleep(60, p);
	while (check_prog_status(p->prog_satus))
	{
		eat(p);
		sleep_m(p->prog_satus->time_to_sleep, p);
		message_printer(p, 't');
	}
	return (NULL);
}

void	pthread_creator(t_philo *h)
{
	t_prog_status	*prog;
	pthread_t		*tid;
	size_t			i;

	i = 0;
	prog = h->prog_satus;
	tid = malloc(sizeof(pthread_t) * prog->philo_num);
	if (!tid)
		return ;
	while (i < prog->philo_num)
	{
		pthread_create(&tid[i], NULL, role_giver, h);
		i++;
		h = h->next;
	}
	pthread_mutex_lock(&prog->lock);
	prog->start = current_time();
	pthread_mutex_unlock(&prog->lock);
	_7day(h);
	wait_threads(prog, tid);
}

int	main(int ac, char **av)
{
	t_philo			*h;
	t_prog_status	prog;

	if (prog_init(ac, av, &prog))
	{
		printf("invalid arguments\n");
		return (0);
	}
	if (prog.meal_to_eat == 0 || prog.philo_num == 0)
		return (0);
	h = philo_creator(&prog);
	if (one_philo_check(h))
		return (0);
	pthread_creator(h);
	free_all(&h);
	return (0);
}
