/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: qvan-der <qvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/11/12 12:59:13 by qvan-der      #+#    #+#                 */
/*   Updated: 2025/11/12 13:15:56 by qvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <subnetcalc.h>

static void	print_subnet(const t_subnet *s)
{
	uint32_t	usable_hosts;
	uint32_t	first;
	uint32_t	last;

	usable_hosts = (s->host_bits >= 2) ? ((1u << s->host_bits) - 2) : 0;
	first = s->network + 1;
	last = s->broadcast - 1;
	printf("IP:                  %u.%u.%u.%u\n", s->ip.o1, s->ip.o2, s->ip.o3,
		s->ip.o4);
	printf("PREFIX:              %u\n\n", s->prefix);
	printf("HOST_BITS:           %u\n", s->host_bits);
	printf("SUBNET_MASK:         %u.%u.%u.%u\n", get_octet(s->mask, 0),
		get_octet(s->mask, 1), get_octet(s->mask, 2), get_octet(s->mask, 3));
	printf("\nNETWORK:             %u.%u.%u.%u\n", get_octet(s->network, 0),
		get_octet(s->network, 1), get_octet(s->network, 2),
		get_octet(s->network, 3));
	printf("BROADCAST:           %u.%u.%u.%u\n", get_octet(s->broadcast, 0),
		get_octet(s->broadcast, 1), get_octet(s->broadcast, 2),
		get_octet(s->broadcast, 3));
	if (usable_hosts > 0)
	{
		printf("USABLE_RANGE:        %u.%u.%u.%u  ->  %u.%u.%u.%u\n",
			get_octet(first, 0), get_octet(first, 1), get_octet(first, 2),
			get_octet(first, 3), get_octet(last, 0), get_octet(last, 1),
			get_octet(last, 2), get_octet(last, 3));
		printf("USABLE_HOSTS:        %u\n", usable_hosts);
	}
	else
	{
		printf("USABLE_RANGE:        none\n");
		printf("USABLE_HOSTS:        0\n");
	}
}

int	main(int argc, char **argv)
{
	t_subnet	subnet;

	if (argc != 2)
		return (show_usage());
	if (!parse_ipv4(argv[1], &subnet))
		return (calc_error());
	calc_subnet(&subnet);
	print_subnet(&subnet);
	return (0);
}
