/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 20:19:09 by mmeising          #+#    #+#             */
/*   Updated: 2022/05/23 06:27:37 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

#include "exec.h"

/*
 *	Resets the data that needs to be cleaned for every time we get new input.
 *	Includes resetting stdin and stdout from the backup saved in data.
 */
int	reset_data(t_data *data)
{
	if (data->input)
	{
		free(data->input);
		data->input = NULL;
	}
	if (data->cmds)
		free_cmds(&data->cmds);
	// data->cmds = ft_calloc(1, sizeof(t_cmd));
	// if (data->cmds == NULL)
	// 	return (ft_err(MALLOC_FAIL));
	if (data->tokens)
		free_tokens(&data->tokens);
	data->flags.single_quote = 0;
	data->flags.double_quote = 0;
	data->cmd_count = 0;
	data->dollar_count = 0;
	if (data->expands)
		free_2d_char(&data->expands);
	// if (add_char_ptr(&data->expands) != 0)
	// 	return (MALLOC_FAIL);
	dup2(data->std_in, STDIN_FILENO);
	dup2(data->std_out, STDOUT_FILENO);
	return (0);
}

int	input_is_empty(char	*input)
{
	int	i;

	i = 0;
	while (input[i] == ' ')
		i++;
	if (input[i] == '\0')
		return (1);
	else
		return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	// signal_handler(data);
	while (true)//can use continue keyword in here in case something fails. print error in the failing function and continue the loop with new input
	{
		if (init_data(&data, envp) != 0)
			return (MALLOC_FAIL);
		data->input = readline("TheShell -> ");
		if (!data->input)
			builtin_exit(NULL, NULL);
				printf("wat\n");
		if (data->input && data->input[0])
			add_history(data->input);
		if (input_is_empty(data->input))
			continue ;
		printf("wat\n");
		// data->input = expander(data->input, data);
		if (lexer(data) != 0)
			continue ;

		if (parser(data) != 0)
			continue ;

		if (do_heredoc(data) != 0)
			continue ;

		in_out_std(data);

		executer(data, data->cmds);
		reset_data(data);
		free(data);
		// 	continue ;
	}
}
