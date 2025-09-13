/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibarbouc <ibarbouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 19:07:49 by ibarbouc          #+#    #+#             */
/*   Updated: 2025/09/13 22:41:28 by ibarbouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	is_eating(t_philo *philo)
{
	if (philo->id % 2 == 0)
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
	philo->last_meal_time = get_time_in_ms();
	print_action(philo, "is eating");
	pthread_mutex_unlock(&philo->data->stop_mutex);
	ft_usleep(philo->data->time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(&philo->right_fork);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(200); // Décalage pour éviter deadlock
	while (1)
	{
		pthread_mutex_lock(&philo->data->stop_mutex);
		if (philo->data->stop_dinner)
		{
			pthread_mutex_unlock(&philo->data->stop_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->data->stop_mutex);
		is_eating(philo);                   // Tout ce qui est lié au repas
		print_action(philo, "is sleeping"); // Dormir
		ft_usleep(philo->data->time_to_sleep);
		print_action(philo, "is thinking"); // Penser
	}
	return (NULL);
}
