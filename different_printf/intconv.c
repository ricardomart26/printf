/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intconv.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 18:23:48 by rimartin          #+#    #+#             */
/*   Updated: 2021/03/29 18:51:34 by rimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	if_width_neg(sign_t *st, int control)
{
	int temp;

	temp = 0;
	if (control == 0)
		ft_putchar('-', st);

	if (st->temp_dot > st->size_c && control == 0)
		st->size_c = st->temp_dot;
	else if (st->temp_dot > st->size_c)
		temp = st->temp_dot;
	if (temp < st->width && control == 1)
	{
		st->width -= temp + 1;
		while (st->width-- > 0)
			if (st->zero)
				ft_putstr_fd("0", 1, st);
			else
				ft_putstr_fd(" ", 1, st);
	}
	else if (st->size_c < st->width && control == 0)
	{
		// printf("\nteste n 2\n");
		st->width -= st->size_c + 1;
		while (st->width-- > 0)
			if (st->zero)
				ft_putstr_fd("0", 1, st);
			else
				ft_putstr_fd(" ", 1, st);
	}
	if (control == 1)
		ft_putchar('-', st);

}

void	if_width_int(sign_t *st)
{
	//printf("\n size_c = %d , width = %d\n", st->size_c, st->width);
	int temp;

	if (st->temp_dot > st->size_c && !(st->cminus))
		st->size_c = st->temp_dot;
	else if (st->temp_dot > st->size_c)
		temp = st->temp_dot;
	if (st->size_c < st->width)
	{
		st->width -= st->size_c;
		while (st->width-- > 0)
			if (st->zero)
				ft_putstr_fd("0", 1, st);
			else
				ft_putstr_fd(" ", 1, st);
	}
	if (!(st->align) && !(st->cminus))
	{
		//printf("printing");
		ft_putstr_fd(st->conv, 1, st);
	}
}

void	if_precision_int(sign_t *st, int control)
{
	//printf("\n size_c = %d , width = %d\n", st->size_c, st->dot);
	//printf("\nst->size_c = %d \n", st->size_c);

	// if (st->dot < st->size_c && st->dot != -1)
	// {
	// 	st->size_c = st->dot; // O size fica com 0
	// 	st->c_dot = 1;
	// 	swap(st);
	// }
	if (st->dot > st->size_c)
	{
		if (control == 0)
			st->size_c -= 0;
		//printf("control = %d", control);
		//printf("\n size_c = %d , width = %d\n", st->size_c, st->dot);
		st->dot -= st->size_c;
		while (st->dot-- > 0)
			ft_putstr_fd("0", 1, st);
		st->size_c -= st->dot;
	}
}

void	negative_int(sign_t *st)
{
	if (st->dot > st->width)
	{
		ft_putchar('-', st);
		if_precision_int(st, 0);
		if (st->align)
			if_align_int(st);
		else if (st->dot)
			if_precision_int(st, 1);
		ft_putstr_fd(st->conv, 1, st);
	}
	else if (st->dot < st->width)
	{
		if (st->zero)
			if_width_neg(st, 0);
		else
			if_width_neg(st, 1);
		if (st->align)
			if_align_int(st);
		if (st->dot != -1)
			if_precision_int(st, 1);
		ft_putstr_fd(st->conv, 1, st);
	}
}

void if_align_int(sign_t *st)
{
	if (st->dot > st->size_c)
		if_precision_int(st, 1);
	ft_putstr_fd(st->conv, 1, st);
	if_width_int(st);
}

void specif_int(sign_t *st, va_list args)
{

	st->conv = ft_get_arg(args, st);
	st->size_c = ft_strlen(st->conv);
	//printf("\n\n size_c = %d", st->size_c);

	st->temp_dot = st->dot;
	//printf("\nst->minus = %d \n", st->cminus);
	//printf("\nst->dot = %d \n", st->dot);
	if (st->cminus)
		negative_int(st);
	else if (st->align)
		if_align_int(st);
	else
	{
		if (st->dot > st->width && !(st->align))
			if_precision_int(st, 0);
		else if (st->dot >= 1 && !(st->align))
			if_precision_int(st, 1);
		if (st->width > st->temp_dot && !(st->align))
			if_width_int(st);
		else if (st->dot != 0 && !(st->align))
			ft_putstr_fd(st->conv, 1, st);
	}
	// if (st->width && !(st->dot))
	// 	if_width(st);z
	// else if (!(st->width) && st->dot)
	// 	if_precision(st);
	//printf("\nwords = %d", st->words);
	free_if_needed(st);
}

















void specif_uint(sign_t *st, va_list args)
{
	st->conv = ft_get_arg(args, st);
	//printf("\n\n st->conv = %s\n\n", st->conv);
	st->size_c = ft_strlen(st->conv);
	if (st->align)
	{
		st->zero = 0;
		if_align(st);
	}
	else if (st->width && !(st->dot))
		if_width(st);
	else if (!(st->width) && st->dot != -1)
		if_precision(st);
	else if (st->width > !(st->dot))
		width_b_precision(st);
	else if (st->width < st->dot)
		width_s_precision(st);
	// else if (st->width == st->dot)
	// 	width_e_precision(st);

	free_if_needed(st);

}

