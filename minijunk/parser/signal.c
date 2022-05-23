/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 08:16:03 by lkindere          #+#    #+#             */
/*   Updated: 2022/05/22 08:54:13 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void    handle_sigint(int sig)
{
    write(2, "\n", 1);
    write(2, "TheShell -> ", 13);
}

void    signal_handler(t_data *data)
{
    struct sigaction sint;
    struct sigaction squit;

    sint.sa_handler = &handle_sigint;
    sint.sa_flags = SA_RESTART;
    squit.sa_handler = SIG_IGN;
    sigaction(SIGINT, &sint, NULL);
    sigaction(SIGQUIT, &squit, NULL);
}
