#include"overall.h"
#include"lawn.h"
#include"game.h"
#include"zombie.h"
#include<iostream>
using namespace std;
//≥ı ºªØ
Zombie::Zombie(){
	if_slowed = 0;
	slowing = 0;
	garlicing = 0;
	can_jump = 0;
}
//Ω© ¨––∂Ø
void Zombie::move( Game& game ){
	speed_cooling++;
	if ( speed_cooling == speed ){
		speed_cooling = 0;
		if ( x == 0 ) game.game_over();
		else x--;
	}
}
//Ω© ¨π•ª˜
void Zombie::hit( Game& game ){
	Grid* now = &game.lawn.grid_list[x][y];
	if ( now->pumpkin != NULL ) now->plant_minus( now->pumpkin , attack );
	else{
		now->plant_minus( now->plant , attack );
		if ( now->plant != NULL && now->plant->type == Plant_type::garlic ){
			color = light_green_back;
			garlicing = 17;
		}
	}
}
//±˘∂≥◊¥Ã¨
void Zombie::slow( Game& game ){
	if ( slowing ){
		Grid* now = &game.lawn.grid_list[x][y];
		slowing--;
		if ( slowing == 100 ){
			if ( if_slowed == 1 ) return;
			if_slowed = 1;
			speed *= 2;
			speed_cooling *= 2;
			attack /= 2;
			if ( type == dancing ){
				( (Dancing*) this )->make_time *= 2;
				( (Dancing*) this )->make_cooling *= 2;
			}
			color = dark_cyan_back;
			now->in_refresh = 1;
		}
		if ( slowing == 0 ){
			if_slowed = 0;
			speed /= 2;
			speed_cooling /= 2;
			attack *= 2;
			if ( type == dancing ){
				( (Dancing*) this )->make_time /= 2;
				( (Dancing*) this )->make_cooling /= 2;
			}
			color = origin_color;
			now->in_refresh = 1;
		}
	}
}
//±ª∂æ◊¥Ã¨
void Zombie::garlic( Game& game ){
	if ( garlicing ){
		garlicing--;
		if ( garlicing == 10 ){
			if ( y == 0 ) y++;
			else if ( y == whole_width - 1 ) y--;
			else{
				int cnt = rand() % 2;
				if ( cnt ) y++;
				else y--;
			}
		}
		if ( garlicing == 2 ){
			color = origin_color;
			game.lawn.grid_list[x][y].in_refresh = 1;
		}
	}
}
//≈–∂œΩ© ¨ «∑Òƒ‹π•ª˜÷≤ŒÔ
bool Zombie::zombie_can_attack( Game& game ){
	Grid* now = &game.lawn.grid_list[x][y];
	if ( now->pumpkin != NULL ) return true;
	if ( now->plant != NULL && now->plant->type != spikeweed ) return true;
	return false;
}
void Zombie::action( Game& game ){}
Ordinary::Ordinary():Zombie(){
	name = "∆’Õ®Ω© ¨";
	type = ordinary;
	attack = 10;
	blood = defence = 200;
	speed_cooling = 0;
	speed = 47;
	score = 5;
	origin_color = color = grey_back;
}
Flag::Flag():Zombie(){
	name = "“°∆ÏΩ© ¨";
	type = flag;
	attack = 10;
	blood = defence = 200;
	speed_cooling = 0;
	speed = 37;
	score = 5;
	origin_color = color = dark_red_back;
}
Conehead::Conehead():Zombie(){
	name = "¬∑’œΩ© ¨";
	type = conehead;
	attack = 10;
	blood = defence = 570;
	speed_cooling = 0;
	speed = 47;
	score = 10;
	origin_color = color = dark_yellow_back;
}
Pole_vaulting::Pole_vaulting():Zombie(){
	name = "≥≈∏ÀΩ© ¨";
	type = pole_vaulting;
	attack = 10;
	blood = defence = 500;
	speed_cooling = 0;
	speed = 25;
	score = 15;
	origin_color = color = dark_red_back;

	name2 = "Œﬁ∏ÀΩ© ¨";
	speed2 = 45;
	can_jump = 1;
}
Bucket::Bucket():Zombie(){
	name = "Ã˙Õ∞Ω© ¨";
	type = bucket;
	attack = 10;
	blood = defence = 1370;
	speed_cooling = 0;
	speed = 47;
	score = 20;
	origin_color = color = selected;
}
Newspaper::Newspaper():Zombie(){
	name = "∂¡±®Ω© ¨";
	type = newspaper;
	attack = 10;
	blood = defence = 420;
	speed_cooling = 0;
	speed = 47;
	score = 15;
	origin_color = color = grey_back;

	name2 = "Œﬁ±®Ω© ¨";
	speed2 = 18;
	angry = 0;
}
Dancing::Dancing():Zombie(){
	name = "ŒËÕıΩ© ¨";
	type = dancing;
	attack = 10;
	blood = defence = 500;
	speed_cooling = 0;
	speed = 12;
	score = 25;
	origin_color = color = light_cyan_back;

	first_time = 25;
	flash_time = 11;
	state = 0;
	make_cooling = 0;
	make_time = 25;
	flag = 0;
	left = right = top = bottom = NULL;
}
Back_up::Back_up():Zombie(){
	name = "∞ÈŒËΩ© ¨";
	type = back_up;
	attack = 10;
	blood = defence = 200;
	speed_cooling = 0;
	speed = 55;
	score = 5;
	origin_color = color = light_purple_back;
}
Jack_in_the_box::Jack_in_the_box():Zombie(){
	name = "–°≥ÛΩ© ¨";
	type = jack_in_the_box;
	attack = 10;
	blood = defence = 367;
	speed_cooling = 0;
	speed = 33;
	score = 15;
	origin_color = color = selected;

	int cnt = rand() % 20;
	if ( cnt == 0 ) life_time = 45 + rand() % 34;
	else life_time = 133 + rand() % 98;
	bomb_time = 11;
}
Catapult::Catapult(){
	name = "Õ∂ Ø≥µΩ© ¨";
	type = catapult;
	attack = 20;
	blood = defence = 850;
	speed_cooling = 0;
	speed = 25;
	score = 25;
	origin_color = color = light_blue_back;

	ball_num = 20;
	throw_time = 40;
	throw_cooling = 0;
}
//∆’Õ®Ω© ¨––∂Ø
void Ordinary::action( Game& game ){
	if ( defence < 0 ) return;
	if ( garlicing ) garlic( game );
	else {
		if ( zombie_can_attack( game ) ) hit( game );
		else move( game );
		slow( game );
	}
}
//“°∆ÏΩ© ¨––∂Ø
void Flag::action( Game& game ){
	if ( defence < 0 ) return;
	if ( garlicing ) garlic( game );
	else {
		if ( zombie_can_attack( game ) ) hit( game );
		else move( game );
		slow( game );
	}
}
//¬∑’œΩ© ¨––∂Ø
void Conehead::action( Game& game ){
	if ( defence < 0 ) return;
	if ( garlicing ) garlic( game );
	else {
		if ( zombie_can_attack( game ) ) hit( game );
		else move( game );
		slow( game );
	}
}
////≥≈∏ÀΩ© ¨––∂Ø
void Pole_vaulting::action( Game& game ){
	if ( defence < 0 ) return;
	if ( can_jump == 0 ){
		if ( garlicing ) garlic( game );
		else {
			if ( zombie_can_attack( game ) ) hit( game );
			else move( game );
			slow( game );
		}
	}
	else{
		if ( zombie_can_attack( game ) ) jump( game );
		else{
			if ( garlicing ) garlic( game );
			else {
				if ( zombie_can_attack( game ) ) hit( game );
				else move( game );
				slow( game );
			}
		}
	}
}
void Pole_vaulting::jump( Game& game ){
	can_jump = 0;
	name = name2;
	speed = speed2;
	speed_cooling = 0;
	if ( game.lawn.grid_list[x][y].plant == NULL ||
		game.lawn.grid_list[x][y].plant->can_be_jump() )
		x--;
}
//Ã˙Õ∞Ω© ¨––∂Ø
void Bucket::action( Game& game ){
	if ( defence < 0 ) return;
	if ( garlicing ) garlic( game );
	else {
		if ( zombie_can_attack( game ) ) hit( game );
		else move( game );
		slow( game );
	}
}
//∂¡±®Ω© ¨––∂Ø
void Newspaper::action( Game& game ){
	if ( defence < 0 ) return;
	if ( angry == 0 && defence <= 270 ){
		speed = speed2;
		speed_cooling = 0;
		name = name2;
		color = origin_color = light_red_back;
		if ( slowing ){
			speed *= 2;
			speed_cooling *= 2;
			attack /= 2;
			color = origin_color = dark_cyan_back;
		}
		game.lawn.grid_list[x][y].in_refresh = 1;
		angry = 1;
	}
	if ( garlicing ) garlic( game );
	else {
		if ( zombie_can_attack( game ) ) hit( game );
		else move( game );
		slow( game );
	}
}
//ŒËÕıΩ© ¨––∂Ø
void Dancing::action( Game& game ){
	if ( defence < 0 ) return;
	flag = can_move( game );
	if ( left != NULL ) left->action( game );
	if ( right != NULL ) right->action( game );
	if ( top != NULL ) top->action( game );
	if ( bottom != NULL ) bottom->action( game );
	if ( garlicing ) garlic( game );
	else slow( game );
	if ( zombie_can_attack( game ) && !garlicing )hit( game );
	else if ( flag ) move( game );
	/*set_cursor( 0 , 4 );
	cout << speed_cooling << " " << speed << endl;
	if ( left != NULL )
		cout << left->speed_cooling << " " << left->speed << endl;
	if ( right != NULL )
		cout << right->speed_cooling << " " << right->speed << endl;
	if ( top != NULL )
		cout << top->speed_cooling << " " << top->speed << endl;
	if ( bottom != NULL )
		cout << bottom->speed_cooling << " " << bottom->speed << endl;*/
	if ( first_time ){
		first_time--;
		if ( first_time == 0 ){
			Grid* now = &game.lawn.grid_list[x][y];
			now->flashing = flash_time;
			speed = 55;
			if ( slowing ) speed = 110;
			add_back_up( game );
		}
	}
	else if ( check( game ) ){
		if ( make_cooling == 0 ) make_cooling = make_time;
		make_cooling--;
		if ( make_cooling == 0 ){
			Grid* now = &game.lawn.grid_list[x][y];
			now->flashing = flash_time;
			add_back_up( game );
		}
	}
}
int Dancing::max_slowing(){
	int now = slowing;
	if ( left != NULL ) now = max( now , left->slowing );
	if ( right != NULL ) now = max( now , right->slowing );
	if ( top != NULL ) now = max( now , top->slowing );
	if ( bottom != NULL ) now = max( now , bottom->slowing );
	return now;
}
bool Dancing::can_move( Game& game ){
	if ( left != NULL && ( left->zombie_can_attack( game ) || left->garlicing ) ) return false;
	if ( right != NULL && ( right->zombie_can_attack( game ) || right->garlicing ) ) return false;
	if ( top != NULL && ( top->zombie_can_attack( game ) || top->garlicing ) ) return false;
	if ( bottom != NULL && ( bottom->zombie_can_attack( game ) || bottom->garlicing ) ) return false;
	if ( zombie_can_attack( game ) || garlicing ) return false;
	return true;
}
void Dancing::add_back_up( Game& game ){
	Back_up* now = NULL;
	if ( x > 0 && left == NULL ){
		now = new Back_up();
		now->dancing = this;
		now->direction = 0;
		now->x = x - 1;
		now->y = y;
		left = now;
		game.lawn.grid_list[x - 1][y].zombie_list.push_back( now );
		game.lawn.grid_list[x - 1][y].in_refresh = 1;
		game.lawn.grid_list[x - 1][y].flashing = flash_time;
	}
	if ( x < whole_length - 1 && right == NULL ){
		now = new Back_up();
		now->dancing = this;
		now->direction = 1;
		now->x = x + 1;
		now->y = y;
		right = now;
		game.lawn.grid_list[x + 1][y].zombie_list.push_back( now );
		game.lawn.grid_list[x + 1][y].in_refresh = 1;
		game.lawn.grid_list[x + 1][y].flashing = flash_time;
	}
	if ( y > 0 && top == NULL ){
		now = new Back_up();
		now->dancing = this;
		now->direction = 2;
		now->x = x;
		now->y = y - 1;
		top = now;
		game.lawn.grid_list[x][y - 1].zombie_list.push_back( now );
		game.lawn.grid_list[x][y - 1].in_refresh = 1;
		game.lawn.grid_list[x][y - 1].flashing = flash_time;
	}
	if ( y < whole_width - 1 && bottom == NULL ){
		now = new Back_up();
		now->dancing = this;
		now->direction = 3;
		now->x = x;
		now->y = y + 1;
		bottom = now;
		game.lawn.grid_list[x][y + 1].zombie_list.push_back( now );
		game.lawn.grid_list[x][y + 1].in_refresh = 1;
		game.lawn.grid_list[x][y + 1].flashing = flash_time;
	}
}
bool Dancing::check( Game& game ){
	if ( x > 0 && left == NULL ) return true;
	if ( x < whole_length - 1 && right == NULL ) return true;
	if ( y > 0 && top == NULL ) return true;
	if ( y < whole_width - 1 && bottom == NULL ) return true;
	return false;
}
//∞ÈŒËΩ© ¨––∂Ø
void Back_up::action( Game& game ){
	if ( defence < 0 ) return;
	speed = dancing->speed;
	speed_cooling = dancing->speed_cooling;
	//	slowing = dancing->slowing;
	if ( garlicing ) garlic( game );
	else slow( game );
	if ( dancing->flag )move( game );//÷ª”–ŒËÕıƒ‹“∆∂Ø≤≈ƒ‹––∂Ø
	else if ( zombie_can_attack( game ) && !garlicing ) hit( game );
}
//–°≥ÛΩ© ¨––∂Ø
void Jack_in_the_box::action( Game& game ){
	if ( defence < 0 ) return;
	if ( garlicing ) garlic( game );
	else {
		move( game );
		slow( game );
	}
	life_time--;
	if ( life_time != 0 ) return;
	game.lawn.grid_list[x][y].zombie_minus( this , defence , game );
	int row_up = max( y - 1 , 0 );
	int row_down = min( y + 1 , whole_width - 1 );
	int col_left = max( x - 1 , 0 );
	int col_right = min( x + 1 , whole_length - 1 );
	for ( int i = col_left; i <= col_right; i++ ){
		for ( int j = row_up; j <= row_down; j++ ){
			game.lawn.grid_list[i][j].bombing = bomb_time;
			Grid* now = &game.lawn.grid_list[i][j];
			if ( now->plant != NULL )
				now->plant_minus( now->plant , now->plant->defence );
			if ( now->pumpkin != NULL )
				now->plant_minus( now->pumpkin , now->pumpkin->defence );
		}
	}
}
//Õ∂ Ø≥µΩ© ¨––∂Ø
void Catapult::action( Game& game ){
	if ( defence < 0 ) return;
		Grid* cnt = &game.lawn.grid_list[x][y];
	if ( cnt->plant!=NULL||cnt->pumpkin!=NULL ){
		if ( cnt->plant != NULL ){
			if ( cnt->plant->type == spikeweed && cnt->pumpkin == NULL ){
				cnt->zombie_minus( this , defence , game );
				cnt->bombing = 11;
			}
			cnt->plant_minus( cnt->plant , cnt->plant->defence );
		}
		if ( cnt->pumpkin != NULL )
			cnt->plant_minus( cnt->pumpkin , cnt->pumpkin->defence );
	}
	int now = can_attack( game );
	if ( now != -1 && ball_num ){
		if ( throw_cooling < throw_time ) throw_cooling++;
		if ( throw_cooling == throw_time ){
			throw_cooling = 0;
			ball_num--;
			Grid* cnt = &game.lawn.grid_list[now][y];
			if ( cnt->plant != NULL ) cnt->plant_minus( cnt->plant , attack );
			else cnt->plant_minus( cnt->pumpkin , attack );
		}
	}
	else{
		speed_cooling++;
		if ( speed_cooling == speed ){
			speed_cooling = 0;
			if ( x == 0 ) game.game_over();
			else x--;
		}
	}
	slow( game );
}
int Catapult::can_attack( Game& game ){
	for ( int i = 0; i <= x; i++ ){
		Grid* cnt = &game.lawn.grid_list[i][y];
		if ( cnt->plant != NULL || cnt->pumpkin != NULL ) return i;
	}
	return -1;
}