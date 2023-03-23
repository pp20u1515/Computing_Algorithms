CC := gcc
INC := inc/
SRC := src/
OBJ := obj/
CFLAGS := -std=c99 -g -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion -Wsign-conversion -Wvla -Iinc -lm
OBJS := $(OBJ)main.o $(OBJ)additional_funcs.o $(OBJ)io_funcs.o $(OBJ)task_funcs.o

.PHONY : clean

app.exe: obj $(OBJS)
	$(CC) -o $@ $(OBJS) -lm

obj/main.o: $(SRC)main.c $(INC)io_funcs.h $(INC)return_codes.h $(INC)additional_funcs.h $(INC)task_funcs.h
	$(CC) $(CFLAGS) -o $@ -c $<

obj/additional_funcs.o: $(SRC)additional_funcs.c $(INC)additional_funcs.h $(INC)return_codes.h $(INC)io_funcs.h
	$(CC) $(CFLAGS) -o $@ -c $<

obj/io_funcs.o: $(SRC)io_funcs.c $(INC)io_funcs.h $(INC)return_codes.h $(INC)additional_funcs.h
	$(CC) $(CFLAGS) -o $@ -c $<

obj/task_funcs.o: $(SRC)task_funcs.c $(INC)task_funcs.h $(INC)return_codes.h  $(INC)additional_funcs.h $(INC)io_funcs.h
	$(CC) $(CFLAGS) -o $@ -c $< 

obj:
	mkdir -p obj

clean :
	rm -rf .vscode
	rm *.exe 
	rm -fr obj/