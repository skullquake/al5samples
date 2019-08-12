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
		-lallegro\
		-lallegro_dialog\
		-lallegro_primitives\
		-o $(BIN)
.phony:
	run \
	clean
run:
	@./bin/a.out
clean:
	@rm $(BIN)
