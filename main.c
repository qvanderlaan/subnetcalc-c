#include <ctype.h>
#include <stdint.h>
#include <stdio.h>

typedef struct s_ip
{
	uint8_t		o1;
	uint8_t		o2;
	uint8_t		o3;
	uint8_t		o4;
}				t_ip;

typedef struct s_subnet
{
	t_ip		ip;
	uint8_t		prefix;
	uint8_t		host_bits;
	uint32_t	mask;
	uint32_t	network;
	uint32_t	broadcast;
}				t_subnet;

static int	read_u8(const char **p, uint8_t *v)
{
	int	n;
	int	d;

	n = 0;
	d = 0;
	while (isdigit(**p))
	{
		if (++d > 3)
			return (0);
		n = n * 10 + (**p - '0');
		if (n > 255)
			return (0);
		(*p)++;
	}
	*v = (uint8_t)n;
	return (d > 0);
}

int	parse_ipv4(const char *s, t_subnet *out)
{
	const char	*p = s;

	if (!read_u8(&p, &out->ip.o1) || *p++ != '.')
		return (0);
	if (!read_u8(&p, &out->ip.o2) || *p++ != '.')
		return (0);
	if (!read_u8(&p, &out->ip.o3) || *p++ != '.')
		return (0);
	if (!read_u8(&p, &out->ip.o4) || *p++ != '/')
		return (0);
	if (!read_u8(&p, &out->prefix) || out->prefix > 32)
		return (0);
	return (*p == '\0');
}

void	calc_subnet(t_subnet *s)
{
	uint32_t	ip;

	ip = (s->ip.o1 << 24) | (s->ip.o2 << 16) | (s->ip.o3 << 8) | s->ip.o4;
	s->host_bits = 32 - s->prefix;
	if (s->prefix == 0)
		s->mask = 0;
	else
		s->mask = 0xFFFFFFFF << s->host_bits;
	s->network = ip & s->mask;
	s->broadcast = s->network | ~s->mask;
}

static uint8_t	get_octet(uint32_t value, int index)
{
	return ((value >> (8 * (3 - index))) & 0xFF);
}

void	print_subnet(const t_subnet *s)
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
		return (1); // TODO: Add error
	if (!parse_ipv4(argv[1], &subnet))
		return (1);
	calc_subnet(&subnet);
	print_subnet(&subnet);
	return (0);
}
