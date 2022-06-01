/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeising <mmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 18:23:43 by lkindere          #+#    #+#             */
/*   Updated: 2022/06/01 22:27:50 by mmeising         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	get_input(char **full_input, t_data *data)
{
	signal_handler();
	if (data->is_fork)
		return ;
	if (!*full_input)
		*full_input = readline("MiniJunk XD: ");
	signal_unhandler();
	if (!*full_input)
		exit (exit_code(-1));
	if (*full_input && (*full_input)[0])
		add_history(*full_input);
	if (input_is_empty(*full_input))
	{
		free(*full_input);
		*full_input = NULL;
		reset_data(data);
	}
}

int	input_is_empty(char	*input)
{
	int	i;

	i = 0;
	if (!input)
		return (1);
	while (input[i] == ' ' || (input[i] >= 9 && input[i] <= 13))
		i++;
	if (input[i] == '\0')
		return (1);
	else
		return (0);
}

int	is_input(char *full_input, char *segment)
{
	if (!segment || input_is_empty(segment))
	{
		if (!full_input || input_is_empty(full_input))
			return (0);
	}
	return (1);
}
