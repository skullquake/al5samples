CC=g++
SRC=./src/a.cpp
BIN=./bin/a.out
CFLAGS=\
	-Wall \
	-I./include \
	-L./lib \
	`pkg-config --cflags allegro_acodec-5 allegro_audio-5 allegro_color-5 allegro_dialog-5 allegro_font-5 allegro_image-5 allegro_main-5 allegro_memfile-5 allegro_physfs-5 allegro_primitives-5 allegro_ttf-5 allegro_video-5 allegro-5`
LIBS=`pkg-config --libs allegro_acodec-5 allegro_audio-5 allegro_color-5 allegro_dialog-5 allegro_font-5 allegro_image-5 allegro_main-5 allegro_memfile-5 allegro_physfs-5 allegro_primitives-5 allegro_ttf-5 allegro_video-5 allegro-5`

$(BIN):$(SRC)
	@$(CC) \
		$(CFLAGS) \
		$(SRC) \
		$(LIBS) \
		-o $(BIN)
.phony:
	run \
	clean
run:
	@./bin/a.out
clean:
	@rm $(BIN)
