/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezzine <mezzine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 18:17:52 by mezzine           #+#    #+#             */
/*   Updated: 2024/02/11 18:30:53 by mezzine          ###   ########.fr       */
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

void	role_giver(t_philo *p)
{
	pthread_t	tid;

	sem_wait(p->last_meal.lock);
	p->last_meal.last_meal = current_time();
	sem_post(p->last_meal.lock);
	pthread_create(&tid, NULL, _7day, p);
	pthread_detach(tid);
	if (p->num % 2)
		time_to_sleep(60);
	while (1)
	{
		eat(p);
		if (full_check(p))
			break ;
		sleep_m(p->prog_satus->time_to_sleep, p);
		message_printer(p, 't');
	}
	ft_lstclear(&p, p->prog_satus->philo_num);
	exit(0);
}

void	processes_creator(t_philo *h)
{
	t_prog_status	*prog;
	size_t			i;

	prog = h->prog_satus;
	i = 0;
	prog = h->prog_satus;
	prog->start = current_time();
	while (i < prog->philo_num)
	{
		h->pid = fork_error(h);
		if (!h->pid)
			role_giver(h);
		i++;
		h = h->next;
	}
	wait_processes(prog, h);
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
	processes_creator(h);
	free_all(&h);
	return (0);
}
