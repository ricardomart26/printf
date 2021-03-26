/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 14:47:34 by rimartin          #+#    #+#             */
/*   Updated: 2021/03/21 15:31:02 by rimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

// Verificar se esta a contar bem as palavras
// Ver se e melhor fazer uma função para escrever e depois as flags ou vice versa
// Ver o 0
// Perguntar se temos que meter o 0x ja que o # faz isso

int print_until_perc(char *fmt, sign_t *st) // Write até ao %
{
	int c;

	c = 0;
	while (fmt[c] != '%' && fmt[c] != '\0')
		ft_putchar(fmt[c++], st);
	return (c);
}

int size_per(char *fmt, sign_t *st)
{
	int counter;

	counter = 0;
	if (fmt[counter + 1] == '%')
		return (2);

	while ((!type(fmt[counter])))
		counter++;
	if (type(fmt[counter]))
	{
		st->c = fmt[counter];
		return (counter + 1);
	}

	return (1);
}

void with_no_flags(va_list args, sign_t *st)
{
	st->conv = ft_get_arg(args, st);
	if (st->c == 'c')
		ft_putchar(st->conv[0], st);
	else
		ft_putstr_fd(st->conv, 1, st);
	free_if_needed(st);
}

void start_loop(char *fmt, va_list args, sign_t *st)
{
	int size_perc;

	st->words = 0;
	while (*fmt != '\0')
	{
		printf("\nbe words = %d", st->words);
		init_struct(st);
		fmt += print_until_perc((char *)fmt, st);
		printf("\naf words = %d", st->words);
		
		if (*fmt == '\0')
			break;
		size_perc = size_per((char *)fmt, st);
		if (size_perc == 2)
			if (fmt[1] == '%')
				write(1, "%%", 1);
			else
				with_no_flags(args, st);
		else if (size_perc > 2)
			with_flags(st, fmt, args);
		fmt += size_perc;
	}
}

int ft_printf(const char *fmt, ...)
{
	va_list args;
	sign_t st;

	if (!fmt)
		return (0);
	if (invalid(fmt) != 0)
		return (-1);

	va_start(args, (char *)fmt);
	start_loop((char *)fmt, args, &st);
	va_end(args);
	return (st.words);
}

// String com so um . tem precision 0 e nao escreve
// Com a width negativa
// d = -2 Se tiver uma precisio de 10 o menos tem de ser antes do 0

	// int b = -1;
	// int *ptr = &b;
int main(void)
{
	int d;

	// printf("%d\n", d);
	// ft_printf(" %p ", ptr);
	// printf(" %p ", ptr);

	// printf("%d\n", d);
	// d = printf("%*c  d\n", -2, '0');
	// printf("%d\n", d);
	// d = ft_printf("%*c  d\n", -2, '0');
	// printf("%d\n", d);
	// d = printf("%*c  d\n", -10, '0');
	// printf("%d\n", d);
	// d = ft_printf("%*c  d\n", -10, '0');
	// printf("%d\n", d);
	// d = printf("\n\n%-c%-c%c*\n", 1, '0', 0);
	// printf("d = %d\n", d);
	// d = ft_printf("%-c%-c%c*\n", 1, '0', 0);
	// printf("d = %d\n", d);

	d = printf("teste %.d\n", 0);
	printf("%d\n", d);
	d = printf("teste %-.2d \n", 0);
	printf("%d\n", d);
	d = printf("teste %-2.2d \n", 0);
	printf("%d\n", d);
	d = printf("teste %-3.2d \n", 0);
	printf("%d\n", d);
	d = printf("teste %-3.2dteste %10.42d \n", 0, 0);
	printf("%d\n", d);
	d = printf("teste %-3.2dteste %10.42d \n", 1, -1);
	printf("%d\n", d);
	d = printf("teste %-3.2dteste %10.42d \n", 10, -10);
	printf("%d\n", d);
	d = printf(" *%-*.*d* *%*.*d* \n", 4, 5, 10, 10, 21, -10);
	printf("%d\n", d);	
	d = printf(" *%-*.*d* *%*.*d* \n", 6, 2, 102, 10, 21, -101);
	printf("%d\n\n", d);

	d = ft_printf("teste %.d\n", 0);
	printf("%d\n", d);
	d = ft_printf("teste %-.2d \n", 0);
	printf("%d\n", d);
	d = ft_printf("teste %-2.2d \n", 0);
	printf("%d\n", d);
	d = ft_printf("teste %-3.2d \n", 0);
	printf("%d\n", d);
	d = ft_printf("teste %-3.2d teste %10.42d \n", 0, 0);
	printf("%d\n", d);
	d = ft_printf("teste %-3.2d teste %10.42d \n", 1, -1);
	printf("%d\n", d);
	d = ft_printf("teste %-3.2d %10.42d \n", 10, -10);
	printf("%d\n", d);
	d = ft_printf(" *%-*.*d* *%*.*d* \n", 4, 5, 10, 10, 21, -10);
	printf("%d\n", d);
	d = ft_printf(" *%-*.*d* *%*.*d* \n\n", 6, 2, 102, 10, 21, -101);
	printf("%d\n", d);

	// 	printf(" %s %s\n", "0", "1");
	// 	ft_printf(" %s %s\n", "0", "1");

	// 	return (0);
}

















// 	// O 0 nem a precisao, nao funcionam para strings!

// 	// int main()
// 	// {
// 	// 	char str[8] = "Ricardo";
// 	// 	char c = 'i';
// 	// 	int d = 1020;
// 	// 	unsigned int u = 60;
// 	// 	unsigned int v = -60;
// 	// 	unsigned int hexa = -65464872;
// 	// 	int *ptr;
// 	// 	int b;
// 	// 	int number = 30;
// 	// 	b = 5;

// 	// 	ptr = &b;

// 	// ft_printf("\n\n\t\tSEM FLAGS\n\n");

// 	// printf("printf = %s\n", "ola tudo bem?");
// 	// ft_printf("meu printf = %s\n", "ola tudo bem?");
// 	// printf("printf = %d\n", 41);
// 	// ft_printf("meu printf = %d\n", 41);
// 	// printf("printf = %i\n", 41);
// 	// ft_printf("meu printf = %i\n", 41);
// 	// printf("printf = %x\n", 41);
// 	// ft_printf("meu printf = %x\n", 41);
// 	// printf("printf = %X\n", 41);
// 	// ft_printf("meu printf = %X\n", 41);
// 	// printf("printf = %c\n", "ola tudo bem?");
// 	// ft_printf("meu printf = %c\n", "ola tudo bem?");
// 	// printf("printf = %p\n", ptr);
// 	// ft_printf("meu printf = %p\n", ptr);
// 	// printf("printf = %u\n", -41);
// 	// ft_printf("meu printf = %u\n", -41);

// 	// ft_printf("\n\n\t\tCOM WIDTH A MAIS\n\n");

// 	// printf("printf = %25s\n", "ola tudo bem?");
// 	// ft_printf("meu printf = %25s\n", "ola tudo bem?");
// 	// printf("printf = %5d\n", 41);
// 	// ft_printf("meu printf = %5d\n", 41);
// 	// printf("printf = %5i\n", 41);
// 	// ft_printf("meu printf = %5i\n", 41);
// 	// printf("printf = %5x\n", 41);
// 	// ft_printf("meu printf = %5x\n", 41);
// 	// printf("printf = %5X\n", 41);
// 	// ft_printf("meu printf = %5X\n", 41);
// 	// printf("printf = %5c\n", 'c');
// 	// ft_printf("meu printf = %5c\n", 'c');
// 	// printf("printf = %15p\n", ptr);
// 	// ft_printf("meu printf = %15p\n", ptr);
// 	// printf("printf = %5u\n", 41);
// 	// ft_printf("meu printf = %5u\n", 41);

// 	// ft_printf("\n\n\t\tCOM WIDTH A MENOS\n\n\n");

// 	// printf("printf = %5s\n", "ola tudo bem?");
// 	// ft_printf("meu printf = %5s\n", "ola tudo bem?");
// 	// printf("printf = %2d\n", 4153);
// 	// ft_printf("meu printf = %2d\n", 4153);
// 	// printf("printf = %2x\n", 4153);
// 	// ft_printf("meu printf = %2x\n", 4153);
// 	// printf("printf = %2X\n", 4123);
// 	// ft_printf("meu printf = %2X\n", 4123);
// 	// printf("printf = %2c\n", 'c');
// 	// ft_printf("meu printf = %2c\n", 'c');
// 	// printf("printf = %2p\n", ptr);
// 	// ft_printf("meu printf = %2p\n", ptr);
// 	// printf("printf = %2u\n", 4123);
// 	// ft_printf("meu printf = %2u\n", 4123);

// 	// ft_printf("\n\n\t\tCOM PRECISAO MAIS\n\n\n");
// 	// printf("printf = %.25s\n", "ola tudo bem?");
// 	// ft_printf("meu printf = %.25s\n", "ola tudo bem?");
// 	// printf("printf = %.5d\n", 4153);
// 	// ft_printf("meu printf = %.5d\n", 4153);
// 	// printf("printf = %.5x\n", 4153);
// 	// ft_printf("meu printf = %.5x\n", 4153);
// 	// printf("printf = %.5X\n", 4153);
// 	// ft_printf("meu printf = %.5X\n", 4153);
// 	// printf("printf = %.5c\n", 'c');
// 	// ft_printf("meu printf = %.5c\n", 'c');
// 	// printf("printf = %.5p\n", ptr);
// 	// ft_printf("meu printf = %.5p\n", ptr);
// 	// printf("printf = %.5u\n", 4153);
// 	// ft_printf("meu printf = %.5u\n", 4153);

// 	// ft_printf("\n\n\t\tCOM PRECISAO MENOS\n\n\n");

// 	// printf("printf = %.5s\n", "ola tudo bem?");
// 	// ft_printf("meu printf = %.5s\n", "ola tudo bem?");
// 	// printf("printf = %.2d\n", 4123);
// 	// ft_printf("meu printf = %.2d\n", 4123);
// 	// printf("printf = %.2x\n", 4123);
// 	// ft_printf("meu printf = %.2x\n", 4123);
// 	// printf("printf = %.2X\n", 4123);
// 	// ft_printf("meu printf = %.2X\n", 4123);
// 	// printf("printf = %.2c\n", 'c');
// 	// ft_printf("meu printf = %.2c\n", 'c');
// 	// printf("printf = %.2p\n", ptr);
// 	// ft_printf("meu printf = %.2p\n", ptr);
// 	// printf("printf = %.2u\n", 4153);
// 	// ft_printf("meu printf = %.5u\n", 4153);

// 	// ft_printf("\n\n\t\tALIGN COM WIDTH MENOR\n\n\n");

// 	// printf("printf = %25.30s ahahaha\n", "ola tudo bem?");
// 	// ft_printf("meu printf = %25.30s ahahaha\n", "ola tudo bem?");
// 	// printf("printf = %10.15d ahahaha\n", 4123);
// 	// ft_printf("meu printf = %10.15d ahahaha\n", 4123);
// 	// printf("printf = %10.15x ahahaha\n", 4123);
// 	// ft_printf("meu printf = %10.15x ahahaha\n", 4123);
// 	// printf("printf = %10.15X ahahaha\n", 4123);
// 	// ft_printf("meu printf = %10.15X ahahaha\n", 4123);
// 	// printf("printf = %10.15c ahahaha\n", 'c');
// 	// ft_printf("meu printf = %10.15c ahahaha\n", 'c');
// 	// printf("printf = %10.15p ahahaha\n", ptr);
// 	// ft_printf("meu printf = %10.15p ahahaha\n", ptr);
// 	// printf("printf = %10.15u ahahaha\n", 41103);
// 	// ft_printf("meu printf = %10.15u ahahaha\n", 4153);

// 	// ft_printf("\n\n\t\tALIGN COM WIDTH MAIOR\n\n\n");

// 	// printf("printf = %30.25s ahahaha\n", "ola tudo bem?");
// 	// ft_printf("meu printf = %30.25s ahahaha\n", "ola tudo bem?");

// 	// printf("printf = %20.10d ahahaha\n", 4123);
// 	// ft_printf("meu printf = %20.10d ahahaha\n", 4123);
// 	// printf("printf = %20.10x ahahaha\n", 4123);
// 	// ft_printf("meu printf = %20.10x ahahaha\n", 4123);
// 	// printf("printf = %20.10X ahahaha\n", 4123);
// 	// ft_printf("meu printf = %20.10X ahahaha\n", 4123);
// 	// printf("printf = %20.10c ahahaha\n", 'c');
// 	// ft_printf("meu printf = %20.10c ahahaha\n", 'c');
// 	// printf("printf = %20.30p ahahaha\n", ptr);
// 	// ft_printf("meu printf = %20.10p ahahaha\n", ptr);
// 	// printf("printf = %20.10u ahahaha\n", 41103);
// 	// ft_printf("meu printf = %20.10u ahahaha\n", 4153);

// 	// ft_printf("\n\n\t\tCOM ZERO\n\n\n");

// 	// printf("printf = %0s\n", "ola tudo bem?");
// 	// ft_printf("meu printf = %0s\n", "ola tudo bem?");
// 	// printf("printf = %0d\n", 4123);
// 	// ft_printf("meu printf = %0d\n", 4123);
// 	// printf("printf = %0x\n", 4123);
// 	// ft_printf("meu printf = %0x\n", 4123);
// 	// printf("printf = %0X\n", 4123);
// 	// ft_printf("meu printf = %0X\n", 4123);
// 	// printf("printf = %0c\n", 'c');
// 	// ft_printf("meu printf = %0c\n", 'c');
// 	// printf("printf = %0p\n", ptr);
// 	// ft_printf("meu printf = %0p\n", ptr);
// 	// printf("printf = %0u\n", 4153);
// 	// ft_printf("meu printf = %0u\n", 4153);

// 	// ft_printf("\n\n\t\tALIGN COM WIDTH\n\n\n");

// 	// printf("printf = %-25s ahahaha\n", "ola tudo bem?");
// 	// ft_printf("meu printf = %-25s ahahaha\n", "ola tudo bem?");
// 	// printf("printf = %-10d ahahaha\n", 4123);
// 	// ft_printf("meu printf = %-10d ahahaha\n", 4123);
// 	// printf("printf = %-10x ahahaha\n", 4123);
// 	// ft_printf("meu printf = %-10x ahahaha\n", 4123);
// 	// printf("printf = %-10X ahahaha\n", 4123);
// 	// ft_printf("meu printf = %-10X ahahaha\n", 4123);
// 	// printf("printf = %-10c ahahaha\n", 'c');
// 	// ft_printf("meu printf = %-10c ahahaha\n", 'c');
// 	// printf("printf = %-10p ahahaha\n", ptr);
// 	// ft_printf("meu printf = %-10p ahahaha\n", ptr);
// 	// printf("printf = %-10u ahahaha\n", 41103);
// 	// ft_printf("meu printf = %-10u ahahaha\n", 4153);

// 	// ft_printf("\n\n\t\tALIGN COM PRECISAO MAIS\n\n\n");

// 	// printf("printf = %-.25s ahahaha\n", "ola tudo bem?");
// 	// ft_printf("meu printf = %-.25s ahahaha\n", "ola tudo bem?");
// 	// printf("printf = %-.10d ahahaha\n", 4123);
// 	// ft_printf("meu printf = %-.10d ahahaha\n", 4123);
// 	// printf("printf = %-.10x ahahaha\n", 4123);
// 	// ft_printf("meu printf = %-.10x ahahaha\n", 4123);
// 	// printf("printf = %-.10X ahahaha\n", 4123);
// 	// ft_printf("meu printf = %-.10X ahahaha\n", 4123);
// 	// printf("printf = %-.10c ahahaha\n", 'c');
// 	// ft_printf("meu printf = %-.10c ahahaha\n", 'c');
// 	// printf("printf = %-.10p ahahaha\n", ptr);
// 	// ft_printf("meu printf = %-.10p ahahaha\n", ptr);
// 	// printf("printf = %-.10u ahahaha\n", 41103);
// 	// ft_printf("meu printf = %-.10u ahahaha\n", 4153);

// 	// ft_printf("\n\n\t\tALIGN COM WIDTH MENOR\n\n\n");

// 	// printf("printf = %-25.30s ahahaha\n", "ola tudo bem?");
// 	// ft_printf("meu printf = %-25.30s ahahaha\n", "ola tudo bem?");
// 	// printf("printf = %-10.15d ahahaha\n", 4123);
// 	// ft_printf("meu printf = %-10.15d ahahaha\n", 4123);
// 	// printf("printf = %-10.15x ahahaha\n", 4123);
// 	// ft_printf("meu printf = %-10.15x ahahaha\n", 4123);
// 	// printf("printf = %-10.15X ahahaha\n", 4123);
// 	// ft_printf("meu printf = %-10.15X ahahaha\n", 4123);
// 	// printf("printf = %-10.15c ahahaha\n", 'c');
// 	// ft_printf("meu printf = %-10.15c ahahaha\n", 'c');
// 	// printf("printf = %-10.15p ahahaha\n", ptr);
// 	// ft_printf("meu printf = %-10.15p ahahaha\n", ptr);

// 	// printf("printf = %-10.15u ahahaha\n", 41103);
// 	// ft_printf("meu printf = %-10.15u ahahaha\n", 41103);

// 	// ft_printf("\n\n\t\tALIGN COM WIDTH MAIOR\n\n\n");

// 	// printf("printf = %-30.25s ahahaha\n", "ola tudo bem?");
// 	// ft_printf("meu printf = %-.25s ahahaha\n", "ola tudo bem?");

// 	// printf("printf = %-20.10d ahahaha\n", 4123);
// 	// ft_printf("meu printf = %-20.10d ahahaha\n", 4123);
// 	// printf("printf = %-20.10x ahahaha\n", 4123);
// 	// ft_printf("meu printf = %-20.10x ahahaha\n", 4123);
// 	// printf("printf = %-20.10X ahahaha\n", 4123);
// 	// ft_printf("meu printf = %-20.10X ahahaha\n", 4123);
// 	// printf("printf = %-20.10c ahahaha\n", 'c');
// 	// ft_printf("meu printf = %-20.10c ahahaha\n", 'c');
// 	// printf("printf = %-20.10p ahahaha\n", ptr);
// 	// ft_printf("meu printf = %-20.10p ahahaha\n", ptr);
// 	// printf("printf = %-20.10u ahahaha\n", 41103);
// 	// ft_printf("meu printf = %-20.10u ahahaha\n", 4153);

// 	// printf("%s\n%s\n", "ola tudo bem?", "sim e contigo?");
// 	// printf("%s%s\n", "ola tudo", " bem?");
// 	// printf("%s %s\n", "ola tudo", " bem?");
// 	// printf("%5s\n", "ola tudo bem?");
// 	// printf("%25s\n", "ola tudo bem?");
// 	// printf("%.35s\n", "ola tudo bem?");
// 	// printf("%16.23s\n", "ola tudo bem?");
// 	// printf("%3.s\n", "ola tudo bem?");
// 	// printf("%5.22s\n", "ola tudo bem?");
// 	// printf("%22.5s\n", "ola tudo bem?");
// 	// printf("%22.20s\n", "ola tudo bem?");
// 	// printf("%-24s coisas a frente\n", "ola tudo bem?");
// 	// printf("%-26.30s coisas a frente\n", "ola tudo bem?");
// 	// printf("%-14s coisas a frente\n", "ola tudo bem?");
// 	// printf("%-.23s coisas a frente\n", "ola tudo bem?");
// 	// printf("%23s\n", "ola tudo bem?");
// 	// printf("%12s\n", "ola tudo bem?");
// 	// printf("%.24s\n", "ola tudo bem?");
// 	// printf("%.12s\n", "ola tudo bem?");
// 	// printf("%24.28s\n", "ola tudo bem?");
// 	// printf("%28.24s\n", "ola tudo bem?");
// 	// printf("%s\n", "ola tudo bem?");

// 	// printf("%s\n", "ola tudo bem?");
// 	// printf("%s\n%s\n", "ola tudo bem?", "sim e contigo?");
// 	// printf("%s%s\n", "ola tudo", " bem?");
// 	// printf("%s %s\n", "ola tudo", " bem?");
// 	// printf("%5s\n", "ola tudo bem?");
// 	// printf("%25s\n", "ola tudo bem?");
// 	// printf("%.35s\n", "ola tudo bem?");
// 	// printf("%16.23s\n", "ola tudo bem?");
// 	// printf("%3.s\n", "ola tudo bem?");
// 	// printf("%5.22s\n", "ola tudo bem?");
// 	// printf("%22.5s\n", "ola tudo bem?");
// 	// printf("%22.20s\n", "ola tudo bem?");
// 	// printf("%-24s coisas a frente\n", "ola tudo bem?");
// 	// printf("%-26.30s coisas a frente\n", "ola tudo bem?");
// 	// printf("%-14s coisas a frente\n", "ola tudo bem?");
// 	// printf("%-.23s coisas a frente\n", "ola tudo bem?");
// 	// printf("%23s\n", "ola tudo bem?");
// 	// printf("%12s\n", "ola tudo bem?");
// 	// printf("%.24s\n", "ola tudo bem?");
// 	// printf("%.12s\n", "ola tudo bem?");
// 	// printf("%24.28s\n", "ola tudo bem?");
// 	// printf("%28.24s\n", "ola tudo bem?");
// 	// printf("%s\n", "ola tudo bem?");

// 	// ft_printf("\n\n MEU PRINTF \n\n");

// 	// ft_printf("%s\n", "ola tudo bem?"); // Certo
// 	// ft_printf("%s\n%s\n", "ola tudo bem?", "sim e contigo?"); // Certo

// 	// ft_printf("%s%s\n", "ola tudo", " bem?"); // Certo
// 	// ft_printf("%s %s\n", "ola tudo", " bem?"); // Certo
// 	// ft_printf("%5s\n", "ola tudo bem?"); // Certo
// 	// ft_printf("%25s\n", "ola tudo bem?");
// 	// ft_printf("%.35s\n", "ola tudo bem?");
// 	// ft_printf("%16.23s\n", "ola tudo bem?");
// 	// ft_printf("%3.s\n", "ola tudo bem?");
// 	// ft_printf("%5.22s\n", "ola tudo bem?");
// 	// ft_printf("%22.5s\n", "ola tudo bem?");
// 	// ft_printf("%22.20s\n", "ola tudo bem?");
// 	// ft_printf("%-24s coisas a frente\n", "ola tudo bem?");
// 	// ft_printf("%-26.30s coisas a frente\n", "ola tudo bem?");
// 	// ft_printf("%-14s coisas a frente\n", "ola tudo bem?");
// 	// ft_printf("%-.23s coisas a frente\n", "ola tudo bem?");
// 	// ft_printf("%23s\n", "ola tudo bem?");
// 	// ft_printf("%12s\n", "ola tudo bem?");
// 	// ft_printf("%.24s\n", "ola tudo bem?");
// 	// ft_printf("%.12s\n", "ola tudo bem?");
// 	// ft_printf("%24.28s\n", "ola tudo bem?");
// 	// ft_printf("%28.24s\n", "ola tudo bem?");
// 	// ft_printf("%s\n", "ola tudo bem?");

// 	// printf("TESTE STRING PRINTF = Este e o resultado do %s printf real %s \n", str, str);
// 	// ft_printf("TESTE STRING MEU PRINTF = Este e o resultado do %s meu printf. %s\n", str, str);

// 	// printf("\nTESTE PRINTF = %% (precent) e sem args\n");
// 	// ft_printf("MEU PRINTF = %% (percent) e sem args\n");

// 	// printf("\nTESTE CHAR = %c (char)\n", c);
// 	//  ft_printf("MEU PRINTF CHAR = %c (char)\n", c);

// 	// // printf("\nTESTE NUMBER = %i = 10 (i) , %d (d)= 55 \n", i, d);
// 	// ft_printf("MEU PRINTF NUMBER = %i = 10 (i) , %d (d) = 55 \n", i, d );

// 	// printf("\nTESTE UNSIGNED = %u = 60 (u) , %u (u) = 60 \n", u, v);
// 	// ft_printf("MEU PRINTF UNSIGNED = %u = 60 (u) , %u (u) = -60 \n", u, v);

// 	// printf("\nHexadecimal = %x (x) , %X (X)\n", 10241241, 10241241);
// 	// ft_printf("MEU HEXA = %x (x), %X (X)\n", 10241241, 10241241); // nao funciona com numeros negativos.

// 	// printf("\n\nTESTE POINTER: %p (p)\n", ptr);
// 	// ft_printf("MEU PTR = %p (p)\n\n", ptr);

// 	// printf("Teste ao meu new-line.");
// 	// ft_printf("\nTeste s.kmfao meu new-line.");

// 	// ft_printf("Teste\a ao meu\a bell char\n\n."); //TERMINAL DON'T RING
// 	// printf("Teste\a ao verdadeiro\a bell char\n\n."); //TERMINAL DON'T RING

// 	// ft_printf("Teste\f ao meu\f form feed char\f.\n");
// 	// printf("\nTeste\f ao verdadeiro\f form feed char\f.\n");

// 	// ft_printf("Teste\r ao meu\r return carriage char\r.\n");
// 	// printf("Teste\r ao verdadeiro\r return carriage char\r.\n");

// 	// ft_printf("Teste\tao meu\ttab char\t.\n");
// 	// printf("Teste\t ao verdadeiro\ttab char\t.\n");

// 	// ft_printf("Teste\vao meu \vvertical tab char\v .\n");
// 	// printf("Teste\vao verdadeiro \vvertical tab char\v .\n");

// 	// ft_printf("Teste\'ao meu \'single quote char\' .\n");
// 	// printf("Teste\'ao verdadeiro \'single quote char\' .\n");

// 	// ft_printf("Teste\"ao meu \"double quote char\" .\n");
// 	// printf("Teste\"ao verdadeiro \"double quote char\" .\n");

// 	// ft_printf("Teste\\ao meu \\backslash char\\ .\n");
// 	// printf("Teste\\ao verdadeiro \\backslash char\\ .\n");

// 	// ft_printf("teste num \126\n");
// 	// printf("test num  \126\n");

// 	// printf("Teste Width real: .%4d (d) , .%5d (5d)\n", d, d);
// 	// ft_printf("Teste Width: .%4d (d) , .%100d (5d)\n", d, d);

// 	// printf("\nTeste Width star real: .%*d (5d)\n", 5, d);
// 	// ft_printf("Teste Width star meu: .%*d (*8d)\n", 8, d);

// 	// printf("\nTeste align real: .%-5d (-5d) , .%-*d (-*d)",  d, 8, d);
// 	// ft_printf("\nTeste align meu: .%-*d (-*d)\n", 8, d);

// 	// printf("printf real = %10.5d\n", 10); // (  00010)
// 	// ft_printf("meu printf = %10.5d\n", 10); // (  00010)

// 	// printf(" %-10d \n", number);
// 	// printf(" %010d \n", number);
// 	// printf(" %-#10x \n", number);
// 	// printf(" %#x \n", 100);

// 	// printf(" %x \n", 100);
// 	// printf(" %+d \n", 100);
// 	// printf(" % d \n", -100);

// 	// printf("\n%.6d\n", 42);
// 	// 	ft_printf("\nasgaijgfij %10.6d meu \n", 424242);

// 	// 	return 0;
// //}