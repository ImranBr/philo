/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibarbouc <ibarbouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 20:58:22 by ibarbouc          #+#    #+#             */
/*   Updated: 2025/09/13 23:44:05 by ibarbouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	check_all_ate_enough(t_data *data)
{
	int	i;
	int	finished;
	int	num_meals;
	int	all_ate;

	if (data->num_of_meal == -1)
		return (0);
	
	pthread_mutex_lock(&data->stop_mutex);
	if (data->stop_dinner)
	{
		pthread_mutex_unlock(&data->stop_mutex);
		return (0);
	}

	i = 0;
	finished = 0;
	num_meals = data->num_of_meal;
	while (i < data->number_of_philo)
	{
		if (data->philo[i].meals_eaten >= num_meals)
			finished++;
		i++;
	}
	all_ate = (finished == data->number_of_philo);
	pthread_mutex_unlock(&data->stop_mutex);
	return (all_ate);
}

void	*monitor_routine(void *arg)
{
	t_data	*data;
	int		i;
	long	current_time;
	long	last_meal;
	int		is_dead;

	data = (t_data *)arg;
	ft_usleep(1);
	while (1)
	{
		pthread_mutex_lock(&data->stop_mutex);
		if (data->stop_dinner)
		{
			pthread_mutex_unlock(&data->stop_mutex);
			return (NULL);
		}
		pthread_mutex_unlock(&data->stop_mutex);

		i = 0;
		while (i < data->number_of_philo)
		{
			current_time = get_time_in_ms();
			pthread_mutex_lock(&data->stop_mutex);
			last_meal = data->philo[i].last_meal_time;
			is_dead = (current_time - last_meal >= data->time_to_die);
			
			if (is_dead)
			{
				data->stop_dinner = 1;
				pthread_mutex_unlock(&data->stop_mutex);
				pthread_mutex_lock(&data->print_lock);
				printf("%ld %d died\n", current_time - data->start_time, 
					data->philo[i].id);
				pthread_mutex_unlock(&data->print_lock);
				return (NULL);
			}
			pthread_mutex_unlock(&data->stop_mutex);
			i++;
		}

		if (check_all_ate_enough(data))
		{
			pthread_mutex_lock(&data->stop_mutex);
			data->stop_dinner = 1;
			pthread_mutex_unlock(&data->stop_mutex);
			return (NULL);
		}
		usleep(100);
	}
	return (NULL);
}
