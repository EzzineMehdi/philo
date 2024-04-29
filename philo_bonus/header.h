/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezzine <mezzine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 19:10:02 by mezzine           #+#    #+#             */
/*   Updated: 2024/02/11 18:30:57 by mezzine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H

# define HEADER_H

# include <unistd.h>
# include <sys/time.h>
# include <stdio.h>
# include <stdlib.h>
# include <semaphore.h>
# include <pthread.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include <limits.h>

typedef struct s_prog_status
{
	size_t	time_to_die;
	size_t	time_to_eat;
	size_t	time_to_sleep;
	int		meal_to_eat;
	int		p_status;
	size_t	start;
	size_t	philo_num;
	sem_t	*print;
	sem_t	*forks;
}	t_prog_status;

typedef struct s_meal
{
	size_t	last_meal;
	sem_t	*lock;
}	t_meal;

typedef struct s_philo
{
	pid_t			pid;
	int				num;
	t_prog_status	*prog_satus;
	t_meal			last_meal;
	int				meal_eaten;
	sem_t			*meal_lock;
	struct s_philo	*next;
}				t_philo;

void	ft_lstadd_back(t_philo **lst, t_philo *new);

t_philo	*ft_lstnew(int i, t_prog_status *prog);
t_philo	*ft_lstlast(t_philo *lst);
size_t	current_time(void);
void	eat(t_philo *p);
void	sleep_m(size_t time, t_philo *p);
void	*_7day(void *ph);
int		check_prog_status(t_prog_status *prog);
void	message_printer(t_philo *p, char c);
int		full_check(t_philo *p);
int		prog_init(int ac, char **av, t_prog_status *prog);
void	ft_lstclear(t_philo **lst, size_t num);
void	free_all(t_philo **h);
void	wait_processes(t_prog_status *prog, t_philo *h);
int		parse(int ac, char **av);
long	ft_atoi(const char *str);
void	killer(t_philo *h);
int		all_full(t_philo *h);
void	time_to_sleep(size_t time);
pid_t	fork_error(t_philo *h);

#endif