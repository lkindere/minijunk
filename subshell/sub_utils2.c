/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 11:50:31 by lkindere          #+#    #+#             */
/*   Updated: 2022/05/25 11:51:05 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Replaces && || | wih spaces
int	remove_separator(char **segment, int i)
{
	if ((*segment)[i] == '|' || (*segment)[i] == '&')
		(*segment)[i] = ' ';
	if ((*segment)[i + 1] == '|' || (*segment)[i + 1] == '&')
		(*segment)[i + 1] = ' ';
	// printf("\nSep New segment  : %s\n", *segment);
	return (0);
}
