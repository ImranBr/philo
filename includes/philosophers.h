/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibarbouc <ibarbouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 18:46:41 by ibarbouc          #+#    #+#             */
/*   Updated: 2025/08/02 21:03:03 by ibarbouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>

typedef struct s_data t_data;

typedef struct s_philo
{
	t_data			*data;
	int				id;
	pthread_t		thread;
	long			last_meal_time;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	right_fork;
}					t_philo;

typedef struct s_data
{
	int				num_philo;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				num_of_meal;
	t_philo			*philo;
	// pthread_mutex_t	*forks;
	long			start_time;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	stop_mutex;
	int				stop_dinner;

}					t_data;



// INIT
int	init_data(t_data *data, int ac, char **av);
int init_philo(t_data *data);

// UTILS
long				ft_atol(const char *str);
int					ft_atoi(const char *str);

#endif