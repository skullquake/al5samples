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
		-lallegro_font.dll\
		-lallegro_ttf.dll\
		-lfreetype.dll\
		-o $(BIN)
#		-lallegro_primitives.dll
.phony:
	run \
	clean
run:
	@./bin/a.out
clean:
	@rm $(BIN)
