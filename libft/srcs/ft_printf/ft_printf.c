/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thzimmer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 16:47:30 by thzimmer          #+#    #+#             */
/*   Updated: 2019/04/29 18:50:22 by thzimmer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"
#include <stdarg.h>

/*
** Checks the syntax of the flag(s).
*/

static char	ft_valid_flags(char const *s, int j)
{
	if (s[j]
		&& ft_strchr("#+-'*. 0123456789lLhcCsSpPdDiIoOuUKkxXfFbBeErR%", s[j]))
	{
		while (s[j] && ft_strchr("#+- 0'", s[j]))
			j++;
		if (s[j] == '*')
			j++;
		else if (s[j] && ft_strchr("123456789", s[j]))
			while (ft_isdigit(s[j]))
				j++;
		if (s[j] == '.' && (j += 1))
			while (ft_isdigit(s[j]))
				j++;
		if (s[j - 1] == '.' && s[j] == '*')
			j++;
		if ((s[j] == 'l' && s[j + 1] == 'l')
			|| (s[j] == 'h' && s[j + 1] == 'h'))
			j += 2;
		else if (s[j] == 'l' || s[j] == 'h' || s[j] == 'L')
			j++;
		if (s[j] && ft_strchr("fcspdiouxXbFCSPDIOUBekKErR%", s[j]))
			return (1);
	}
	return (0);
}

/*
** Checks for variable flag(s) describing minimal width and/or precision
** then gets the variable.
*/

static void	ft_get_variable(t_var *var, va_list ap, int dbl, int i)
{
	while (var->flg[++i])
	{
		if (var->flg[i] == '*' && (i - 1 >= 0 && var->flg[i - 1] == '.')
			&& (var->prelock = 1))
			(var->prec = va_arg(ap, int));
		if (var->flg[i] == '*' && (i - 1 < 0 || var->flg[i - 1] != '.')
			&& (var->widlock = 1))
			var->width = (va_arg(ap, int));
	}
	if (var->name == 's' || var->name == 'r')
		var->s = va_arg(ap, char *);
	if (ft_strchr("puXxokb", var->name))
		var->ull = va_arg(ap, unsigned long long);
	if (var->name == 'c' || var->name == 'd' || var->name == 'i')
		var->ll = va_arg(ap, long long);
	if (var->name == 'f' || var->name == 'g' || var->name == 'e')
	{
		if (dbl == 1)
			var->ld = va_arg(ap, long double);
		if (dbl == 0)
			var->f = va_arg(ap, double);
	}
}

/*
** Roots the variable to the adequate function for calculating the output.
*/

static void	ft_calculate_output(t_var *var, char **output)
{
	if (var->name == 's')
		ft_string_output(var, output);
	if (var->name == 'd' || var->name == 'i')
		ft_integer_output(var, output);
	if (var->name == 'c')
		ft_char_output(var, output);
	if (var->name == 'u')
		ft_unsigned_output(var, output);
	if (ft_strchr("xXop", var->name))
		ft_converted_output(var, output);
	if (var->name == 'f')
		ft_float_output(var, output);
	if (var->name == 'b')
		ft_binary_output(var, output);
	if (var->name == 'e')
		ft_exponent_output(var, output);
	if (var->name == 'k')
		ft_time_output(var, output);
	if (var->name == 'r')
		ft_notreadable_output(var, output);
	if (var->name == '%')
		ft_string_output(var, output);
}

/*
** Checks flag(s) syntax and if correct gets the next variable using <stdarg.h>.
** This variable is then printed to standard output using the according flag(s).
*/

static void	ft_print_variable(char const *s, int *i, va_list ap, t_var *var)
{
	char	*output;
	int		j;

	var->width = 0;
	var->prelock = 0;
	var->widlock = 0;
	if (ft_valid_flags(s, (j = ++(*i))))
	{
		while (s[*i] && !ft_strchr("fcspdiouxXbFCSPkKDIOUBeErR%", s[*i]))
			(*i)++;
		free(var->flg);
		if (!(var->flg = (char *)malloc(sizeof(char) * (*i - j + 1))))
			return (ft_putstr("error from malloc in ft_print_variable"));
		var->flg = ft_strncpy(var->flg, &(s[j]), *i - j);
		var->flg[*i - j] = '\0';
		var->name = (ft_iscapital(s[*i]) && s[*i] != 'X') ? s[*i] + 32 : s[*i];
		if (var->name != '%')
			ft_get_variable(var, ap, var->d = (s[*i - 1] == 'L' || (*i > 1
				&& s[*i - 1] == 'l' && s[*i - 2] == 'l') ? 1 : 0), -1);
		ft_calculate_output(var, &output);
		ft_putstr_len(output, var->width);
		free(output);
	}
}

/*
** Goes through the given constant string looking for variable outputs ('%').
** Prints it according to given flag(s) in the specified data format.
** Returns the number of printed characters.
*/

int			ft_printf(char const *format, ...)
{
	t_var		var;
	va_list		ap;
	int			i;
	int			j;

	va_start(ap, format);
	var.flg = NULL;
	var.varlen = 0;
	i = -1;
	j = 0;
	while (format[++i] && ft_color(format, i, &j, &var.varlen))
		if (format[i] == '%' && format[i + 1])
		{
			ft_putstr_len(&(format[j]), i - j);
			ft_print_variable(format, &i, ap, &var);
			j = i + 1;
			--var.varlen;
		}
	free(var.flg);
	ft_putstr_len(&(format[j]), i - j);
	va_end(ap);
	return (var.varlen);
}
