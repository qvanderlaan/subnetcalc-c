# IPv4 Subnet Calculator (C)

A minimal IPv4 subnet calculator written in C.
It parses an IPv4 CIDR address and outputs network information.

---

## Features

- Validates IPv4 input
- Computes subnet mask
- Computes network and broadcast addresses
- Shows usable host range and host count

---

## Example

Input:

```bash
./subnetcalc 192.168.10.55/20
```

Output:

```
IP:                  192.168.10.55
PREFIX:              20

HOST_BITS:           12
BLOCK_SIZE:          16
MASK_LAST_OCTET:     240
SUBNET_MASK:         255.255.240.0

NETWORK:             192.168.0.0
BROADCAST:           192.168.15.255
USABLE_RANGE:        192.168.0.1  ->  192.168.15.254
USABLE_HOSTS:        4094
```

---

## Usage

Compile:

```bash
cc -Wall -Wextra -Werror main.c -o subnetcalc
```

Run:

```bash
./subnetcalc <ipv4/cidr>
```

Example:

```bash
./subnetcalc 10.0.5.17/24
```
