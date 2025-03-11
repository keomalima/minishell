# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lthan <lthan@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/15 14:26:45 by keomalima         #+#    #+#              #
#    Updated: 2025/03/11 10:33:11 by lthan            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = cc
CFLAGS = -Wall -Werror -Wextra -MMD -MP
RM = rm -f

LIBSRCS := src
OBJDIR := objects

LIBFT_SRCS := $(LIBSRCS)/ft_atoi.c $(LIBSRCS)/ft_bzero.c $(LIBSRCS)/ft_calloc.c \
			$(LIBSRCS)/ft_isalnum.c $(LIBSRCS)/ft_isalpha.c $(LIBSRCS)/ft_isascii.c \
			$(LIBSRCS)/ft_isdigit.c $(LIBSRCS)/ft_isprint.c $(LIBSRCS)/ft_memchr.c \
			$(LIBSRCS)/ft_memcmp.c $(LIBSRCS)/ft_memcpy.c $(LIBSRCS)/ft_memmove.c \
			$(LIBSRCS)/ft_memset.c $(LIBSRCS)/ft_strchr.c $(LIBSRCS)/ft_strdup.c \
			$(LIBSRCS)/ft_strlcat.c $(LIBSRCS)/ft_strlcpy.c $(LIBSRCS)/ft_strlen.c \
			$(LIBSRCS)/ft_strncmp.c $(LIBSRCS)/ft_strnstr.c $(LIBSRCS)/ft_strrchr.c \
			$(LIBSRCS)/ft_tolower.c $(LIBSRCS)/ft_toupper.c $(LIBSRCS)/ft_substr.c \
			$(LIBSRCS)/ft_itoa.c $(LIBSRCS)/ft_putchar_fd.c $(LIBSRCS)/ft_putnbr_fd.c \
			$(LIBSRCS)/ft_putstr_fd.c $(LIBSRCS)/ft_split.c $(LIBSRCS)/ft_putendl_fd.c \
			$(LIBSRCS)/ft_striteri.c $(LIBSRCS)/ft_strjoin.c  $(LIBSRCS)/ft_strtrim.c \
			$(LIBSRCS)/ft_strmapi.c $(LIBSRCS)/ft_printf.c $(LIBSRCS)/ft_print_char.c \
			$(LIBSRCS)/ft_print_hex.c $(LIBSRCS)/ft_print_int.c $(LIBSRCS)/ft_print_ptr.c \
			$(LIBSRCS)/get_next_line.c $(LIBSRCS)/get_next_line_utils.c $(LIBSRCS)/ft_strndup.c \
			$(LIBSRCS)/ft_isspace.c $(LIBSRCS)/ft_lstadd_back.c $(LIBSRCS)/ft_lstadd_front.c \
			$(LIBSRCS)/ft_lstclear.c $(LIBSRCS)/ft_lstdelone.c \
			$(LIBSRCS)/ft_lstiter.c $(LIBSRCS)/ft_lstlast.c  $(LIBSRCS)/ft_split_set.c \
			$(LIBSRCS)/ft_lstnew.c $(LIBSRCS)/ft_lstsize.c $(LIBSRCS)/ft_lstmap.c


HEADER := includes/libft.h

OBJS = $(LIBFT_SRCS:$(LIBSRCS)/%.c=$(OBJDIR)/libft/%.o)
DEPS = $($(OBJDIR)/%.o=.d)
-include $(DEPS)
	
all: $(NAME)

$(NAME): $(OBJS)
	@ar rcs $(NAME) $(OBJS)
	@echo "\n\\033[1;32mLibft commpiled \\e[0m🔥🚀\n"

$(OBJDIR)/libft/%.o: $(LIBSRCS)/%.c $(HEADER) Makefile | $(OBJDIR)/libft
	$(CC) $(CFLAGS) -Iincludes -c $< -o $@
	
$(OBJDIR)/libft:
	@mkdir -p $(OBJDIR)/libft

clean:
	@$(RM) -r $(OBJDIR)
	@echo "\033[34mClean libft\033[0m"

fclean: 
	@$(RM) -r $(OBJDIR)
	@$(RM) $(NAME)
	@echo "\033[34mClean libft\033[0m"

re: fclean all

.PHONY: all clean fclean re