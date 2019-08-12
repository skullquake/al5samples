#include<allegro5\allegro.h>
#include<allegro5\allegro_font.h>
#include<allegro5\allegro_ttf.h>
#include<allegro5\allegro_native_dialog.h>
#include<allegro5\allegro_primitives.h>
int main(int argc,char** argv){
	int width=640;
	int height=480;
	bool done=false;
	int pos_x=width/2;
	int pos_y=height/2;
	ALLEGRO_DISPLAY *display=NULL;
	ALLEGRO_EVENT_QUEUE *event_queue=NULL;
	if(!al_init())
		return -1;
	display=al_create_display(width,height);
	if(!display)
		return -1;
	al_init_primitives_addon();
	al_install_keyboard();
	al_install_mouse();
	al_hide_mouse_cursor(display);
	al_init_font_addon();
	al_init_ttf_addon();
	ALLEGRO_FONT *font24=al_load_font("../res/a.ttf",24,0);
	ALLEGRO_FONT *font36=al_load_font("../res/a.ttf",36,0);
	ALLEGRO_FONT *font18=al_load_font("../res/a.ttf",18,0);
	event_queue=al_create_event_queue();
	al_register_event_source(event_queue,al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_mouse_event_source());

	do{
		al_draw_filled_circle(pos_x,pos_y,10,al_map_rgb(255,255,255));
		al_draw_textf(font18,al_map_rgb(255,255,255),20,20,ALLEGRO_ALIGN_LEFT,"[%i,%i]",pos_x,pos_y);
		al_flip_display();
		al_clear_to_color(al_map_rgb(0,0,0));
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);
		if(ev.type == ALLEGRO_EVENT_KEY_UP){
			switch(ev.keyboard.keycode){
				case ALLEGRO_KEY_ESCAPE:
					done=true;
					break;
			}
		}else if(ev.type==ALLEGRO_EVENT_DISPLAY_CLOSE){
			done=true;
		}else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
		}
		else if(ev.type == ALLEGRO_EVENT_MOUSE_AXES){
			pos_x = ev.mouse.x;
			pos_y = ev.mouse.y;
		}
	}while(!done);
	al_destroy_font(font18);
	al_destroy_font(font24);
	al_destroy_font(font36);
	al_destroy_event_queue(event_queue);
	al_destroy_display(display);
	return 0;
}



