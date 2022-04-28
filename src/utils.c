/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas-ma <lucas-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 11:40:07 by lucas-ma          #+#    #+#             */
/*   Updated: 2022/04/28 13:31:40 by lucas-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static char	*ft_stradd_first(char c)
{
	char	*temp;

	temp = malloc(2);
	if (!temp)
		return (NULL);
	temp[0] = c;
	temp[1] = 1;
	return (temp);
}

char	*ft_addchar(char *str, char c)
{
	char	*temp;
	int		i;

	if (!c)
		return (NULL);
	if (!str)
		return (ft_stradd_first(c));
	temp = malloc(ft_strlen(str) + 2);
	if (!temp)
	{
		free(str);
		return (NULL);
	}
	i = -1;
	while (str[++i])
		temp[i] = str[i];
	free(str);
	temp[i] = c;
	temp[++i] = '\0';
	return (temp);
}

int	str_is_numeric(char *str)
{
	int	i;

	i = -1;
	if (str[0] == '-')
		i++;
	while (str[++i])
		if (!(ft_isdigit(str[i])))
			return (0);
	return (1);
}
