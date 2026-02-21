/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dufama <dufama@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 10:54:39 by dufama            #+#    #+#             */
/*   Updated: 2025/11/09 15:15:24 by dufama           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*strjoin_free(char *s1, char *s2)
{
	char	*new_string;
	size_t	len_s1;
	size_t	len_s2;

	if (!s1)
	{
		s1 = (char *)malloc(1);
		if (!s1)
			return (NULL);
		s1[0] = '\0';
	}
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	new_string = malloc(len_s1 + len_s2 + 1);
	if (!new_string)
	{
		free(s1);
		return (NULL);
	}
	ft_memcpy(new_string, s1, len_s1);
	ft_memcpy(new_string + len_s1, s2, len_s2 + 1);
	free(s1);
	return (new_string);
}
