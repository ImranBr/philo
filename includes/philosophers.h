/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibarbouc <ibarbouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 18:46:41 by ibarbouc          #+#    #+#             */
/*   Updated: 2025/08/10 21:05:39 by ibarbouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	struct s_data	*data;
	int				id;
	long			last_meal_time;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	right_fork;
}					t_philo;

typedef struct s_data
{
	int				number_of_philo;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				num_of_meal;
	t_philo			*philo;
	long			start_time;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	stop_mutex;
	pthread_t		monitor;
	int				monitor_created;
	int				stop_dinner;
}					t_data;

// INIT
int					init_structs(t_data *data, int ac, char **av);

// UTILS
long				ft_atol(const char *str);
int					ft_atoi(const char *str);
long				get_time_in_ms(void);

#endif