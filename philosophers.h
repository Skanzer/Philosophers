/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szerzeri <szerzeri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 17:16:18 by szerzeri          #+#    #+#             */
/*   Updated: 2024/03/13 13:11:30 by szerzeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

# define SUCCESS 0
# define ALLOC_ERROR 1
# define THREAD_ERROR 2
# define MUTEX_ERROR 3

# define FORK "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DIE "died"

typedef enum e_philo_state
{
	TAKING_FORK,
	SLEEPING,
	THINKING,
	EATING,
	DIYING,
}	t_philo_state;

typedef struct s_general
{
	long int			nb_phi;
	long int			t_d;
	long int			t_e;
	long int			t_s;
	long int			nb_e;
}	t_general;

typedef struct s_philosopher
{
	struct s_philosopher	*next;
	struct s_philosopher	*previous;
	t_general				sim_data;
	pthread_mutex_t			*right_fork;
	pthread_mutex_t			*left_fork;
	pthread_mutex_t			*print_mutex;
	pthread_mutex_t			philo_mutex;
	pthread_t				philo;
	long int				last_meal;
	long int				start_time;
	int						index;
	int						eat_count;
	int						exit;
}	t_philosopher;

typedef struct s_simulation
{
	t_philosopher	*philosophers;
	pthread_mutex_t	*print_mutex;
	t_general		sim_data;
	long int		start_time;
	int				nb_finished;
}	t_simulation;

int			check_digits(char **argv);
int			check_error(int argc, char **argv);
int			check_phi_nb(char **argv);
int			check_limit(char **argv);


long int	ft_atol(const char *str);
void		*ft_calloc(size_t n_membr, size_t size);
void		display_error(int ret);
void		free_memory(t_simulation *sim);
void		print_action(t_philosopher *philosopher, t_philo_state state);


long int	get_timestamp(long int start);
long int	time_in_ms(void);
void		wait_duration(long int duration);


void		take_input(t_general *input, int argc, char **argv);
void		add_philo_to_list(t_philosopher *philo, t_simulation *simulation);
int			init_struct(t_simulation *simulation, int argc, char **argv);
int			init_philo(t_philosopher *philo, t_general *input);
int			init_mutexes(t_philosopher *philo);


int			create_threads(t_simulation *simulation);
int			join_threads(t_simulation *simulation);


void		*begin_simulation(void *arg);
int			check_exit(t_philosopher *philosopher);


void		a_eat(t_philosopher *philosopher);
void		a_sleep(t_philosopher *philosopher);
void		a_think(t_philosopher *philosopher);

void		monitor_philosophers(t_simulation *sim);
void		set_exit(t_philosopher *first);

#endif