# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: apetitje <apetitje@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/01/15 19:00:52 by apetitje          #+#    #+#              #
#    Updated: 2017/02/10 19:20:11 by apetitje         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = clang
AR = ar
ARFLAGS = rc
RM = /bin/rm -f

DIRLIB = libs
DIROBJ = .obj
DIRDEP = .deps

NAME = fdf

SRCS=		\
			fdf.c										\
			input.c										\
			draw_func.c									\
			event_func.c								\

LIBS 	=	\
	   		$(DIRLIB)/libft/libftprintf.a				\
			$(DIRLIB)/minilibx_macos/libmlx.a			\
			
LDFLAGS = 	\
			-L $(DIRLIB)/libft							\
			-L $(DIRLIB)/minilibx_macos					\

LDLIBS	=	\
			-lftprintf									\
			-lmlx -framework OpenGL -framework Appkit	\

CPPFLAGS = 	\
		   	-I $(DIRLIB)/libft/inc						\
			-I $(DIRLIB)/minilibx_macos					\

CFLAGS = -Wall -Wextra -Werror -ggdb

DEPFLAGS =	\
			-MT $@ -MMD -MP -MF $(DIRDEP)/$*.Td			\

COMPILE.c =	$(CC) $(DEPFLAGS) $(CFLAGS) $(CPPFLAGS) -c

POSTCOMPILE =  mv -f $(DIRDEP)/$*.Td $(DIRDEP)/$*.d

SRC = $(SRCS)

OBJ = $(addprefix $(DIROBJ)/, $(SRCS:.c=.o))

$(DIROBJ)	:
	@mkdir -p $(DIROBJ)

$(DIRDEP)	:
	@mkdir -p $(DIRDEP)

all : libs $(NAME)

$(NAME) : $(DIROBJ) $(DIRDEP) $(OBJ) $(LIBS)
	@$(CC) $(OBJ) -o $(NAME) $(LDFLAGS) $(LDLIBS)

libs		:
	@make -C $(DIRLIB)/libft
	@make -C $(DIRLIB)/minilibx_macos

fcleanlibs	:
	@make -C $(DIRLIB)/libft fclean

clean :
	@$(RM) -r $(DIROBJ)
	@$(RM) -r $(DIRDEP)

fclean : clean
	@$(RM) $(NAME)

re : fcleanlibs fclean all

$(DIROBJ)/%.o	:	%.c
$(DIROBJ)/%.o	:	%.c $(DIRDEP)/%.d
	@mkdir -p $(dir $@)
	@mkdir -p $(dir $(word 2,$^))
	@printf "%s %s\n" "$(NAME)" "compiling $<..."
	@$(COMPILE.c) $(OUTPUT_OPTION) $<
	@$(POSTCOMPILE)
	@printf "complete\n"

$(DIRDEP)/%.d	:	;
.PRECIOUS		:	$(DIRDEP)/%.d
-include $(patsubst %,$(DIRDEP)/%.d,$(basename $(SRC)))

.PHONY : all clean fclean re fcleanlibs libs 
