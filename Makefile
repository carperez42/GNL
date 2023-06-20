# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: carperez <carperez@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/17 18:42:11 by carperez          #+#    #+#              #
#    Updated: 2023/06/17 18:42:11 by carperez         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#variable definition
NAME = get_next_line.a
#paths
DIR_OBJ = obj/
#C files
FILES_MANDATORY = get_next_line.c get_next_line_utils.c
FILES_BONUS = get_next_line_bonus.c get_next_line_utils_bonus.c
#O files 
OBJECTS_MANDATORY = $(addprefix $(DIR_OBJ),$(FILES_MANDATORY:.c=.o))
OBJECTS_BONUS = $(addprefix $(DIR_OBJ),$(FILES_BONUS:.c=.o))
#commands 
COM_COMPILER = gcc
COM_FLAGS= -Wall -Werror -Wextra -I
COM_STATICLIB = ar rcs
COM_TEMPS = .cache_exists
COM_FOLDERS = mkdir -p
COM_REMOVE = rm -f

#UPDATE static lib
all:			$(NAME)
$(NAME):		$(OBJECTS_MANDATORY)
					@$(COM_STATICLIB) $@ $^
bonus:			$(OBJECTS_MANDATORY) $(OBJECTS_BONUS)
					@$(COM_STATICLIB) $(NAME) $^
#COMPILATION
$(DIR_OBJ)%.o:	%.c | $(COM_TEMPS)
					@$(COM_COMPILER) $(COM_FLAGS) -I -c $< -o $@			
#CREATION temp folders
$(COM_TEMPS):
					@$(COM_FOLDERS) $(DIR_OBJ)
#REMOVE temp files
clean:
					@$(COM_REMOVE) -rf $(DIR_OBJ)
					@$(COM_REMOVE) -f $(COM_TEMPS)
#REMOVE compilation
fclean: 		clean
					@$(COM_REMOVE) -f $(NAME)
#CLEAN environmnet					
re: 			fclean all
#DECLARATION tags
.PHONY:			all bonus clean fclean re