#include<allegro5/allegro.h>
#include<allegro5/allegro_font.h>
#include<allegro5/allegro_ttf.h>
#include<allegro5/allegro_native_dialog.h>
#include<allegro5/allegro_primitives.h>
#include<allegro5/allegro_image.h>
const int WIDTH=640;
const int HEIGHT=480;
const int NUM_BULLETS=5;
const int NUM_COMETS=1;
enum KEYS{UP,DOWN,LEFT,RIGHT,SPACE};
enum IDS{PLAYER,BULLET,ENEMY};
int score=0;
struct SpaceShip{
	int ID;
	int x;
	int y;
	int lives;
	int speed;
	int boundx;
	int boundy;
	int sw;
	int sh;
	int score;
	ALLEGRO_BITMAP *img;
};
struct Bullet{
	int ID;
	int x;
	int y;
	bool live;
	int speed;
	ALLEGRO_BITMAP *img;
};
struct Comet{
	int ID;
	int x;
	int y;
	bool live;
	int speed;
	int boundx;
	int boundy;
	ALLEGRO_BITMAP *img;
};
bool InitShip(SpaceShip&);
void DrawShip(SpaceShip&);
void MoveShipLeft(SpaceShip&);
void MoveShipUp(SpaceShip&);
void MoveShipDown(SpaceShip&);
void MoveShipRight(SpaceShip&);
void InitBullet(Bullet[],int);
void DrawBullet(Bullet[],int);
void FireBullet(Bullet[],int,SpaceShip&);
void UpdateBullet(Bullet bullet[], int size);
bool InitComet(Comet[],int);
void DrawComet(Comet[],int);
void StartComet(Comet[],int);
void UpdateComet(Comet[],int);
void CollideBullet(Bullet bullet[], int bSize, Comet comets[], int cSize);
void CollideComet(Comet comets[], int cSize, SpaceShip &ship);
int main(int argc,char** argv){
	Bullet bullets[5];
	Comet comets[NUM_COMETS];
	SpaceShip ship;
	int FPS=60;
	int width=WIDTH;
	int height=HEIGHT;
	bool done=false;
	int k_pos_x=width/2;
	int k_pos_y=height/2;
	int m_pos_x=width/2;
	int m_pos_y=height/2;
	bool keys[4]={false,false,false,false};
	bool redraw=true;
	ALLEGRO_DISPLAY *display=NULL;
	ALLEGRO_EVENT_QUEUE *event_queue=NULL;
	ALLEGRO_TIMER *timer=NULL;
	if(!al_init())
		return -1;
	display=al_create_display(width,height);
	if(!display){
		return -1;
	}
	if(!al_init_image_addon()) {
		al_show_native_message_box(display, "Error", "Error", "Failed to initialize al_init_image_addon!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}
	al_init_primitives_addon();
	al_install_keyboard();
	al_install_mouse();
	InitBullet(bullets, NUM_BULLETS);
	InitComet(comets, NUM_COMETS);
	al_hide_mouse_cursor(display);
	al_init_font_addon();
	al_init_ttf_addon();
	ALLEGRO_FONT *font24=al_load_font("../res/a.ttf",24,0);
	ALLEGRO_FONT *font36=al_load_font("../res/a.ttf",36,0);
	ALLEGRO_FONT *font18=al_load_font("../res/a.ttf",18,0);
	timer=al_create_timer(1.0/FPS);
	event_queue=al_create_event_queue();
	al_register_event_source(event_queue,al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_mouse_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_start_timer(timer);
	InitShip(ship);
	StartComet(comets, NUM_COMETS);
	do{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);
		if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch(ev.keyboard.keycode)
			{
				case ALLEGRO_KEY_UP:
					keys[UP] = true;
					break;
				case ALLEGRO_KEY_DOWN:
					keys[DOWN] = true;
					break;
				case ALLEGRO_KEY_RIGHT:
					keys[RIGHT] = true;
					break;
				case ALLEGRO_KEY_LEFT:
					keys[LEFT] = true;
					break;
				case ALLEGRO_KEY_SPACE:
					keys[SPACE] = true;
					FireBullet(bullets, NUM_BULLETS, ship);
					break;
			}
		}
		else if(ev.type == ALLEGRO_EVENT_KEY_UP)
		{
			switch(ev.keyboard.keycode)
			{
				case ALLEGRO_KEY_UP:
					keys[UP] = false;
					break;
				case ALLEGRO_KEY_DOWN:
					keys[DOWN] = false;
					break;
				case ALLEGRO_KEY_RIGHT:
					keys[RIGHT] = false;
					break;
				case ALLEGRO_KEY_LEFT:
					keys[LEFT] = false;
					break;
				case ALLEGRO_KEY_ESCAPE:
					done = true;
					break;
				case ALLEGRO_KEY_SPACE:
					keys[SPACE] = false;
					break;

			}
		}else if(ev.type==ALLEGRO_EVENT_DISPLAY_CLOSE){
			done=true;
		}else if(ev.type==ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
		}else if(ev.type==ALLEGRO_EVENT_MOUSE_AXES){
			m_pos_x=ev.mouse.x;
			m_pos_y=ev.mouse.y;
		}else if(ev.type==ALLEGRO_EVENT_TIMER){
			redraw = true;
			if(keys[UP])
				MoveShipUp(ship);
			if(keys[DOWN])
				MoveShipDown(ship);
			if(keys[LEFT])
				MoveShipLeft(ship);
			if(keys[RIGHT])
				MoveShipRight(ship);
			UpdateBullet(bullets, NUM_BULLETS);
			StartComet(comets, NUM_COMETS);
			UpdateComet(comets, NUM_COMETS);
			CollideBullet(bullets, NUM_BULLETS, comets, NUM_COMETS);
			CollideComet(comets, NUM_COMETS, ship);
		}
		if(redraw && al_is_event_queue_empty(event_queue)){
			DrawShip(ship);
			DrawBullet(bullets, NUM_BULLETS);
			DrawComet(comets, NUM_COMETS);
			redraw = false;
			al_draw_filled_circle(m_pos_x,m_pos_y,5,al_map_rgb(128,128,128));
			al_draw_filled_rectangle(0,0,WIDTH,64,al_map_rgb(32,32,32));
			al_draw_filled_rectangle(0,48,WIDTH,64,al_map_rgb(64,64,64));
			//al_draw_textf(font24,al_map_rgb(128,128,128),22,22,ALLEGRO_ALIGN_LEFT,"k[%i,%i],m[%i,%i],s[%i]",ship.x,ship.y,m_pos_x,m_pos_y,score);
			//al_draw_textf(font24,al_map_rgb(196,196,196),20,20,ALLEGRO_ALIGN_LEFT,"k[%i,%i],m[%i,%i],s[%i]",ship.x,ship.y,m_pos_x,m_pos_y,score);
			al_draw_textf(font24,al_map_rgb(196,196,196),20,20,ALLEGRO_ALIGN_LEFT,"SCORE: %i",score);
			al_flip_display();
			al_clear_to_color(al_map_rgb(0,0,0));
		}
	}while(!done);
	al_destroy_timer(timer);
	al_destroy_font(font18);
	al_destroy_font(font24);
	al_destroy_font(font36);
	al_destroy_event_queue(event_queue);
	al_destroy_display(display);
	return 0;
}
bool InitShip(SpaceShip &ship){
	ship.x=20;
	ship.y=HEIGHT/2;
	ship.ID=PLAYER;
	ship.lives=3;
	ship.speed=7;
	ship.sw=64;
	ship.sh=64;
	ship.boundx=32;
	ship.boundy=32;
	ship.score=0;
	ship.img=al_load_bitmap("../res/a.png");
	return true;
}
void DrawShip(SpaceShip &ship){
	al_draw_scaled_bitmap(
		ship.img,
		0,
		0,
		al_get_bitmap_width(ship.img),
		al_get_bitmap_height(ship.img),
		ship.x-ship.sw/2,
		ship.y-ship.sh/2,
		ship.sw,
		ship.sh,
		0
	);
}

void MoveShipLeft(SpaceShip &ship){
	ship.x-=ship.speed;
	if(ship.x<0)
		ship.x=0;
}
void MoveShipUp(SpaceShip &ship){
	ship.y-=ship.speed;
	if(ship.y<64)
		ship.y=64;
}
void MoveShipDown(SpaceShip&ship){
	ship.y+=ship.speed;
	if(ship.y>HEIGHT)
		ship.y=HEIGHT;

}
void MoveShipRight(SpaceShip &ship){
	ship.x+=ship.speed;
	if(ship.x>WIDTH)
		ship.x=WIDTH;
}
void InitBullet(Bullet bullet[], int size){
	for(int i=0;i<size;i++){
		bullet[i].ID=BULLET;
		bullet[i].speed=10;
		bullet[i].live=false;
		bullet[i].img=al_load_bitmap("../res/b.png");
	}
}
void DrawBullet(Bullet bullet[], int size){
	for(int i=0;i<size;i++){
		if(bullet[i].live)
			//al_draw_filled_circle(bullet[i].x,bullet[i].y,2,al_map_rgb(255,255,255));
		al_draw_scaled_bitmap(
			bullet[i].img,
			0,
			0,
			al_get_bitmap_width(bullet[i].img),
			al_get_bitmap_height(bullet[i].img),
			bullet[i].x-8,
			bullet[i].y-8,
			24,
			16,
			0
		);

	}
}
void FireBullet(Bullet bullet[], int size, SpaceShip &ship){
	for(int i=0;i<size;i++){
		if(!bullet[i].live){
			bullet[i].x=ship.x+17;
			bullet[i].y=ship.y;
			bullet[i].live=true;
			break;
		}
	}
}
void UpdateBullet(Bullet bullet[], int size){
	for(int i=0;i<size;i++){
		if(bullet[i].live){
			bullet[i].x+=bullet[i].speed;
			if(bullet[i].x>WIDTH)
				bullet[i].live=false;
		}
	}
}
bool InitComet(Comet comets[], int size){
	bool ret=false;
	for(int i=0;i<size;i++){
		comets[i].ID=ENEMY;
		comets[i].live=false;
		comets[i].speed=5;
		comets[i].boundx=18;
		comets[i].boundy=18;
		comets[i].img=al_load_bitmap("../res/c.png");
		ret=true;
	}
	return ret;
}
void DrawComet(Comet comets[], int size){
	for(int i=0;i<size;i++){
		if(comets[i].live){
			//al_draw_filled_circle(comets[i].x,comets[i].y,20,al_map_rgb(255,0,0));
			al_draw_scaled_bitmap(
				comets[i].img,
				0,
				0,
				al_get_bitmap_width(comets[i].img),
				al_get_bitmap_height(comets[i].img),
				comets[i].x-8,
				comets[i].y-8,
				64,
				32,
				0
			);

		}
	}
}
void StartComet(Comet comets[], int size){
	for(int i=0;i<size;i++){
		if(!comets[i].live){
			if(rand()%50==0){
				comets[i].live=true;
				comets[i].x=WIDTH;
				comets[i].y=30+rand()%(HEIGHT-128)+64;
				break;
			}
		}
	}
}
void UpdateComet(Comet comets[], int size){
	for(int i=0;i<size;i++){
		if(comets[i].live){
			comets[i].x-=comets[i].speed;
			if(comets[i].x<0)
				comets[i].live=false;
		}
	}
}
void CollideBullet(Bullet bullet[],int bSize,Comet comets[],int cSize){
	for(int i=0;i<bSize;i++){
		if(bullet[i].live){
			for(int j=0;j<cSize;j++){
				if(comets[j].live){
					if(
						bullet[i].x>(comets[j].x-comets[j].boundx)&&
						bullet[i].x<(comets[j].x+comets[j].boundx)&&
						bullet[i].y>(comets[j].y-comets[j].boundy)&&
						bullet[i].y<(comets[j].y+comets[j].boundy)
					){
						bullet[i].live=false;
						comets[j].live=false;
						score++;
					}
				}
			}
		}
	}
}
void CollideComet(Comet comets[],int cSize,SpaceShip &ship){
	for(int i=0;i<cSize;i++){
		if(comets[i].live){
			if(
				comets[i].x-comets[i].boundx<ship.x+ship.boundx&&
				comets[i].x+comets[i].boundx>ship.x-ship.boundx&&
				comets[i].y-comets[i].boundy<ship.y+ship.boundy&&
				comets[i].y+comets[i].boundy>ship.y-ship.boundy
			){
				ship.lives--;
				comets[i].live=false;
			}else if(comets[i].x<0){
				comets[i].live=false;
				ship.lives--;
			}
		}
	}
}


