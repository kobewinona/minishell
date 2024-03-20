.PHONY:			all clean fclean re
MACHINE 		:= $(shell uname -m)
NAME			= minishell

CC				= gcc
# CFLAGS			= -g -Wall -Wextra -Werror -MMD
CFLAGS			= -g -MMD
RM				= rm -rf

INCLUDES		= ./includes
SRCS_DIR		= ./src
UTILS_DIR		= ./utils
LIBFT_DIR		= ./libs/libft
LIBS_DIR		= ./libs
OBJS_DIR		= ./obj

LIBFT			= -lft-$(MACHINE)

rwildcard		= $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2) $(filter $(subst *,%,$2),$d))
SRCS			= $(call rwildcard, $(SRCS_DIR)/, *.c) $(call rwildcard, $(UTILS_DIR)/, *.c)
OBJS 			= $(SRCS:%.c=$(OBJS_DIR)/%.o)
DEPS 			= $(OBJS:.o=.d)
LIBS			= -L$(LIBFT_DIR) $(LIBFT) -lreadline

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBS) -I$(INCLUDES)

all: libft $(NAME)
	
$(OBJS_DIR)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -I$(INCLUDES) -c $< -o $@

-include $(DEPS)

libft:
	$(MAKE) -C $(LIBFT_DIR)

clean:
	$(RM) $(OBJS_DIR) $(DEPS)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME)

re: fclean all