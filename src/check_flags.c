/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 14:48:25 by rimartin          #+#    #+#             */
/*   Updated: 2021/03/21 15:26:11 by rimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void init_struct(sign_t *st)
{
	st->align = 0;
	st->zero = 0;
	st->dot = -1;
	st->cdot = 0;
	st->width = 0;
	st->c = 48;
	st->conv = 0;
	st->size_c = 0;
	st->temp_dot = 0;
	st->negprec = 0;
	st->cminus = 0;
	st->max_value = 0;
}

// Posso guardar os args na struct?
// Como alocar memoria para variavel que vai guardar a string convertida?
// Nao esquecer de chamar as funcoes width e sign
// Precisao %5.4d (10) sao 5 espacos, mas 3 numeros, exemplo ( 0010);
// Precisao das strings %10.4s (      olai)a esquerda sao os espacos e a direita os caracteres
// Width .carateres
// if (width menor que a string ignorar, se for maior acrescentar espacos.)
// if (width menor que a string ignorar, se for maior acrescentar espacos.)
// if (menos entao print string e acrescentar espacos a direita)
// Fazer align depois de escrever a conversao
// Funcao para saber o tamanho, para onde mandar mos o tamanho?

void	with_flags(sign_t *st, char *fmt, va_list args)
{
	int c_signs;

	c_signs = 1;
	while (fmt[c_signs] == '0' || fmt[c_signs] == '-')
	{
		if (fmt[c_signs] == '0' )
			st->zero = c_signs++;
		if (fmt[c_signs] == '-')
			st->align = c_signs++;
	}
	if (ft_isdigit(fmt[c_signs]) || fmt[c_signs] == '*')
		see_width(st, fmt, args, &c_signs);
	fmt += c_signs;
	if (*fmt == '.')
		see_precision(st, fmt + 1, args);
	if (st->zero && (st->dot != -1 || st->align))
		st->zero = 0;
	st->temp_dot = st->dot;
	do_arg(args, st);
}

void	see_width(sign_t *st, char *fmt, va_list args, int *c_signs)
{
	if (ft_isdigit(fmt[*c_signs]))
	{
		st->width = ft_atoi(fmt + *c_signs);
		*c_signs += ft_intlen(st->width);
	}
	else if (fmt[(*c_signs)++] == '*')
	{
		st->width = va_arg(args, int);
		if (st->width < 0)
		{
			st->width *= -1;
			st->align = 1;
		}
	}
}

void	see_precision(sign_t *st, char *fmt, va_list args)
{
	if (type(*fmt))
	{
		st->cdot = 1;
		st->dot = 0;
	}
	else if (*fmt == '-')
	{
		fmt++;
		st->negprec = 1;
	}
	else if (*fmt == '*')
	{
		st->dot = va_arg(args, int);
		if (st->dot < 0)
		{
			st->dot *= -1;
			st->negprec = 1;
		}
	}
	if (ft_isdigit(*fmt))
		st->dot = ft_atoi(fmt);
	if (st->negprec)
		st->dot = 0;
}
