/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_notreadable.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thzimmer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 13:42:17 by thzimmer          #+#    #+#             */
/*   Updated: 2019/02/20 11:42:49 by thzimmer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

/*
** Calculates the flagged output of a not readable string.
*/

void	ft_notreadable_output(t_var *var, char **output)
{
	int		i;
	int		len;

	ft_get_attributes(var);
	len = var->prec;
	if (!var->s)
		return (ft_return_null(var, output));
	if (var->prec == -1)
		return (ft_putstr("[Imput the precision for not readable.]"));
	var->width = var->width < len ? len : var->width;
	if (!(*output = (char *)malloc(sizeof(char) * (var->width + 1))))
		return (ft_putstr("error from malloc in ft_notreadable_output.\n"));
	i = -1;
	while (++i < var->width)
		output[0][i] = ' ';
	if ((i = -1) && var->s && var->leftjustify)
		while (++i < len)
			output[0][i] = var->s[i];
	if (var->s && !var->leftjustify)
		while (++i < len)
			output[0][i + var->width - len] = var->s[i];
	output[0][var->width] = '\0';
	var->varlen += var->width;
}

/*
** Simplifies an exponent notation used with %g format identifier.
*/

void	ft_gconv_reduce_exponent(t_var *var)
{
	int		i;
	int		j;

	i = ft_strlen(var->s);
	while (--i >= 1 && var->s[i] != 'e')
		;
	while ((--i >= 1 && var->s[i] == '0') || var->s[i] == '.')
	{
		j = i - 1;
		while (var->s[++j])
			var->s[j] = var->s[j + 1];
	}
}

/*
** Apply the thousand separator flag for an integer or a float value.
*/

void	ft_apply_ksep(t_var *var)
{
	char	*new;
	int		count;
	int		size;
	int		i;
	int		j;

	count = 0;
	j = 1;
	i = ft_strlen(var->s);
	while (--i >= 0 && var->s[i] != '.')
		j++;
	j = (i == -1 ? 0 : j);
	i = (i == -1 ? (int)ft_strlen(var->s) : i);
	size = i + j + i / 3 - (i % 3 == 0 ? 1 : 0) + 1;
	if (!(new = (char *)malloc(sizeof(char) * (size))))
		return (ft_putstr("error from malloc in ft_apply_ksep\n"));
	new[--size] = '\0';
	while (--j >= 0)
		new[--size] = var->s[j + i];
	while (--i >= 0 && (new[--size] = var->s[i]))
		if (i - 1 >= 0 && ++count == 3 && !(count = 0))
			new[--size] = ',';
	free(var->s);
	var->s = new;
}
