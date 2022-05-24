/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 15:34:12 by lkindere          #+#    #+#             */
/*   Updated: 2022/05/24 15:35:15 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	can_execute(int and_or, int exit_code)
{
	if (and_or == 0)
		return (1);
	if (and_or == 1 && exit_code == 0)
		return (1);
	if (and_or == 2 && exit_code != 0)
		return (1);
	return (0);
}
