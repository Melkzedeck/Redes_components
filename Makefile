CC=g++
CFLAGS= -Wall -g
RM=rm -rf
CFORMAT=.cpp
EXE_FORMAT=.out

# objetos e .cpp
C_DEPENDENCES=$(wildcard ./src/*$(CFORMAT))
OBJ_DEPENDENCES=$(subst $(CFORMAT),.o,$(subst src,obj, $(C_DEPENDENCES)))

MAIN_CPP=$(wildcard ./test/*$(CFORMAT))
MAIN_OUT=$(subst $(CFORMAT),$(EXE_FORMAT),$(subst ./test,./test/out, $(MAIN_CPP)))

# diretórios
C_DIR=./src/
H_DIR=./include/
MAIN_DIR=./test/
OBJ_DIR=./obj/

all: test

test: objs make_dir_out $(MAIN_OUT)
	@ echo 

objs: make_dir_obj $(OBJ_DEPENDENCES)
	@ echo Objetos das classes gerados com sucesso
	@ echo

$(MAIN_DIR)out/%.out: $(MAIN_DIR)%$(CFORMAT)
	@ echo compilando $@
	@ $(CC) $(CFLAGS) $< $(OBJ_DEPENDENCES) -o $@ -I$(H_DIR)
	@ echo 

$(OBJ_DIR)%.o: $(C_DIR)%$(CFORMAT)
	@ echo Gerando $@ 
	@ $(CC) $(CFLAGS) -c $< -o $@ -I$(H_DIR)
	@ echo 

make_dir_out:
	@ echo Compilando os programas de teste
	@ [ -d "./test/out" ] && echo "'./test/out' already exist" || mkdir test/out
	@ echo

make_dir_obj:
	@ echo Gerando as dependencias do programa
	@ [ -d "./obj" ] && echo "'./obj' already exist" || mkdir obj
	@ echo

cleanObj:
	@ rm ./obj/*
	@ rmdir obj
	@ echo "objetos excluídos"

clean: cleanObj
	@ rm  ./test/out/*.out
	@ rmdir test/out
	@ echo "binários excluídos"