/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 20:19:09 by mmeising          #+#    #+#             */
/*   Updated: 2022/05/24 09:57:07 by lkindere         ###   ########.fr       */
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
	data->cmds = ft_calloc(1, sizeof(t_cmd));
	if (data->cmds == NULL)
		return (ft_err(MALLOC_FAIL));
	if (data->tokens)
		free_tokens(&data->tokens);
	data->flags.single_quote = 0;
	data->flags.double_quote = 0;
	data->cmd_count = 0;
	data->dollar_count = 0;
	if (data->expands)
		free_2d_char(&data->expands);
	if (add_char_ptr(&data->expands) != 0)
		return (MALLOC_FAIL);
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
	char	*full_input;
	char	*segment;
	t_data	*data;
	int		temp_pid = -1;

	signal_handler(data);
	if (init_data(&data, envp) != 0)
		return (MALLOC_FAIL);
	while (true)//can use continue keyword in here in case something fails. print error in the failing function and continue the loop with new input
	{
		full_input = readline("TheShell -> ");
		if (!full_input)
			builtin_exit(NULL, NULL);
		if (full_input && full_input[0])
			add_history(data->input);
		if (input_is_empty(full_input))
			continue ;
		splitter(&full_input, &segment);
		handle_separators(data, &full_input);
		is_subshell(&segment);
		// while (full_input)
		// {
		// 	while (!data->input && full_input && full_input[0])
		// 	{
		// 		if (subshells(&full_input, &sub_input))
		// 		{
		// 			temp_pid = fork();
		// 			if (temp_pid == 0)
		// 			{
		// 				free(full_input);
		// 				full_input = sub_input;
		// 				sub_input = NULL;
		// 			}
		// 			if (temp_pid > 0)
		// 			{
		// 				data->exit_code = get_exitstatus(temp_pid);
		// 				temp_pid = -1;
		// 				continue ;
		// 			}
		// 		}
		// 		split_input(&full_input, &data);
		// 		// printf("pid: %d, before split data input: %s, full input: %s, and_or: %d\n", temp_pid, data->input, full_input, data->and_or[0]);
		// 		// printf("pid: %d, after split data input: %s, full input: %s\n, and_or: %d\n", temp_pid, data->input, full_input, data->and_or[0]);
		// 		// printf("pid: %d, Full input: %s\n", temp_pid, full_input);
		// 		// printf("pid: %d, Data input: %s\n", temp_pid, data->input);
		// 	}
		// 	if (!data->input || input_is_empty(data->input))
		// 	{
		// 		reset_data(data);
		// 		if (temp_pid == 0)
		// 			exit(data->exit_code);
		// 		break ;
		// 	}
		// 	// sleep(1);
		// 	// printf("Pid: %d, pre expander\n", temp_pid);
		// 	data->input = expander(data->input, data);
		// 	// printf("Pid: %d, pre lexer\n", temp_pid);
		// 	if (lexer(data) != 0)
		// 		continue ;
		// 	// printf("Past lexer\n");
		// 	// printf("Pid: %d, pre parser\n", temp_pid);
		// 	if (parser(data) != 0)
		// 	{
		// 		free(full_input);
		// 		full_input = NULL;
		// 		continue ;
		// 	}
		// 	// printf("Pid: %d, pre heredoc\n", temp_pid);
		// 	// printf("Past parser\n");
		// 	// if (do_heredoc(data) != 0)
		// 	// 	continue ;

		// 	in_out_std(data);
		// 	// printf("Pid: %d, pre exec\n", temp_pid);
		// 	// printf("Pid: %d, executing: %s\n", temp_pid, data->input);
		// 	if (data->and_or[0] <= 0 || (data->and_or[0] == 1 && data->exit_code == 0) || (data->and_or[0] == 2 && data->exit_code != 0))
		// 		executer(data, data->cmds);
		// 	if (temp_pid == 0 && (!full_input || input_is_empty(full_input)))
		// 	{
		// 		printf("Sub process exitting with exit code: %d\n", data->exit_code);
		// 		exit(data->exit_code);
		// 	}
			reset_data(data);
		// 	// printf("pid: %d, full input after reset: %s\n", temp_pid, full_input);
		// 	// printf("pid: %d post reset\n", temp_pid);
	}
}
