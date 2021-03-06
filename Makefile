# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: babdelka <babdelka@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/23 16:25:47 by yait-el-          #+#    #+#              #
#    Updated: 2021/03/28 15:22:17 by babdelka         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

####################### Make Makefile  beautiful
BLACK           := $(shell tput -Txterm setaf 0)
RED             := $(shell tput -Txterm setaf 1)
GREEN           := $(shell tput -Txterm setaf 2)
YELLOW          := $(shell tput -Txterm setaf 3)
LIGHTPURPLE     := $(shell tput -Txterm setaf 4)
PURPLE          := $(shell tput -Txterm setaf 5)
BLUE            := $(shell tput -Txterm setaf 6)
WHITE           := $(shell tput -Txterm setaf 7)
RESET           := $(shell tput -Txterm setaf 9)
####################### Project Name

NAME = RT

######################Executable / Libraries

MLX  = libmlx.a
FT   = libft.a

######################DIR

LFTDIR		= library/Libft
SRCSDIR		= src
OBJSDIR		= obj
INCSDIR		:= inc
INCSDIR		+= $(LFTDIR)
MLXDIR		= library/mlx
CHILDDIR    := start
CHILDDIR    += parse
CHILDDIR    += effects
CHILDDIR    += mlx
CHILDDIR    += libvect
CHILDDIR    += raytracing
CHILDDIR    += error
CHILDDIR    += library/qdbmp_1.0.0/
####################INC

INCS		:= inc/rtv1.h
INCS		+= inc/fuction.h
INCS		+= inc/struct.h
INCS		+= library/Libft/include/libft.h
INCS		+= library/mlx/mlx.h

########################SRC files

SRC			:=start/main.c
SRC			+=start/freeing.c
SRC			+=mlx/mlx_stuff.c
SRC			+=mlx/mlx_stuffnext.c
SRC			+=mlx/mlx_stuffnext_help.c
SRC			+=mlx/mlx_stuffnext_helpone.c
SRC         +=parse/light_parse.c
SRC         +=parse/tools_parse2.c
SRC         +=parse/tools_parse3.c
SRC			+=parse/parse.c
SRC			+=parse/parse2.c
SRC			+=parse/extra.c
SRC			+=parse/objs_parse.c
SRC			+=parse/check_obj.c
SRC			+=parse/check_obj2.c
SRC			+=parse/check_obj3.c
SRC			+=parse/tools_parse.c
SRC			+=parse/list_rt.c
SRC			+=libvect/calc_vect.c
SRC			+=libvect/vector_calculation.c
SRC			+=libvect/vector_calculation2.c
SRC			+=libvect/perlin_noise.c
SRC			+=libvect/hash_set.c
SRC			+=error/parse_error.c
SRC			+=raytracing/raytracing.c
SRC			+=raytracing/rotation.c
SRC			+=raytracing/intersection.c
SRC			+=raytracing/intersectiontri.c
SRC			+=raytracing/get_pxl.c
SRC			+=raytracing/colors.c
SRC			+=effects/saving.c
SRC			+=effects/color_palette.c
SRC			+=effects/antialiasing.c
SRC			+=effects/blur.c
SRC			+=effects/reloading.c
SRC			+=effects/stereoscopy.c
SRC			+=effects/sepia_grey.c
SRC			+=raytracing/reflectionandrefraction.c
SRC			+=raytracing/texture.c
SRC			+=raytracing/extra.c
SRC			+=raytracing/sliceandneg.c

#################### Libraries
LIBS		:= -L$(MLXDIR) -lmlx
LIBS		+= -framework OpenGL
LIBS		+= -framework AppKit
LIBS		+= -lz
LIBS		+= -L$(LFTDIR) -lft

################### 3ya9a li makine lache Oops!... I Did It Again
LFT			= $(LFTDIR)/$(FT)
MLXX		= $(MLXDIR)/$(MLX)
D_SRCS		= $(addsuffix /, $(SRCSDIR))
D_OBJS		= $(addsuffix /, $(OBJSDIR))
C_OBJS		= $(addprefix $(D_OBJS),  $(SRC:.c=.o))
C_INCS		= $(foreach include, $(INCSDIR), -I$(include))
C_CHILDDIR	= $(foreach dir, $(CHILDDIR),$(D_OBJS)$(dir))
################# Compilation flags
CC    		= gcc
RM    		= rm -rf
CFLAGS		= $(C_INCS) #-Wall -Werror -Wextra

#----------------->>>>>>>>>>>>>>>>START<<<<<<<<<<<<<-------------------#
$(D_OBJS)%.o: $(D_SRCS)%.c $(INCS)
	@echo "$(PURPLE)**********>>>Compiling : $(RESET) $(LIGHTPURPLE)" $<
	@$(CC) $(CFLAGS) -c $< -o $@

all:$(OBJSDIR) $(C_CHILDDIR) $(NAME)

########## for D-bug
print-%  : ; @echo $* = $($*)
############################

$(NAME):$(LFT) $(MLXX) $(C_OBJS)
	@echo "$(RED)\n***********>>>Building : $(RESET)$(NAME) $(YELLOW)...\n$(RESET)"
	@$(CC) $(CFLAGS) -o $(NAME) $(C_OBJS) $(LIBS)

#########  make libft
$(LFT):
	@make -sC $(LFTDIR)
######## create obj dir
$(OBJSDIR):
	@mkdir -p $(OBJSDIR)
####### create sub folder
$(C_CHILDDIR):
	@mkdir -p $(C_CHILDDIR)
####### make mlix
$(MLXX):
	make -sC $(MLXDIR)
clean:
	@make -sC $(LFTDIR) clean
	@echo "$(GREEN)**********   Deleting all object from $(NAME) **********\n$(RESET)"
	@$(RM) $(C_OBJS)

fclean: clean
	@make -sC $(LFTDIR) fclean
	@echo "$(GREEN)**********   Deleting $(NAME) **********\n$(RESET)"
	@$(RM) $(NAME)
	@$(RM) $(OBJSDIR)

re: fclean all