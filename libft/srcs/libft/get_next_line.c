/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thzimmer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 12:48:22 by thzimmer          #+#    #+#             */
/*   Updated: 2019/05/08 16:32:45 by thzimmer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

static char	init(t_gnl **current, char **buff)
{
	if (!*current)
	{
		if (!(*current = (t_gnl *)malloc(sizeof(t_gnl))))
			return (0);
		(*current)->content = NULL;
		(*current)->len = 0;
	}
	if (!(*buff = (char *)malloc(513)))
		return (0);
	return (1);
}

static char	cpy(t_gnl **cur, char *buff, int rd)
{
	int		i;
	int		j;
	int		size;
	char	*tmp;

	i = (*cur)->len;
	size = (*cur)->len + rd;
	(*cur)->len = size;
	if (!(tmp = (char *)malloc(sizeof(char) * (size + 1))))
		return (-1);
	tmp[size] = '\0';
	j = rd;
	while (--j >= 0)
		tmp[--size] = buff[j];
	while (--i >= 0)
		tmp[--size] = (*cur)->content[i];
	free((*cur)->content);
	(*cur)->content = tmp;
	while (++i < rd)
		if (buff[i] == '\n')
			return (1);
	return (0);
}

static char	*getline(t_gnl **cur, char **line, int *rd)
{
	int		i;
	int		j;
	char	*tmp;

	*rd = 0;
	i = 0;
	while ((*cur)->content[i] != '\n' && i < (*cur)->len)
		i++;
	if (i == (*cur)->len)
		*rd = 1;
	if (!(*line = (char *)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	j = i;
	(*line)[i] = '\0';
	while (--j >= 0)
		(*line)[j] = (*cur)->content[j];
	if (!(tmp = (char *)malloc(sizeof(char) * ((*cur)->len - i + 1))))
		return (NULL);
	while (++j < (*cur)->len - i)
		tmp[j] = (*cur)->content[i + j + 1];
	tmp[j] = '\0';
	free((*cur)->content);
	(*cur)->len -= (i + 1);
	return (tmp);
}

int			get_next_line(char **line)
{
	static t_gnl	*current = NULL;
	char			*buff;
	int				rd;

	if (line == NULL || !init(&current, &buff) || read(0, buff, 0) < 0)
		return (-1);
	while ((rd = read(0, buff, 512)) > 0)
		if (!(buff[rd] = '\0') && cpy(&current, buff, rd))
			break ;
	free(buff);
	if (current->len <= 0)
	{
		free(current->content);
		free(current);
		*line = NULL;
		return (0);
	}
	current->content = getline(&current, line, &rd);
	return (1 + rd);
}
