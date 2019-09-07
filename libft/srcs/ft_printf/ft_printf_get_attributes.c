/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_get_attributes.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thzimmer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 16:49:41 by thzimmer          #+#    #+#             */
/*   Updated: 2019/02/20 11:42:43 by thzimmer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

/*
** Initialises the structure's flags.
*/

static void	ft_var_init(t_var *var)
{
	if (!var->prelock)
		var->prec = -1;
	var->lf = 0;
	var->hflag = 0;
	var->hash = 0;
	var->zeropadding = 0;
	var->space = 0;
	var->showsign = 0;
	var->leftjustify = 0;
	var->ksep = 0;
	if (!var->widlock)
		var->width = 0;
	else
		var->width = (var->width < 0 ? -var->width : var->width);
}

/*
** Gets the 'width' parameter from flags.
*/

static void	ft_get_width(t_var *var)
{
	int		i;

	i = 0;
	while (var->flg[i] && var->flg[i] != '.')
	{
		if (ft_strchr("123456789", var->flg[i]))
			if (var->widlock == 0 && (var->widlock = 1))
				var->width = ft_atoi(&(var->flg[i]));
		i++;
	}
}

/*
** Gets attribute(s) flag(s) attached to the variable.
*/

void		ft_get_attributes(t_var *var)
{
	int		i;

	ft_var_init(var);
	ft_get_width(var);
	i = -1;
	while (var->flg[++i])
	{
		if (var->flg[i] == '#')
			var->hash = 1;
		if (var->flg[i] == '-')
			var->leftjustify = 1;
		if (var->flg[i] == 39)
			var->ksep = 1;
		if (var->flg[i] == ' ')
			var->space = 1;
		if (var->flg[i] == '+')
			var->showsign = 1;
		if (var->flg[i] == '0' && (i == 0
			|| (!ft_isdigit(var->flg[i - 1]) && var->flg[i - 1] != '.')))
			var->zeropadding = 1;
		if (var->flg[i] == '.')
			if (var->prelock == 0 && (var->prelock = 1))
				var->prec = ft_atoi(&(var->flg[i + 1]));
	}
}

/*
** Gets the flag representing data size if there is one.
*/

void		ft_get_format(t_var *var)
{
	int		i;

	i = -1;
	while (var->flg[++i])
	{
		if (var->flg[i] == 'l' && var->flg[i + 1] != 'l' && (var->lf = 1))
			break ;
		if (var->flg[i] == 'l' && var->flg[i + 1] == 'l' && (var->lf = 2))
			break ;
		if (var->flg[i] == 'L' && (var->lf = 3))
			break ;
		if (var->flg[i] == 'h' && var->flg[i + 1] != 'h' && (var->hflag = 1))
			break ;
		if (var->flg[i] == 'h' && var->flg[i + 1] == 'h' && (var->hflag = 2))
			break ;
	}
	var->zeropadding = var->leftjustify ? 0 : var->zeropadding;
}

/*
** Checks for a {color} or {end of color} modifier in format.
*/

char		ft_color(char const *format, int i, int *j, int *varlen)
{
	*varlen += 1;
	if (format[i] == '{')
	{
		write(1, (&(format[*j])), i - *j) ? *j += (i - *j) : 0;
		if (!ft_strncmp("{black}", &(format[i]), 7) && (*j += 7))
			write(1, "\033[30;1m", 7) ? *varlen -= 7 : 0;
		if (!ft_strncmp("{red}", &(format[i]), 5) && (*j += 5))
			write(1, "\033[31;1m", 7) ? *varlen -= 5 : 0;
		if (!ft_strncmp("{green}", &(format[i]), 7) && (*j += 7))
			write(1, "\033[32;1m", 7) ? *varlen -= 7 : 0;
		if (!ft_strncmp("{yellow}", &(format[i]), 8) && (*j += 8))
			write(1, "\033[33;1m", 7) ? *varlen -= 8 : 0;
		if (!ft_strncmp("{blue}", &(format[i]), 6) && (*j += 6))
			write(1, "\033[34;1m", 7) ? *varlen -= 6 : 0;
		if (!ft_strncmp("{magenta}", &(format[i]), 9) && (*j += 9))
			write(1, "\033[35;1m", 7) ? *varlen -= 9 : 0;
		if (!ft_strncmp("{cyan}", &(format[i]), 6) && (*j += 6))
			write(1, "\033[36;1m", 7) ? *varlen -= 6 : 0;
		if (!ft_strncmp("{white}", &(format[i]), 7) && (*j += 7))
			write(1, "\033[37;1m", 7) ? *varlen -= 7 : 0;
		if (!ft_strncmp("{eoc}", &(format[i]), 5) && (*j += 5))
			write(1, "\033[0m", 4) ? *varlen -= 5 : 0;
	}
	return (1);
}
