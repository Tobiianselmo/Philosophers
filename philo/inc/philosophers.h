/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanselmo <tanselmo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 15:41:52 by tanselmo          #+#    #+#             */
/*   Updated: 2024/08/09 18:51:14 by tanselmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <stdbool.h>
# include <errno.h>
# include <sys/time.h>

# define SLEEP "is sleeping"
# define FORK_L "has taken LEFT fork"
# define FORK_R "has taken RIGHT fork"
# define FORK "has taken a fork"
# define EAT "is eating"
# define THINK "is thinking"
# define DIED "died"

typedef enum s_actions
{
	LOCK,
	UNLOCK,
	DESTROY,
}	t_actions;

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
	int				finish_meal;
	bool			create_threads;
	pthread_mutex_t	finish_meal_mtx;
	pthread_mutex_t	num_meals_mtx;
	pthread_mutex_t	last_meal_mtx;
	pthread_mutex_t	death_mtx;
	pthread_mutex_t	write_mtx;
}	t_vars;

typedef struct s_philo
{
	int				id;
	int				num_meals;
	int				leave_dinner_table;
	long			last_meal;
	pthread_t		thread;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	t_vars			*vars;
	pthread_mutex_t	*finish_meal_mtx;
	pthread_mutex_t	*num_meals_mtx;
	pthread_mutex_t	*last_meal_mtx;
	pthread_mutex_t	*death_mtx;
	pthread_mutex_t	*write_mtx;
}	t_philo;

//-------------INIT------------//
int				init_struct(t_vars *data, char **argv);
void			init_philos(t_philo *p, t_vars *vars, pthread_mutex_t *forks);
pthread_mutex_t	*init_forks(int len);
//-------------ATOI------------//
int				atoi_phil(char *str);
//------------UTILS------------//
void			write_action(t_philo *philo, char *action);
void			sleepy_time(int time);
int				get_time(void);
void			the_end(t_vars vars, pthread_mutex_t *forks, t_philo *p);
//----------CHECK UTILS--------//
void			take_forks(t_philo *philo);
int				get_death(t_vars *vars);
void			set_death(t_vars *vars, int death);
bool			check_bool(t_philo *philo);
//----------MUTEX UTILS--------//
void			protect_mutex(int action, pthread_mutex_t *mutex);
//------------THREADS----------//
bool			create_threads(t_philo *philo, t_vars *vars,
					pthread_mutex_t *forks);
bool			set_philo(t_philo *philo, t_vars *vars, pthread_mutex_t *forks);
//-----------SIMULATION--------//
bool			init_simulation(t_philo *philo, t_vars *vars,
					pthread_mutex_t *forks);
//-------------ERROR-----------//
void			free_msg(char *msg, t_philo *philo, pthread_mutex_t *forks);

#endif