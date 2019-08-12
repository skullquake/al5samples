CC=g++
SRC=./src/a.cpp
BIN=./bin/a.out
CFLAGS=\
	-Wall \
	-I./include \
	-L./lib 
$(BIN):$(SRC)
	@$(CC) \
		$(CFLAGS) \
		$(SRC) \
		-lallegro \
		-lallegro_dialog \
		-static-libstdc++ \
		-o $(BIN)
.phony:
	run \
	dist \
	clean 
run:
	@./bin/a.out
clean:
	@rm $(BIN)
