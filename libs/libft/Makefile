.PHONY:		all clean fclean re
MACHINE 	:= $(shell uname -m)

NAME		= libft-$(MACHINE).a
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror -MMD
RM			= rm -rf

INCLUDES	= ./includes
SRCS_DIR	= ./src
OBJS_DIR	= ./obj

rwildcard	= $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2) $(filter $(subst *,%,$2),$d))
SRCS		= $(call rwildcard, $(SRCS_DIR)/, *.c)
OBJS 		= $(SRCS:%.c=$(OBJS_DIR)/%.o)
DEPS 		= $(OBJS:.o=.d)

$(NAME): $(OBJS)
	$(AR) rcs $(NAME) $^

all: $(NAME)

$(OBJS_DIR)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -I$(INCLUDES) -c $< -o $@

-include $(DEPS)

clean:
	$(RM) $(OBJS_DIR) $(DEPS)

fclean: clean
	$(RM) $(NAME)

re: fclean all