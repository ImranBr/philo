/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibarbouc <ibarbouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 19:07:49 by ibarbouc          #+#    #+#             */
/*   Updated: 2025/09/14 00:53:09 by ibarbouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	is_eating(t_philo *philo)
{
	int		stop;
	long	current_time;

	if (philo->data->number_of_philo == 1)
	{
		pthread_mutex_lock(&philo->right_fork);
		print_action(philo, "has taken a fork");
		while (1)
		{
			pthread_mutex_lock(&philo->data->stop_mutex);
			stop = philo->data->stop_dinner;
			pthread_mutex_unlock(&philo->data->stop_mutex);
			if (stop)
				break ;
			usleep(1000);
		}
		pthread_mutex_unlock(&philo->right_fork);
		return (0);
	}
	if (philo->id % 2 == 1)
	{
		pthread_mutex_lock(&philo->right_fork);
		print_action(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		print_action(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		print_action(philo, "has taken a fork");
		pthread_mutex_lock(&philo->right_fork);
		print_action(philo, "has taken a fork");
	}
	pthread_mutex_lock(&philo->data->stop_mutex);
	if (!philo->data->stop_dinner)
	{
		pthread_mutex_unlock(&philo->data->stop_mutex);
		pthread_mutex_lock(&philo->meal_mutex);
		current_time = get_time_in_ms();
		philo->last_meal_time = current_time;
		philo->meals_eaten++;
		pthread_mutex_unlock(&philo->meal_mutex);
		print_action(philo, "is eating");
		ft_usleep(philo->data->time_to_eat);
	}
	else
	{
		pthread_mutex_unlock(&philo->data->stop_mutex);
	}
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(&philo->right_fork);
	pthread_mutex_lock(&philo->data->stop_mutex);
	stop = philo->data->stop_dinner;
	pthread_mutex_unlock(&philo->data->stop_mutex);
	return (!stop);
}

void	*routine(void *arg)
{
	t_philo	*philo;
	int		stop;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		ft_usleep(1);
	while (1)
	{
		pthread_mutex_lock(&philo->data->stop_mutex);
		stop = philo->data->stop_dinner;
		pthread_mutex_unlock(&philo->data->stop_mutex);
		if (stop)
			break ;
		if (!is_eating(philo))
			break ;
		print_action(philo, "is sleeping");
		ft_usleep(philo->data->time_to_sleep);
		pthread_mutex_lock(&philo->data->stop_mutex);
		stop = philo->data->stop_dinner;
		pthread_mutex_unlock(&philo->data->stop_mutex);
		if (!stop)
			print_action(philo, "is thinking");
	}
	return (NULL);
}
