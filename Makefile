CC=g++
CFLAGS= -Wall -g
RM=rm -rf
CFORMAT=.cpp

# objetos e .cpp
C_DEPENDENCES=$(wildcard ./src/*$(CFORMAT))
OBJ_DEPENDENCES=$(subst $(CFORMAT),.o,$(subst src,obj, $(C_DEPENDENCES)))

# diretórios
C_DIR=./src/
H_DIR=./include/
MAIN_DIR=./main/
OBJ_DIR=./obj/

all: make_dir $(OBJ_DEPENDENCES)
	$(CC) $(CFLAGS) $(MAIN_DIR)server$(CFORMAT) $(OBJ_DEPENDENCES) -o server.out -I$(H_DIR)
	$(CC) $(CFLAGS) $(MAIN_DIR)serverMT$(CFORMAT) $(OBJ_DEPENDENCES) -o serverMT.out -I$(H_DIR)
	$(CC) $(CFLAGS) $(MAIN_DIR)client$(CFORMAT) $(OBJ_DEPENDENCES) -o client.out -I$(H_DIR)

$(OBJ_DIR)%.o: $(C_DIR)%$(CFORMAT)
	@$(CC) $(CFLAGS) -c $< -o $@ -I$(H_DIR)


make_dir:
	@ [ -d "./obj" ] && echo "'./obj' already exist" || mkdir obj

cleanObj:
	@ rm ./obj/*
	@ echo "objetos excluídos"

clean: cleanObj
	@ rmdir obj
	@ rm  ./*.out
	@ echo "binários excluídos"