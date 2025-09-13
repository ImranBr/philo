/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibarbouc <ibarbouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 20:58:22 by ibarbouc          #+#    #+#             */
/*   Updated: 2025/09/13 22:40:55 by ibarbouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*monitor_routine(void *arg)
{
	t_data	*data;
	int		i;
	long	time_now;

	data = (t_data *)arg;
	while (1)
	{
		i = 0;
		while (i < data->number_of_philo)
		{
			pthread_mutex_lock(&data->stop_mutex);
			time_now = get_time_in_ms();
			if (time_now - data->philo[i].last_meal_time > data->time_to_die)
			{
				print_action(&data->philo[i], "died");
				data->stop_dinner = 1;
				pthread_mutex_unlock(&data->stop_mutex);
				return (NULL);
			}
			pthread_mutex_unlock(&data->stop_mutex);
			i++;
		}
		ft_usleep(100); // petite pause pour éviter CPU 100%
	}
	return (NULL);
}
