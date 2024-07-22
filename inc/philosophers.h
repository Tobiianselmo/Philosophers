/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanselmo <tanselmo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 15:41:52 by tanselmo          #+#    #+#             */
/*   Updated: 2024/07/22 19:36:44 by tanselmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>

# define SLEEP "is sleeping"
# define FORK_L "has taken LEFT fork"
# define FORK_R "has taken RIGHT fork"
# define FORK "has taken a fork"
# define EAT "is eating"
# define THINK "is thinking"
# define DIED "died"

typedef struct	s_vars
{
	int				n_philo;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				must_eat;
	int				death;
	long			start;
	pthread_mutex_t	write;
}	t_vars;

typedef struct	s_philo
{
	int				id;
	int				num_meals;
	long			last_meal;
	pthread_t		thread;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*write;
	t_vars			*vars;
}	t_philo;

//-------------INIT------------//
int		init_struct(t_vars *data, char **argv);
//-------------ATOI------------//
int		atoi_phil(char *str);
//------------UTILS------------//
void	write_action(t_philo *philo, char *action);
void	eat_time(t_philo *philo, int time);
void	sleep_time(int time);
int		get_time(void);

void	create_threads(t_philo *philo, t_vars *vars, pthread_mutex_t *forks);

#endif