/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 18:43:34 by lkindere          #+#    #+#             */
/*   Updated: 2022/05/30 14:51:13 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void    handle_sigint(int sig)
{
	(void)sig;
    write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

int	signal_default(void)
{
	struct sigaction	sint = {0};

	sint.sa_handler = SIG_DFL;
	sint.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sint, NULL);
	return (1);
}

void    signal_unhandler(void)
{
	struct sigaction	sint = {0};

	sint.sa_handler = SIG_IGN;
	sint.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sint, NULL);
}

void    signal_handler(void)
{
	struct termios		term;
	struct sigaction	sint = {0};
	struct sigaction	squit = {0};

	tcgetattr(0, &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(0, 0, &term);
	sint.sa_handler = &handle_sigint;
	sint.sa_flags = SA_RESTART;
	squit.sa_handler = SIG_IGN;
	sigaction(SIGINT, &sint, NULL);
	sigaction(SIGQUIT, &squit, NULL);
}
