#include"game.h"
#include"plant.h"
#include"overall.h"
#include"lawn.h"
#include<iostream>
using namespace std;
//初始化
Bullet::Bullet( int p , int q ){
	x = p;
	y = q;
	attack = 20;
	speed = 4;
}
Pea_bullet::Pea_bullet( int x , int y ):Bullet( x , y ){
	type = pea;
	color = dark_green;
}
Snow_bullet::Snow_bullet( int x , int y ) : Bullet( x , y ){
	type = snow;
	color = dark_cyan;
}
Fire_bullet::Fire_bullet( int x , int y ) : Bullet( x , y ){
	type = fire;
	color = dark_red;
	attack = 40;
}

Plant::Plant() {
	name = "  ?";//未出现的植物
	cost_sun = 0;
	cooling = 100;
	cool_time = 100;
	can_jump = 1;
	eating = 0;
}
void Plant::action( Game& game ){}
//判断射手攻击范围内是否有僵尸
bool Plant::shooter_can_attack( Lawn& lawn ){
	for ( int i = x; i < whole_length; i++ ){
		if ( !lawn.grid_list[i][y].zombie_list.empty() ) return 1;
	}
	return 0;
}
bool Plant::can_be_jump(){
	return can_jump;
}
void Plant::shine( Lawn& lawn ){
	if ( eating ){
		if ( eating == 4 ) color = high_light;
		else if ( eating == 1 ) color = origin_color;
		eating--;
		lawn.grid_list[x][y].in_refresh = 1;
	}
}
Peashooter::Peashooter():Plant(){
	name = "豌豆射手";
	type = peashooter;
	origin_color = color = light_green_back;
	high_light = light_green;
	blood = defence = 300;
	cost_sun = 100;
	cooling = 75;
	cool_time = 75;

	attack_cooling = 4;
	attack_time = 14;
}
Sunflower::Sunflower():Plant(){
	name = "向日葵";
	type = sunflower;
	origin_color = color = dark_yellow_back;
	high_light = dark_yellow;
	blood = defence = 300;
	cost_sun = 50;
	cooling = 75;
	cool_time = 75;

	make_sun = 25;//每次生产25阳光
	start_sun_circle = 75;//第一次生产阳光只需7.5秒
	if_start = 0;
	sun_circle = 240;//后续每隔24秒生产一个阳光
	sun_cooling = 0;
	sun_shine_time = 0;
}
Cherry_bomb::Cherry_bomb():Plant(){
	name = "樱桃炸弹";
	type = cherry_bomb;
	origin_color = color = dark_red_back;
	high_light = dark_red;
	blood = defence = 30000;
	cost_sun = 150;
	cooling = 300;
	cool_time = 300;

	life_time = 11;
	bomb_time = 11;
	attack = 1800;
}
Wall_nut::Wall_nut():Plant(){
	name = "坚果墙";
	type = wall_nut;
	origin_color = color = dark_yellow_back;
	high_light = dark_yellow;
	blood = defence = 4000;
	cost_sun = 50;
	cooling = 300;
	cool_time = 300;
}
Potato_mine::Potato_mine(){
	name = "土豆雷";
	type = potato_mine;
	origin_color = color = grey_back;
	high_light = grey;
	blood = defence = 300;
	cost_sun = 25;
	cooling = 300;
	cool_time = 300;

	rest_time = 150;
	bomb_time = 11;
	attack = 1800;
}
Snow_pea::Snow_pea():Plant(){
	name = "寒冰射手";
	type = snow_pea;
	origin_color = color = dark_cyan_back;
	high_light = dark_cyan;
	blood = defence = 300;
	cost_sun = 175;
	cooling = 75;
	cool_time = 75;

	attack_cooling = 4;
	attack_time = 14;
	bullet_type = snow;
}
Chomper::Chomper(){
	name = "食人花";
	type = chomper;
	origin_color = color = default_color | dark_purple_back;
	high_light = dark_purple | selected;
	blood = defence = 300;
	cost_sun = 150;
	cooling = 75;
	cool_time = 75;

	rest_time = 0;
	attack = 1800;
}
Repeater::Repeater():Plant(){
	name = "双发射手";
	type = repeater;
	origin_color = color = dark_green_back;
	high_light = dark_green;
	blood = defence = 300;
	cost_sun = 200;
	cooling = 75;
	cool_time = 75;

	attack_cooling = 2;
	first = 12;
	second = 2;
	bullet_type = pea;
}
Squash::Squash():Plant(){
	name = "窝瓜";
	type = squash;
	origin_color = color = light_yellow_back;
	high_light = light_yellow;
	blood = defence = 30000;
	cost_sun = 50;
	cooling = 300;
	cool_time = 300;

	life_time = -1;
	squash_time = 11;
	attack = 1800;
}
Threepeater::Threepeater():Plant(){
	name = "三线射手";
	type = threepeater;
	origin_color = color = dark_green_back;
	high_light = dark_green;
	blood = defence = 300;
	cost_sun = 325;
	cooling = 75;
	cool_time = 75;

	attack_cooling = 4;
	attack_time = 14;
}
Jalapeno::Jalapeno():Plant(){
	name = "火爆辣椒";
	type = jalapeno;
	origin_color = color = dark_red_back;
	high_light = dark_red;
	blood = defence = 30000;
	cost_sun = 125;
	cooling = 500;
	cool_time = 500;

	life_time = 11;
	bomb_time = 11;
	attack = 1800;
}
Spikeweed::Spikeweed():Plant(){
	name = "地刺";
	type = spikeweed;
	origin_color = color = grey_back;
	high_light = grey;
	blood = defence = 300;
	cost_sun = 100;
	cooling = 75;
	cool_time = 75;

	attack = 20;
	attack_time = 7;
	attack_cooling = 7;
}
Torchwood::Torchwood():Plant(){
	name = "火炬树桩";
	type = torchwood;
	origin_color = color = light_red_back;
	high_light = light_red;
	blood = defence = 300;
	cost_sun = 175;
	cooling = 75;
	cool_time = 75;
}
Tall_nut::Tall_nut():Plant(){
	name = "高坚果";
	type = tall_nut;
	origin_color = color = dark_yellow_back;
	high_light = dark_yellow;
	blood = defence = 8000;
	cost_sun = 125;
	cooling = 300;
	cool_time = 300;
	can_jump = 0;
}
Pumpkin::Pumpkin():Plant(){
	name = "南瓜头";
	type = pumpkin;
	origin_color = color = light_yellow;
	blood = defence = 4000;
	cost_sun = 125;
	cooling = 300;
	cool_time = 300;
}
Garlic::Garlic(){
	name = "大蒜";
	type = garlic;
	origin_color = color = selected;
	high_light = default_color;
	blood = defence = 400;
	cost_sun = 50;
	cooling = 75;
	cool_time = 75;
}

//豌豆射手行动
void Peashooter::action( Game& game ){
	shine( game.lawn );
	if ( attack_cooling < attack_time ) attack_cooling++;
	if ( attack_cooling == attack_time ){
		if ( !shooter_can_attack( game.lawn ) ) return;
		attack_cooling = 0;
		Bullet* now = new Pea_bullet( x * ( single_length + 1 ) + single_length / 2 + 1 +
			grass_left , y * ( single_width + 1 ) + grass_top + single_width / 2 + 1 );
		game.bullet_list.push_back( now );
	}
}
//向日葵行动
void Sunflower::action( Game& game ){
	sun_shine( game );
	shine( game.lawn );
	sun_cooling++;
	if ( if_start ){
		if ( sun_cooling == sun_circle ){
			sun_shine_time = 10;
			sun_cooling = 0;
			game.store.sun += make_sun;
			game.store.sun_flash = 2;
		}
	}
	else{
		if ( sun_cooling == start_sun_circle ){
			sun_shine_time = 10;
			sun_cooling = 0;
			game.store.sun += make_sun;
			game.store.sun_flash = 2;
			if_start = 1;
		}
	}
}
//产生阳光时的闪烁
void Sunflower::sun_shine( Game& game ){
	if ( sun_shine_time ){
		if ( sun_shine_time == 10 ) color = light_yellow_back;
		else if ( sun_shine_time == 1 )color = origin_color;
		sun_shine_time--;
		game.lawn.grid_list[x][y].in_refresh = 1;
	}
}
//樱桃炸弹行动
void Cherry_bomb::action( Game& game ){
	life_time--;
	if ( life_time != 0 ) return;
	int row_up = max( y - 1 , 0 );
	int row_down = min( y + 1 , whole_width - 1 );
	int col_left = max( x - 1 , 0 );
	int col_right = min( x + 1 , whole_length - 1 );
	game.lawn.grid_list[x][y].plant_minus( this , defence );
	for ( int i = col_left; i <= col_right; i++ ){
		for ( int j = row_up; j <= row_down; j++ ){
			game.lawn.grid_list[i][j].bombing = bomb_time;
			if ( game.lawn.grid_list[i][j].zombie_list.empty() ) continue;
			for ( list<Zombie*>::iterator k = game.lawn.grid_list[i][j].
				zombie_list.begin(); k != game.lawn.grid_list[i][j].
				zombie_list.end(); k++ ){
				Zombie* now = ( *k );
				game.lawn.grid_list[i][j].zombie_minus( now , attack , game );
			}
		}
	}
}
//坚果墙行动
void Wall_nut::action( Game& game ){
	shine( game.lawn );
}
//土豆雷行动
void Potato_mine::action( Game& game ){
	shine( game.lawn );
	if ( rest_time ){
		rest_time--;
		if ( rest_time == 0 ){
			origin_color = color = light_yellow_back;
			game.lawn.grid_list[x][y].in_refresh = 1;
		}
	}
	if ( rest_time ) return;
	if ( !game.lawn.grid_list[x][y].zombie_list.size() ) return;
	game.lawn.grid_list[x][y].plant_minus( this , defence );
	game.lawn.grid_list[x][y].squashing = bomb_time;
	for ( list<Zombie*>::iterator k = game.lawn.grid_list[x][y].
		zombie_list.begin(); k != game.lawn.grid_list[x][y].
		zombie_list.end(); k++ ){
		Zombie* now = ( *k );
		game.lawn.grid_list[x][y].zombie_minus( now , attack , game );
	}
}
//寒冰射手行动
void Snow_pea::action( Game& game ){
	shine( game.lawn );
	if ( attack_cooling < attack_time ) attack_cooling++;
	if ( attack_cooling == attack_time ){
		if ( !shooter_can_attack( game.lawn ) ) return;
		attack_cooling = 0;
		Bullet* now = new Snow_bullet( x * ( single_length + 1 ) + single_length / 2 + 1 +
			grass_left , y * ( single_width + 1 ) + grass_top + single_width / 2 + 1 );
		game.bullet_list.push_back( now );
	}
}
//食人花行动
void Chomper::action( Game& game ){
	shine( game.lawn );
	if ( rest_time ){
		rest_time--;
		set_cursor( 0 , y );
		if ( rest_time == 5 ){
			origin_color = color = default_color | dark_purple_back;
			game.lawn.grid_list[x][y].in_refresh = 1;
		}
	}
	if ( rest_time ) return;
	if ( !game.lawn.grid_list[x][y].zombie_list.size() && ( x == whole_length - 1
		|| !game.lawn.grid_list[x + 1][y].zombie_list.size() ) ) return;
	int flag = 0;
	if ( game.lawn.grid_list[x][y].zombie_list.size() ) flag = x;
	else flag = x + 1;
	Grid* now = &game.lawn.grid_list[flag][y];
	for ( auto k = now->zombie_list.begin();
		k != now->zombie_list.end(); k++ ){
		if ( ( *k )->type == pole_vaulting && ( *k )->can_jump == 1 ) continue;
		now->zombie_minus( now->zombie_list.front() , attack , game );
		rest_time = 425;
		origin_color = color = grey_back;
		game.lawn.grid_list[x][y].in_refresh = 1;
		break;
	}
}
//双发射手行动
void Repeater::action( Game& game ){
	shine( game.lawn );
	if ( attack_cooling < first + second ) attack_cooling++;
	if ( attack_cooling == first ){
		if ( !shooter_can_attack( game.lawn ) ) return;
		Bullet* now = new Pea_bullet( x * ( single_length + 1 ) + single_length / 2 + 1 +
			grass_left , y * ( single_width + 1 ) + grass_top + single_width / 2 + 1 );
		game.bullet_list.push_back( now );
	}
	if ( attack_cooling == first + second ){
		if ( !shooter_can_attack( game.lawn ) ) return;
		attack_cooling = 0;
		Bullet* now = new Pea_bullet( x * ( single_length + 1 ) + single_length / 2 + 1 +
			grass_left , y * ( single_width + 1 ) + grass_top + single_width / 2 + 1 );
		game.bullet_list.push_back( now );
	}
}
//窝瓜行动
void Squash::action( Game& game ){
	if ( !game.lawn.grid_list[x][y].zombie_list.size() && ( x == whole_length - 1
		|| !game.lawn.grid_list[x + 1][y].zombie_list.size() )
		&& life_time == -1 ) return;
	if ( life_time == -1 ) life_time = 10;
	else life_time--;
	if ( life_time != 0 ) return;
	int flag = 0;
	if ( game.lawn.grid_list[x][y].zombie_list.size() ) flag = x;
	else flag = x + 1;
	for ( list<Zombie*>::iterator k = game.lawn.grid_list[flag][y].
		zombie_list.begin(); k != game.lawn.grid_list[flag][y].
		zombie_list.end(); ){
		Zombie* now = ( *k );
		if ( ( *k )->type == pole_vaulting && ( *k )->can_jump == 1 ){
			( (Pole_vaulting*) now )->jump( game );
			if ( now->x < 0 ) game.game_over();
			else{
				game.lawn.grid_list[now->x][now->y].zombie_list.push_back( *k );
				game.lawn.grid_list[now->x][now->y].in_refresh = 1;
				game.lawn.grid_list[now->x + 1][now->y].zombie_list.erase( k++ );
				game.lawn.grid_list[now->x + 1][now->y].in_refresh = 1;
			}
		}
		else{
			k++;
			game.lawn.grid_list[flag][y].zombie_minus( now , attack , game );
		}

	}
	game.lawn.grid_list[x][y].plant_minus( this , defence );
	game.lawn.grid_list[flag][y].squashing = squash_time;
}
//三线射手行动
void Threepeater::action( Game& game ){
	shine( game.lawn );
	if ( attack_cooling < attack_time ) attack_cooling++;
	if ( attack_cooling == attack_time ){
		if ( !can_attack( game.lawn ) ) return;
		attack_cooling = 0;
		Bullet* now = new Pea_bullet( x * ( single_length + 1 ) + single_length / 2 + 1 +
			grass_left , y * ( single_width + 1 ) + grass_top + single_width / 2 + 1 );
		game.bullet_list.push_back( now );
		if ( y > 0 ){
			now = new Pea_bullet( x * ( single_length + 1 ) + single_length / 2 + 1 +
				grass_left , ( y - 1 ) * ( single_width + 1 ) + grass_top + single_width / 2 + 1 );
			game.bullet_list.push_back( now );
		}
		if ( y < whole_width - 1 ){
			now = new Pea_bullet( x * ( single_length + 1 ) + single_length / 2 + 1 +
				grass_left , ( y + 1 ) * ( single_width + 1 ) + grass_top + single_width / 2 + 1 );
			game.bullet_list.push_back( now );
		}
	}
}
bool Threepeater::can_attack( Lawn& lawn ){
	if ( shooter_can_attack( lawn ) ) return true;
	if ( y > 0 ){
		y--;
		if ( shooter_can_attack( lawn ) ){
			y++;
			return true;
		}
		y++;
	}
	if ( y < whole_width - 1 ){
		y++;
		if ( shooter_can_attack( lawn ) ){
			y--;
			return true;
		}
		y--;
	}
	return false;
}
//火爆辣椒行动
void Jalapeno::action( Game& game ){
	life_time--;
	if ( life_time != 0 ) return;
	game.lawn.grid_list[x][y].plant_minus( this , defence );
	for ( int i = 0; i < whole_length; i++ ){
		game.lawn.grid_list[i][y].bombing = bomb_time;
		if ( game.lawn.grid_list[i][y].zombie_list.empty() ) continue;
		for ( list<Zombie*>::iterator k = game.lawn.grid_list[i][y].
			zombie_list.begin(); k != game.lawn.grid_list[i][y].
			zombie_list.end(); k++ ){
			Zombie* now = ( *k );
			game.lawn.grid_list[i][y].zombie_minus( now , attack , game );
		}
	}
}
//地刺行动
void Spikeweed::action( Game& game ){
	shine( game.lawn );
	if ( attack_cooling < attack_time ) attack_cooling++;
	if ( attack_cooling < attack_time )return;
	attack_cooling = 0;
	Grid* now = &game.lawn.grid_list[x][y];
	list<Zombie*>::iterator k;
	for ( k = now->zombie_list.begin();
		k != now->zombie_list.end(); k++ ){
		now->zombie_minus( ( *k ) , attack , game );
	}
}
//火炬树桩行动
void Torchwood::action( Game& game ){
	shine( game.lawn );
}
//高坚果行动
void Tall_nut::action( Game& game ){
	shine( game.lawn );
}
//南瓜头行动
void Pumpkin::action( Game& game ){
	shine( game.lawn );
}
//大蒜行动
void Garlic::action( Game& game ){
	shine( game.lawn );
}



