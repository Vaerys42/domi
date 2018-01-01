/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 14:14:19 by kboucaud          #+#    #+#             */
/*   Updated: 2016/11/09 13:29:14 by kboucaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>

char	*ft_strnew(size_t size)
{
	char	*new;
	int		i;

	i = 0;
	new = (char*)malloc(sizeof(char) * (size + 1));
	if (new == NULL)
		return (NULL);
	while (new[i] != '\0')
	{
		new[i] = '\0';
		i++;
	}
	return (new);
}
