#include<allegro5/allegro.h>
#include<allegro5/allegro_primitives.h>
#include<allegro5/allegro_native_dialog.h>
int main(int argc,char** argv){
	ALLEGRO_DISPLAY *display=NULL;
	if(!al_init()){
		al_show_native_message_box(NULL,NULL,NULL,"failed to initialize allegro!",NULL,NULL);
		return -1;
	}
	display=al_create_display(640,480);
	if(!display){
		al_show_native_message_box(NULL,NULL,NULL,"failed to initialize display!",NULL,NULL);
		return -1;
	}
	int screen_w=al_get_display_width(display);
	int screen_h=al_get_display_height(display);
	al_clear_to_color(al_map_rgb(255,0,0));
	al_init_primitives_addon();
	al_draw_line(100,100,screen_w-100,100,al_map_rgb(255,0,0),1);
	al_draw_line(50,200,screen_w-50,200,al_map_rgb(0,0,255),5);
	al_draw_line(0,300,screen_w,300,al_map_rgb(255,0,255),10);
	al_draw_line(50,50,50,400,al_map_rgb(0,255,0),3);
	al_draw_line(50,200,screen_w-50,400,al_map_rgb(0,0,255),5);
	al_flip_display();
	al_rest(5.0);
	al_destroy_display(display);
	return 0;
}

