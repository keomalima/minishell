# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kricci-d <kricci-d@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/15 14:26:45 by keomalima         #+#    #+#              #
#    Updated: 2025/01/07 10:25:53 by kricci-d         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = cc
CFLAGS = -Wall -Werror -Wextra
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
			$(LIBSRCS)/get_next_line.c $(LIBSRCS)/get_next_line_utils.c

BONUS_SRCS := $(LIBSRCS)/ft_lstadd_back.c $(LIBSRCS)/ft_lstadd_front.c \
			$(LIBSRCS)/ft_lstclear.c $(LIBSRCS)/ft_lstdelone.c \
			$(LIBSRCS)/ft_lstiter.c $(LIBSRCS)/ft_lstlast.c \
			$(LIBSRCS)/ft_lstnew.c $(LIBSRCS)/ft_lstsize.c $(LIBSRCS)/ft_lstmap.c


HEADER := includes/libft.h

OBJS = $(LIBFT_SRCS:$(LIBSRCS)/%.c=$(OBJDIR)/libft/%.o)
BONUS_OBJS = $(BONUS_SRCS:$(LIBSRCS)/%.c=$(OBJDIR)/bonus/%.o)

OBJS = $(LIBFT_SRCS:$(LIBSRCS)/%.c=$(OBJDIR)/libft/%.o)
BONUS_OBJS = $(BONUS_SRCS:$(LIBSRCS)/%.c=$(OBJDIR)/bonus/%.o)

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

bonus : $(NAME) $(BONUS_OBJS) .bonus

.bonus : $(BONUS_OBJS)
	ar rcs $(NAME) $(BONUS_OBJS)
	@touch .bonus

$(OBJDIR)/libft/%.o: $(LIBSRCS)/%.c $(HEADER) Makefile | $(OBJDIR)/libft
	$(CC) $(CFLAGS) -Iincludes -c $< -o $@

$(OBJDIR)/bonus/%.o: $(LIBSRCS)/%.c $(HEADER) Makefile | $(OBJDIR)/bonus
	$(CC) $(CFLAGS) -Iincludes -c $< -o $@

$(OBJDIR)/libft:
	mkdir -p $(OBJDIR)/libft

$(OBJDIR)/bonus:
	mkdir -p $(OBJDIR)/bonus

clean:
	$(RM) -r $(OBJDIR)

fclean: clean
	$(RM) $(NAME) .bonus

re: fclean all

.PHONY: all clean fclean re bonus