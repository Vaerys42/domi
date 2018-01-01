/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 12:22:58 by kboucaud          #+#    #+#             */
/*   Updated: 2016/11/09 13:41:43 by kboucaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>

void	*ft_memalloc(size_t size)
{
	unsigned char	*new;
	int				i;

	i = 0;
	if (size > 4294967295 || size == 0)
		return (0);
	new = (unsigned char*)malloc(sizeof(char) * (size + 1));
	if (new == NULL)
		return (NULL);
	while (new[i] != '\0')
	{
		new[i] = '\0';
		i++;
	}
	return (new);
}
