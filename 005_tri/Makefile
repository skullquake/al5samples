CC=g++
SRC=./src/a.cpp
BIN=./bin/a.out
CFLAGS=\
       -Wall \
       	-I./include \
	-L./lib
$(BIN):$(SRC)
	@$(CC) \
		$(CFLAGS)\
		$(SRC)\
		-lallegro.dll\
		-lallegro_dialog.dll\
		-lallegro_primitives.dll\
		-o $(BIN)
.phony:
	run \
	clean
run:
	@./bin/a.out
clean:
	@rm $(BIN)
