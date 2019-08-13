#include<stdio.h>
#include<allegro5/allegro.h>
#include<allegro5/allegro_font.h>
#include<allegro5/allegro_ttf.h>
#include<allegro5/allegro_native_dialog.h>
#include<allegro5/allegro_primitives.h>
#include<allegro5/allegro_image.h>
const float FPS=30;
const int SCREEN_W=640;
const int SCREEN_H=480;
const int BOUNCER_SIZE=32;
int main(int argc, char **argv){
	ALLEGRO_DISPLAY *dspl=NULL;
	ALLEGRO_EVENT_QUEUE *eq=NULL;
	ALLEGRO_TIMER *tmr= NULL;
	ALLEGRO_BITMAP *bouncer = NULL;
	int sidx=0;
	float sx=0;
	float sy=0;
	float sw=64;
	float sh=64;
	float dx=0;
	float dy=0;
	int flags=0;
	bool redraw = true;
	if(!al_init()) {
		fprintf(stderr, "failed to initialize allegro!\n");
		return -1;
	}
	if(!al_init_image_addon()) {
		al_show_native_message_box(dspl, "Error", "Error", "Failed to initialize al_init_image_addon!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}
	ALLEGRO_BITMAP *img;
	img=al_load_bitmap("../res/bmb320x320_5x5.png");
	tmr=al_create_timer(1.0 / FPS);
	if(!tmr) {
		fprintf(stderr, "failed to create timer!\n");
		return -1;
	}
	dspl=al_create_display(SCREEN_W, SCREEN_H);
	if(!dspl){
		fprintf(stderr,"failed to create display!\n");
		al_destroy_timer(tmr);
		return -1;
	}
	al_clear_to_color(al_map_rgb(255, 0, 255));
	al_set_target_bitmap(al_get_backbuffer(dspl));
	eq=al_create_event_queue();
	al_install_keyboard();
	al_register_event_source(eq,al_get_keyboard_event_source());
	if(!eq){
		fprintf(stderr, "failed to create event_queue!\n");
		al_destroy_display(dspl);
		al_destroy_timer(tmr);
		return -1;
	}
	al_register_event_source(eq,al_get_display_event_source(dspl));
	al_register_event_source(eq,al_get_timer_event_source(tmr));
	al_clear_to_color(al_map_rgb(0,0,0));
	al_flip_display();
	al_start_timer(tmr);
	bool done=false;
	while(!done){
		ALLEGRO_EVENT ev;
		al_wait_for_event(eq,&ev);
		if(ev.type==ALLEGRO_EVENT_TIMER) {
			sx+=sw;
			if((int(sx))==al_get_bitmap_width(img)){
				sy+=sh;
				sy=(int(sy))%al_get_bitmap_height(img);
			}
			sx=(int(sx))%al_get_bitmap_width(img);
			if(sx==0&&sy==0){
				dx=rand()%al_get_bitmap_width(img)-sw;
				dy=rand()%al_get_bitmap_width(img)-sh;
			}
			redraw = true;
		}
		else if(ev.type==ALLEGRO_EVENT_DISPLAY_CLOSE) {
			break;
		}
		else if(ev.type == ALLEGRO_EVENT_KEY_UP)
		{
			switch(ev.keyboard.keycode){
				case ALLEGRO_KEY_ESCAPE:
					done = true;
					break;
				default:
					break;
			}
		}
		if(redraw&&al_is_event_queue_empty(eq)){
			redraw = false;
			al_clear_to_color(al_map_rgb(0,0,0));
			//al_draw_bitmap(img,SCREEN_W/2-160/2,SCREEN_H/2-160/2,0);
			al_draw_bitmap_region(img,sx,sy,sw,sh,dx,dy,flags);
			al_flip_display();
		}
	}
	al_destroy_bitmap(img);
	al_destroy_timer(tmr);
	al_destroy_display(dspl);
	al_destroy_event_queue(eq);
	return 0;
}


