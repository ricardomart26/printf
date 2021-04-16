/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geral.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 18:25:34 by rimartin          #+#    #+#             */
/*   Updated: 2021/04/16 18:52:35 by rimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	width_s_precision(sign_t *st)
{
	if (st->dot < st->size_c)
	{
		st->size_c = st->dot;
		swap(&st->conv, st->size_c, &st->dot);
		st->dot = 0;
	}
}
