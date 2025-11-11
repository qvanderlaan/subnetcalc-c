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
	uint16_t	block_size;
	uint8_t		mask_last_octet;
	uint16_t	network_octet4;
	uint16_t	broadcast_octet4;
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

static uint16_t	calc_block_size(uint8_t prefix)
{
	uint8_t	rem;

	rem = prefix % 8;
	if (rem == 0)
		return (256);
	return (1u << (8 - rem));
}

void	calc_subnet(t_subnet *s)
{
	uint16_t	o4;
	uint16_t	bs;
	uint16_t	net4;
	uint16_t	br4;

	s->host_bits = 32 - s->prefix;
	bs = calc_block_size(s->prefix);
	s->block_size = bs;
	s->mask_last_octet = 256 - bs;
	o4 = s->ip.o4;
	bs = s->block_size;
	net4 = (o4 / bs) * bs;
	br4 = net4 + (bs - 1);
	s->network_octet4 = (uint8_t)(net4 & 0xFF);
	s->broadcast_octet4 = (uint8_t)(br4 & 0xFF);
}

void	print_subnet(const t_subnet *s)
{
	uint8_t	first;
	uint8_t	last;

	first = s->network_octet4 + 1;
	last = s->broadcast_octet4 - 1;
	printf("IP:                  %u.%u.%u.%u\n", s->ip.o1, s->ip.o2, s->ip.o3,
		s->ip.o4);
	printf("PREFIX:              %u\n\n", s->prefix);
	printf("HOST_BITS:           %u\n", s->host_bits);
	printf("BLOCK_SIZE:          %u\n", s->block_size);
	printf("MASK_LAST_OCTET:     %u\n", s->mask_last_octet);
	printf("SUBNET_MASK:         255.255.255.%u\n\n", s->mask_last_octet);
	printf("NETWORK:             %u.%u.%u.%u\n", s->ip.o1, s->ip.o2, s->ip.o3,
		s->network_octet4);
	printf("BROADCAST:           %u.%u.%u.%u\n", s->ip.o1, s->ip.o2, s->ip.o3,
		s->broadcast_octet4);
	if (s->block_size > 2)
	{
		printf("USABLE_RANGE:        %u.%u.%u.%u  ->  %u.%u.%u.%u\n", s->ip.o1,
			s->ip.o2, s->ip.o3, first, s->ip.o1, s->ip.o2, s->ip.o3, last);
		printf("USABLE_HOSTS:        %u\n", s->block_size - 2);
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
