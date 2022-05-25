/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_straiojoin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 20:30:49 by lkindere          #+#    #+#             */
/*   Updated: 2022/05/25 17:38:49 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include <stdlib.h>

static size_t	ft_stralen(char **s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

//String array index overwrite join
//Joins a1 with a2 starting at a1[index] overwriting it, freeing a1[index]
//a1 strings after [index] get moved to the end of a2
//Changes index pointer to the first element after a2
char	**ft_straiojoin(char **a1, char **a2, int *index)
{
	char	**join;
	int		i;
	int		j;
	int		k;

	if (!a1 || !a2)
		return (NULL);
	i = 0;
	j = 0;
	k = 0;
	join = malloc(sizeof(char *) * (ft_stralen(a1) + ft_stralen(a2)));
	if (!join)
		return (NULL);
	while (a1[j] && i < (*index))
		join[i++] = a1[j++];
	if (a1[j])
		free(a1[j]);
	j++;
	while (a2[k])
		join[i++] = a2[k++];
	*index = i;
	while (a1[j])
		join[i++] = a1[j++];
	join[i] = NULL;
	return (join);
}

// #include <string.h>
// #include <stdio.h>

// int	main(void)
// {
// 	char	**join;
// 	char	**a1;
// 	char 	**a2;

// 	a1 = malloc(sizeof(char *) * 10);
// 	a2 = malloc(sizeof(char *) * 10);
// 	a1[0] = strdup("1 This");
// 	a1[1] = strdup("1 Is");
// 	a1[2] = strdup("1 A");
// 	a1[3] = strdup("1 String");
// 	a1[4] = strdup("1 Array");
// 	a1[5] = NULL;
// 	a2[0] = strdup("2 This");
// 	a2[1] = strdup("2 Is");
// 	a2[2] = strdup("2 A");
// 	a2[3] = strdup("2 String");
// 	a2[4] = strdup("2 Array");
// 	a2[5] = NULL;

// 	join = ft_straiojoin(a1, a2, 3);
// 	for (int i = 0; join[i]; i++)
// 		printf("%s\n", join[i]);
// 	return (0);
// }
