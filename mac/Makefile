INC = includes
SRC = src/*.c
LIBX = minilibx
INCS = -I$(LIBX) -I$(INC)
LIBS = minilibx/libmlx.a -L$(LIBX) -lmlx
FLAGS = $(INCS) $(LIBS) -framework OpenGL -framework Appkit
NAME = ant

all:
	@clear
	@echo -n Compiling Minilibx...
	@make -s -C $(LIBX)
	@echo Done
	@echo -n Compiling ant_sim...
	@gcc $(SRC) $(FLAGS) -o $(NAME)
	@echo Done
	./ant 10000

git:
	@cd ../ && $(MAKE) git

clean:
	@rm -rf $(NAME)
	@make -s clean -C $(LIBX)
	@make -s clean -C $(LIBXLINUX)

fclean: clean

re: fclean all

bonus: all

norm:
	@clear
	@norminette $(INC) $(SRC) $(LIBALL)