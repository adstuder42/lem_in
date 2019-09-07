/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thzimmer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 15:50:11 by thzimmer          #+#    #+#             */
/*   Updated: 2019/04/29 18:49:34 by thzimmer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>

# define BUFF_SIZE 512

/*
** GNL structure.
*/

typedef struct			s_gnl
{
	char				*content;
	int					len;
}						t_gnl;

/*
** Libft standards.
*/

long double				ft_dpow(long double nb, int pow);
unsigned long long		ft_upow(unsigned long long nb, int pow);
char					**ft_strsplit(char const *s, char c);
int						ft_intlen(int nb);
int						ft_pow(int nb, int power);
int						ft_strncmp(char const *s1, char const *s2, size_t n);
int						ft_strcmp(char const *s1, char const *s2);
int						ft_strlen(char const *str);
int						ft_atoi(char const *str);
int						ft_check_intmax(char *str, int len);
int						get_next_line(char **line);
char					*ft_strjoin(char const *s1, char const *s2);
char					*ft_join3(char **s1, char const *s2, char const *s3);
char					*ft_strjoinmulti(int nb, ...);
char					*ft_strdup(char const *src);
char					*ft_strncpy(char *dest, char const *src, size_t n);
char					*ft_strchr(char const *s, int c);
char					*ft_binary(long double n);
char					*ft_strrev(char *str);
char					*ft_itoa(int n);
char					*ft_itoa_base(int n, int base);
char					*ft_strsub(char const *s, unsigned start, size_t len);
char					ft_strequ(char const *s1, char const *s2);
char					ft_strnequ(char const *s1, char const *s2, size_t n);
char					ft_iscapital(char c);
char					ft_isdigit(int c);
void					ft_putchar(char c);
void					ft_putstr(char const *s);
void					ft_putstr_len(char const *s, int len);
void					ft_putstr_fd(char const *s, int fd);
void					ft_putendl(char const *s);
void					ft_sortarr(int **numbers, int len);
void					ft_freetab(char ***tab);

/*
**	Printf structure.
*/

typedef struct			s_var
{
	long double			ld;
	double				f;
	unsigned long long	ull;
	long long			ll;
	int					width;
	int					prec;
	int					varlen;
	char				*flg;
	char				*s;
	char				name;
	char				ksep;
	char				leftjustify;
	char				zeropadding;
	char				showsign;
	char				space;
	char				hash;
	char				widlock;
	char				prelock;
	char				lf;
	char				hflag;
	char				neg;
	char				d;
}						t_var;

/*
** Printf functions.
*/

int						ft_printf(char const *format, ...);
void					ft_time_output(t_var *var, char **output);
void					ft_binary_output(t_var *var, char **output);
void					ft_gconv_output(t_var *var, char **output);
void					ft_char_output(t_var *var, char **output);
void					ft_string_output(t_var *var, char **output);
void					ft_unsigned_output(t_var *var, char **output);
void					ft_converted_output(t_var *var, char **output);
void					ft_integer_output(t_var *var, char **output);
void					ft_float_output(t_var *var, char **output);
void					ft_exponent_output(t_var *var, char **output);
void					ft_notreadable_output(t_var *var, char **output);
void					ft_get_attributes(t_var *var);
void					ft_get_format(t_var *var);
void					ft_apply_flags(char **output, int len, t_var *var);
void					ft_apply_format(t_var *var);
void					ft_apply_ksep(t_var *var);
char					*ft_ultoa(char prefix, int base, t_var *var,
														unsigned long long nb);
char					*ft_ltoa(long long nb);
void					ft_dtoa_start(t_var *var);
void					ft_decimal_rounding(t_var *var, int i, long double dec);
void					ft_return_null(t_var *var, char **output);
void					ft_add_exp(t_var *var);
void					ft_exp_rerounding(t_var *var);
void					ft_gconv_start(t_var *var, int i, int j);
char					*ft_date_init(unsigned long long nb);
void					ft_gconv_reduce_exponent(t_var *var);
char					ft_color(char const *format, int i, int *j,
																int *varlen);
char					*ft_dtoexp(t_var *v, long double nb, int i,
															long double *dec);
int						ft_exp_sorting(t_var *var, long double dec,
															long double *nb);

#endif
