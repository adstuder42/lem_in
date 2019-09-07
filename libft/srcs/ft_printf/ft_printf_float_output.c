/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_float_output.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thzimmer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 13:45:46 by thzimmer          #+#    #+#             */
/*   Updated: 2019/02/20 11:42:32 by thzimmer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

/*
** Provides a rounding feature for decimal numbers.
*/

void		ft_decimal_rounding(t_var *v, int i, long double dec)
{
	char	*tmp;

	if (dec >= 5.L)
	{
		if (v->s[i] == '.')
			--i;
		++v->s[i];
		while ((i > 0) && (v->s[i] == ':' || v->s[i] == '.') && (v->s[i] = '0'))
		{
			v->s[i - 1] == '.' ? --i : 0;
			++v->s[i - 1];
			--i;
		}
		if (i == 0 && (v->s[i] == ':') && (v->s[0] = '0'))
		{
			tmp = ft_strjoin("1", v->s);
			free(v->s);
			v->s = tmp;
		}
	}
}

/*
** Calculates the flagged output of a float variable.
*/

void		ft_float_output(t_var *var, char **output)
{
	int			len;

	ft_get_attributes(var);
	ft_get_format(var);
	ft_apply_format(var);
	if (var->prec < 0)
		var->prec = 6;
	ft_dtoa_start(var);
	if (var->ksep)
		ft_apply_ksep(var);
	len = ft_strlen(var->s);
	if (len > var->prec)
		var->prec = len;
	if ((var->space || var->showsign || var->neg == -1))
		var->prec = var->prec + 1;
	if (var->width < var->prec)
		var->width = var->prec;
	if (!(*output = (char *)malloc(sizeof(char) * (var->width + 1))))
		return (ft_putstr("error from malloc in ft_float_output.\n"));
	ft_apply_flags(output, len, var);
	var->varlen += var->width;
	free(var->s);
}

/*
** Calculates the flagged output of a binary variable.
*/

void		ft_binary_output(t_var *var, char **output)
{
	int		len;

	ft_get_attributes(var);
	ft_get_format(var);
	ft_apply_format(var);
	var->s = ft_binary(var->ull);
	len = ft_strlen(var->s);
	len > var->prec ? (var->prec = len) : 0;
	if (var->width < var->prec)
		var->width = var->prec;
	if (!(*output = (char *)malloc(sizeof(char) * (var->width + 1))))
		return (ft_putstr("error from malloc in ft_binary_output.\n"));
	ft_apply_flags(output, len, var);
	var->varlen += var->width;
	free(var->s);
}

/*
** Adopts the shortest notation : %g flag.
*/

void		ft_gconv_output(t_var *var, char **output)
{
	int			len;

	ft_get_attributes(var);
	ft_get_format(var);
	ft_apply_format(var);
	if (var->prec == -1)
		var->prec = 6;
	if (!var->prec)
		++var->prec;
	ft_gconv_start(var, 0, 0);
	if (ft_strchr(var->s, 'e'))
		ft_gconv_reduce_exponent(var);
	else if (var->ksep)
		ft_apply_ksep(var);
	len = ft_strlen(var->s);
	var->prec = len;
	if ((var->space || var->showsign || var->neg == -1))
		var->prec = var->prec + 1;
	if (var->width < var->prec)
		var->width = var->prec;
	if (!(*output = (char *)malloc(sizeof(char) * (var->width + 1))))
		return (ft_putstr("error from malloc in ft_gconv_output.\n"));
	ft_apply_flags(output, len, var);
	var->varlen += var->width;
	free(var->s);
}

/*
** Prints a "(null)" output when giving NULL pointer.
*/

void		ft_return_null(t_var *var, char **output)
{
	int		i;

	var->s = ft_strdup("(null)");
	if (var->prec != -1)
		var->s[var->prec] = '\0';
	if (var->prec == -1)
		var->prec = 6;
	var->width = var->width < var->prec ? var->prec : var->width;
	if (!(*output = (char *)malloc(sizeof(char) * (var->width + 1))))
		return (ft_putstr("error from malloc in ft_return_null.\n"));
	i = -1;
	while (++i < var->width)
		output[0][i] = ' ';
	i = -1;
	while (++i < var->prec)
		output[0][i] = var->s[i];
	output[0][i + var->width] = '\0';
	free(var->s);
	var->varlen += var->width;
}
