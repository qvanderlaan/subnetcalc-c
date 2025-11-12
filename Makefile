# **************************************************************************** #
#                                                                              #
#                                                          ::::::::            #
#   Makefile                                             :+:    :+:            #
#                                                       +:+                    #
#   By: qvan-der <qvan-der@student.codam.nl>           +#+                     #
#                                                     +#+                      #
#   Created: 2025/11/12 12:57:32 by qvan-der        #+#    #+#                 #
#   Updated: 2025/11/12 13:18:23 by qvan-der        ########   odam.nl         #
#                                                                              #
# **************************************************************************** #

# ========= Variables ========= #

NAME			=	subnetcalc

SRC_DIR			=	src/
OBJ_DIR			=	build/
INCLUDE_DIR		=	include/

CC				=	cc
CFLAGS			=	-Wall -Werror -Wextra -I$(INCLUDE_DIR)

# ========= Register Files ========= #

SOURCE_DIR		=	./
SOURCE_CFILES	=	main.c

CALC_DIR		=	/calculation
CALC_CFILES		=	calculate.c parse.c

ERROR_DIR		=	/error
ERROR_CFILES	=	calc_error.c show_usage.c

HELPER_DIR		=	/helpers
HELPER_CFILES	=	get_octet.c read_u8.c

CFILES			=	$(addprefix $(SOURCE_DIR), $(SOURCE_CFILES)) \
					$(addprefix $(CALC_DIR)/, $(CALC_CFILES)) \
					$(addprefix $(ERROR_DIR)/, $(ERROR_CFILES)) \
					$(addprefix $(HELPER_DIR)/, $(HELPER_CFILES))

SRC_FILES		=	$(addprefix $(SRC_DIR), $(CFILES))
OBJ_FILES		=	$(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))

# ========= Register Functions ========= #

all: $(NAME)

$(NAME): $(OBJ_FILES)
	$(CC) $(CFLAGS) $(OBJ_FILES) -o $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all tester test valgrind clean fclean re
