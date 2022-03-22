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
MAIN_DIR=./test/
MAIN_OUT=out/
OBJ_DIR=./obj/

all: test

test: make_dir_obj make_dir_out $(OBJ_DEPENDENCES)
	$(CC) $(CFLAGS) $(MAIN_DIR)server$(CFORMAT) $(OBJ_DEPENDENCES) -o $(MAIN_DIR)$(MAIN_OUT)server.out -I$(H_DIR)
	$(CC) $(CFLAGS) $(MAIN_DIR)serverMT$(CFORMAT) $(OBJ_DEPENDENCES) -o $(MAIN_DIR)$(MAIN_OUT)serverMT.out -I$(H_DIR)
	$(CC) $(CFLAGS) $(MAIN_DIR)client$(CFORMAT) $(OBJ_DEPENDENCES) -o $(MAIN_DIR)$(MAIN_OUT)client.out -I$(H_DIR)
	$(CC) $(CFLAGS) $(MAIN_DIR)Uclient$(CFORMAT) $(OBJ_DEPENDENCES) -o $(MAIN_DIR)$(MAIN_OUT)Uclient.out -I$(H_DIR)

objs: make_dir_obj $(OBJ_DEPENDENCES)

$(OBJ_DIR)%.o: $(C_DIR)%$(CFORMAT)
	@$(CC) $(CFLAGS) -c $< -o $@ -I$(H_DIR)

make_dir_out:
	@ [ -d "./test/out" ] && echo "'./test/out' already exist" || mkdir test/out

make_dir_obj:
	@ [ -d "./obj" ] && echo "'./obj' already exist" || mkdir obj

cleanObj:
	@ rm ./obj/*
	@ rmdir obj
	@ echo "objetos excluídos"

clean: cleanObj
	@ rm  ./test/out/*.out
	@ rmdir test/out
	@ echo "binários excluídos"