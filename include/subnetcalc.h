/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   subnetcalc.h                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: qvan-der <qvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/11/12 12:58:21 by qvan-der      #+#    #+#                 */
/*   Updated: 2025/11/12 13:14:31 by qvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SUBNETCALC_H
# define SUBNETCALC_H

# include <stdint.h>

// --- Structs ---

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

// --- Function Declarations ---

void			calc_subnet(t_subnet *s);
int				parse_ipv4(const char *s, t_subnet *out);
int				calc_error(void);
int				show_usage(void);
uint8_t			get_octet(uint32_t value, int index);
int				read_u8(const char **p, uint8_t *v);

#endif
