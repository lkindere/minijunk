/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 17:31:00 by lkindere          #+#    #+#             */
/*   Updated: 2022/05/25 21:19:06 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	ft_digits(int n)
{
	int	digits;

	digits = 0;
	if (n < 0)
		digits++;
	while (n >= 10 || n <= -10)
	{
		digits++;
		n /= 10;
	}
	digits++;
	return (digits);
}

static void	fill_array(long nb, char *arr, int digits)
{
	if (nb < 0)
	{
		arr[0] = '-';
		nb *= -1;
	}
	while (nb > 10)
	{
		arr[digits--] = (nb % 10) + '0';
		nb = nb / 10;
	}
	if (nb == 10)
	{
		arr[digits--] = '0';
		arr[digits] = '1';
	}
	else if (nb < 10)
		arr[digits] = nb + '0';
}

char	*ft_itoa(int n)
{
	int		digits;
	char	*arr;

	digits = ft_digits(n);
	arr = malloc(digits + 1);
	if (!arr)
		return (NULL);
	arr[digits--] = '\0';
	fill_array(n, arr, digits);
	return (arr);
}
