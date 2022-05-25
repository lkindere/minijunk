/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 18:43:34 by lkindere          #+#    #+#             */
/*   Updated: 2022/05/25 19:05:43 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void    handle_sigint(int sig)
{
	(void)sig;
    write(2, "\n", 1);
    write(2, "MiniJunk XD:", 13);
}

void    signal_handler(void)
{
    struct sigaction sint;
    struct sigaction squit;

    sint.sa_handler = &handle_sigint;
    sint.sa_flags = SA_RESTART;
    squit.sa_handler = SIG_IGN;
    sigaction(SIGINT, &sint, NULL);
    sigaction(SIGQUIT, &squit, NULL);
}
