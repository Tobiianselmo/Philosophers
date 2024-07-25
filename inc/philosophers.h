/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanselmo <tanselmo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 15:41:52 by tanselmo          #+#    #+#             */
/*   Updated: 2024/07/25 19:20:54 by tanselmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <stdbool.h>
# include <sys/time.h>

# define SLEEP "is sleeping"
# define FORK_L "has taken LEFT fork"
# define FORK_R "has taken RIGHT fork"
# define FORK "has taken a fork"
# define EAT "is eating"
# define THINK "is thinking"
# define DIED "died"

typedef struct s_vars
{
	int				n_philo;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				must_eat;
	bool			bool_meals;
	int				death;
	long			start;
	pthread_mutex_t	num_meals_mtx;
	pthread_mutex_t	last_meal_mtx;
	pthread_mutex_t	bool_mtx;
	pthread_mutex_t	death_mtx;
	pthread_mutex_t	write_mtx;
}	t_vars;

typedef struct s_philo
{
	int				id;
	int				num_meals;
	long			last_meal;
	pthread_t		thread;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	t_vars			*vars;
	pthread_mutex_t	*num_meals_mtx;
	pthread_mutex_t	*last_meal_mtx;
	pthread_mutex_t	*bool_mtx;
	pthread_mutex_t	*death_mtx;
	pthread_mutex_t	*write_mtx;
}	t_philo;

//-------------INIT------------//
int				init_struct(t_vars *data, char **argv);
void			init_philos(t_philo *philo, t_vars *vars,
					pthread_mutex_t *forks);
pthread_mutex_t	*init_forks(int len);
//-------------ATOI------------//
int				atoi_phil(char *str);
//------------UTILS------------//
void			write_action(t_philo *philo, char *action);
void			sleepy_time(int time);
int				get_time(void);
int				get_death(t_vars *vars);
void			set_death(t_vars *vars, int death);
bool			check_bool(t_philo *philo);
//------------THREADS----------//
t_philo			*create_threads(t_vars *vars, pthread_mutex_t *forks);
t_philo			*set_philo(t_vars *vars, pthread_mutex_t *forks);

#endif