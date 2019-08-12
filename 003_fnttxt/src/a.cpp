#include<allegro5\allegro.h>
#include<allegro5\allegro_font.h>
#include<allegro5\allegro_ttf.h>
#include<allegro5\allegro_native_dialog.h>
int main(int argc,char** argv){
	ALLEGRO_DISPLAY *display=NULL;
	//todo: manual
	if(!al_init()){
		al_show_native_message_box(NULL,NULL,NULL,"failed to initialize allegro!",NULL,NULL);
		return -1;
	}
	display=al_create_display(640,480);
	if(!display){
		al_show_native_message_box(NULL,NULL,NULL,"failed to initialize display!",NULL,NULL);
		return -1;
	}
	al_init_font_addon();
	al_init_ttf_addon();
	ALLEGRO_FONT *font24=al_load_font("./res/a.ttf",24,0);
	ALLEGRO_FONT *font36=al_load_font("./res/a.ttf",36,0);
	ALLEGRO_FONT *font18=al_load_font("./res/a.ttf",18,0);
	int screen_w=al_get_display_width(display);
	int screen_h=al_get_display_height(display);
	al_clear_to_color(al_map_rgb(255,0,0));
	al_draw_textf(font18,al_map_rgb(255,255,255),screen_w/2,400, ALLEGRO_ALIGN_CENTRE,"TEXT with variable output (textf): Screen width and height = %i / %i" ,screen_w,screen_h);
	al_flip_display();
	al_rest(5.0);
	al_destroy_font(font18);
	al_destroy_font(font24);
	al_destroy_font(font36);
	al_destroy_display(display);
	return 0;
}
