#include<windows.h>
#include<stdio.h>
#include<conio.h>
#include<iostream>
#include<ctime>
#include<cstdlib>
#include"game.h"
#include"overall.h"
using namespace std;
//初始化
Game::Game(){
	set_screen_title( (TCHAR*) "Plants VS. Zombies" );
	set_screen_size();
	hide_cursor();
	x = 0;
	y = 0;
	bullet_list.clear();
	strcpy_s( tombstone[0] , "■■■■■■■■" );
	strcpy_s( tombstone[1] , "■■■■■■■■■■■" );
	strcpy_s( tombstone[2] , "■■■■■■■■■■■■■■" );
	strcpy_s( tombstone[3] , "■■■■■■■■■■■■■■■■" );
	strcpy_s( tombstone[4] , "◥■■■■■■■■■■■■■■◤" );
	strcpy_s( tombstone[5] , "■■■■■■■■■■■■■■" );
	strcpy_s( tombstone[6] , "■■■■■■■■■■■■■■" );
	strcpy_s( tombstone[7] , "■■■■■■■■■■■■■■" );
	strcpy_s( tombstone[8] , "■■■■■■■■■■■■■■" );
	strcpy_s( tombstone[9] , "■■■■■■■■■■■■■■" );
	strcpy_s( tombstone[10] , "■■■■■■■■■■■■■■" );
	strcpy_s( tombstone[11] , "■■■■■■■■■■■■■■" );
	strcpy_s( tombstone[12] , "■■■■■■■■■■■■■■" );
	strcpy_s( tombstone[13] , "■■■■■■■■■■■■■■" );
	strcpy_s( tombstone[14] , "■■■■■■■■■■■■■■" );
	strcpy_s( tombstone[15] , "◢■■■■■■■■■■■■■■■■◣" );
	strcpy_s( tombstone[16] , "■■■■■■■■■■■■■■■■■■" );
	strcpy_s( tombstone[17] , "■■■■■■■■■■■■■■■■■■■■■■" );
	strcpy_s( tombstone[18] , "■■■■■■■■■■■■■■■■■■■■■■" );
	shop();
	start();
}
//开始循环
void Game::start() {
	while ( true ) {
		Sleep( single_time );
		if ( state == Pause ){
			while ( true ){
				if ( _kbhit() ){
					char c = _getch();
					if ( c == ' ' ){
						shop();
						break;
					}
				}
			}
		}
		if ( state == Shopping ) {
			if ( _kbhit() ) {
				char c = _getch();
				if ( c == -32 ) {
					c = _getch();
					if ( c == 72 ){
						if ( y > 0 && x < 3 ){
							plant_selected( x , y , default_color );
							y--;
							plant_selected( x , y , selected );
						}
						else if ( store.page > 0 && x < 3 ){
							store.turn_page( store.page - 1 );
							y = 3;
							plant_selected( x , y , selected );
						}
					}
					else if ( c == 80 ) {
						if ( y < 3 && x < 3 ){
							plant_selected( x , y , default_color );
							y++;
							plant_selected( x , y , selected );
						}
						else if ( store.page < 1 && x < 3 ){
							store.turn_page( store.page + 1 );
							y = 0;
							plant_selected( x , y , selected );
						}
					}
					else if ( c == 75 && x > 0 && x < 3 ) {
						plant_selected( x , y , default_color );
						x--;
						plant_selected( x , y , selected );
					}
					else if ( c == 77 && x < 2 ) {
						plant_selected( x , y , default_color );
						x++;
						plant_selected( x , y , selected );
					}
					else if ( c == 77 && x == 2 ){
						plant_selected( x , y , default_color );
						x++;
						shovel_selected( light_yellow_back | black );
					}
					else if ( c == 75 && x == 3 ){
						x--;
						plant_selected( x , y , selected );
						shovel_selected( light_cyan );
					}
				}
				else if ( c == ' ' && x < 3 ) {
					if ( buy( x , y ) == 1 ) unplant( dark_cyan_back );
				}
				else if ( c == ' ' && x == 3 ){
					uncancel( dark_cyan_back );
					wipe();
				}
				else if ( c == 27 && x < 3 ){
					if ( store.plant_list[x][y].cooling !=
						store.plant_list[x][y].cool_time )
						plant_selected( x , y , grey );
					else plant_selected( x , y , default_color );
					pause();
					continue;
				}
				else if ( c == 27 && x == 3 ){
					shovel_selected( light_cyan );
					pause();
					continue;
				}
				else if ( c == 13 ){
					if ( store.sun < 99000 ) {
						store.sun += 1000;
						store.sun_flash = 2;
					}
				}
			}
		}
		if ( state == Planting ) {
			if ( _kbhit() ) {
				char c = _getch();
				if ( c == -32 ) {
					c = _getch();
					if ( c == 72 && y > 0 && y < whole_width ) {
						grid_unselected( x , y );
						y--;
						grid_selected( x , y , light_cyan );
					}
					else if ( c == 80 && y < whole_width - 1 ) {
						grid_unselected( x , y );
						y++;
						grid_selected( x , y , light_cyan );
					}
					else if ( c == 75 && x > 0 && x < whole_length && y < whole_width ) {
						grid_unselected( x , y );
						x--;
						grid_selected( x , y , light_cyan );
					}
					else if ( c == 77 && x < whole_length - 1 && y < whole_width ) {
						grid_unselected( x , y );
						x++;
						grid_selected( x , y , light_cyan );
					}
					else if ( c == 80 && y == whole_width - 1 ){
						grid_unselected( x , y );
						y++;
						unplant( light_purple_back );
					}
					else if ( c == 72 && y == whole_width ){
						y--;
						grid_selected( x , y , light_cyan );
						unplant( dark_cyan_back );
					}
				}
				else if ( c == ' ' && y < whole_width ) {
					if ( plant( store_plant_x , store_plant_y ) == 1 ){
						grid_unselected( x , y );
						plant_selected( store_plant_x , store_plant_y , default_color );
						lawn.grid_list[x][y].in_refresh = 1;
						shop();
					}
				}
				else if ( c == ' ' && y == whole_width ){
					plant_selected( store_plant_x , store_plant_y , selected );
					state = Shopping;
					x = store_plant_x;
					y = store_plant_y;
				}
			}
		}
		if ( state == Wiping ) {
			if ( _kbhit() ) {
				char c = _getch();
				if ( c == -32 ) {
					c = _getch();
					if ( c == 72 && y > 0 && y < whole_width ) {
						grid_unselected( x , y );
						y--;
						grid_selected( x , y , light_red );
					}
					else if ( c == 80 && y < whole_width - 1 ) {
						grid_unselected( x , y );
						y++;
						grid_selected( x , y , light_red );
					}
					else if ( c == 75 && x > 0 && x < whole_length && y < whole_width ) {
						grid_unselected( x , y );
						x--;
						grid_selected( x , y , light_red );
					}
					else if ( c == 77 && x < whole_length - 1 && y < whole_width ) {
						grid_unselected( x , y );
						x++;
						grid_selected( x , y , light_red );
					}
					else if ( c == 80 && y == whole_width - 1 ){
						grid_unselected( x , y );
						y++;
						uncancel( light_purple_back );
					}
					else if ( c == 72 && y == whole_width ){
						y--;
						grid_selected( x , y , light_red );
						uncancel( dark_cyan_back );
					}
				}
				else if ( c == ' ' && y < whole_width ) {
					if ( cancel_plant( x , y ) == 0 ) continue;
					grid_unselected( x , y );
					plant_selected( store_plant_x , store_plant_y , default_color );
					shovel_selected( light_cyan );
					shop();
				}
				else if ( c == ' ' && y == whole_width ){
					plant_selected( store_plant_x , store_plant_y , selected );
					shovel_selected( light_cyan );
					state = Shopping;
					x = store_plant_x;
					y = store_plant_y;
				}
			}
		}
		store_action( *this );
		lawn_action();
		bullet_action();
		lawn.refresh( *this );
		print_bullet();
	}
}
//商店模式
void Game::shop() {
	state = Shopping;
	x = 0;
	y = 0;
	plant_selected( 0 , 0 , selected );
}
//是否选中商店植物
void Game::plant_selected( int x , int y , int z ) {
	store.print_plant( x , y , z , store.page );
}
//是否取消种植
void Game::unplant( int z ){
	int p = store_plant_x;
	int q = store_plant_y;
	set_cursor( 0 , 0 );
	p = help_length + 1 + p * 22;
	q = grass_bottom + 1 + 1 + q * 2;
	set_cursor( p , q );
	print_in_color( "      取消种植      " , z );
}
//购买植物
bool Game::buy( int z , int w ) {
	if ( store.page == 1 && ( y > 0 && x > 0 || x == 0 && y > 1 ) ){
		store.set_chat( 5 );
		return 0;
	}
	if ( store.plant_list[z][w + store.page * 4].cooling !=
		store.plant_list[z][w + store.page * 4].cool_time ){
		store.set_chat( 4 );
		return 0;
	}
	else if ( store.plant_list[z][w + store.page * 4].cost_sun > store.sun ){
		store.set_chat( 3 );
		return 0;
	}
	x = 0;
	y = whole_width - 1;
	grid_selected( x , y , light_cyan );
	state = Planting;
	store_plant_x = z;
	store_plant_y = w;
	int i = w * 3 + z + store.page * 12;
	if ( i == 0 ) store.now_plant = peashooter;
	else if ( i == 1 ) store.now_plant = sunflower;
	else if ( i == 2 ) store.now_plant = cherry_bomb;
	else if ( i == 3 ) store.now_plant = wall_nut;
	else if ( i == 4 ) store.now_plant = potato_mine;
	else if ( i == 5 ) store.now_plant = snow_pea;
	else if ( i == 6 ) store.now_plant = chomper;
	else if ( i == 7 ) store.now_plant = repeater;
	else if ( i == 8 ) store.now_plant = squash;
	else if ( i == 9 ) store.now_plant = threepeater;
	else if ( i == 10 ) store.now_plant = jalapeno;
	else if ( i == 11 ) store.now_plant = spikeweed;
	else if ( i == 12 )  store.now_plant = torchwood;
	else if ( i == 13 )  store.now_plant = tall_nut;
	else if ( i == 14 )  store.now_plant = pumpkin;
	else if ( i == 15 )  store.now_plant = garlic;
	return 1;
}
//种植模式
bool Game::plant( int z , int w ) {
	if ( store.now_plant != pumpkin && lawn.grid_list[x][y].plant != NULL ) {
		store.set_chat( 1 );
		return 0;
	}
	if ( store.now_plant == peashooter )
		lawn.grid_list[x][y].add_plant( new Peashooter() );
	else if ( store.now_plant == sunflower )
		lawn.grid_list[x][y].add_plant( new Sunflower() );
	else if ( store.now_plant == cherry_bomb )
		lawn.grid_list[x][y].add_plant( new Cherry_bomb() );
	else if ( store.now_plant == wall_nut )
		lawn.grid_list[x][y].add_plant( new Wall_nut() );
	else if ( store.now_plant == potato_mine )
		lawn.grid_list[x][y].add_plant( new Potato_mine() );
	else if ( store.now_plant == snow_pea )
		lawn.grid_list[x][y].add_plant( new Snow_pea() );
	else if ( store.now_plant == chomper )
		lawn.grid_list[x][y].add_plant( new Chomper() );
	else if ( store.now_plant == repeater )
		lawn.grid_list[x][y].add_plant( new Repeater() );
	else if ( store.now_plant == squash )
		lawn.grid_list[x][y].add_plant( new Squash() );
	else if ( store.now_plant == threepeater )
		lawn.grid_list[x][y].add_plant( new Threepeater() );
	else if ( store.now_plant == jalapeno )
		lawn.grid_list[x][y].add_plant( new Jalapeno() );
	else if ( store.now_plant == spikeweed )
		lawn.grid_list[x][y].add_plant( new Spikeweed() );
	else if ( store.now_plant == torchwood )
		lawn.grid_list[x][y].add_plant( new Torchwood() );
	else if ( store.now_plant == tall_nut )
		lawn.grid_list[x][y].add_plant( new Tall_nut() );
	else if ( store.now_plant == pumpkin ){
		Grid* now = &lawn.grid_list[x][y];
		if ( now->pumpkin != NULL ){
			store.set_chat( 6 );
			return 0;
		}
		now->pumpkin = new Pumpkin();
	}
	else if ( store.now_plant == garlic )
		lawn.grid_list[x][y].add_plant( new Garlic() );
	lawn.grid_list[x][y].in_refresh = 1;
	store.sun -= store.plant_list[z][w + store.page * 4].cost_sun;
	store.print_sun( light_yellow );
	store.plant_list[z][w + store.page * 4].cooling = 0;
	return 1;
}
//选中草块
void Game::grid_selected( int x , int y , int z ) {
	lawn.grid_list[x][y].color = z;
	lawn.grid_list[x][y].out_refresh = 1;
}
//取消选中草块
void Game::grid_unselected( int x , int y ) {
	lawn.grid_list[x][y].color = grass_color;
	lawn.grid_list[x][y].out_refresh = 1;
}
//铲除模式
void Game::wipe() {
	x = 0;
	y = whole_width - 1;
	grid_selected( x , y , light_red );
	state = Wiping;
}
//是否选中铲除
void Game::shovel_selected( int z ){
	int x = screen_size_x - help_length - sun_length;
	int y = grass_bottom + 1 + 3 * 2 + 1;
	set_cursor( x + 1 , y );
	print_in_color( "铲除植物" , z );
}
//是否取消铲除
void Game::uncancel( int z ){
	int x = screen_size_x - help_length - sun_length;
	int y = grass_bottom + 1 + 3 * 2 + 1;
	set_cursor( x + 1 , y );
	print_in_color( "取消铲除" , z );
}
//将植物铲除
bool Game::cancel_plant( int x , int y ) {
	if ( lawn.grid_list[x][y].plant == NULL &&
		lawn.grid_list[x][y].pumpkin == NULL ){
		store.set_chat( 2 );
		return 0;
	}
	if ( lawn.grid_list[x][y].plant != NULL )
		lawn.grid_list[x][y].plant = NULL;
	else lawn.grid_list[x][y].pumpkin = NULL;
	lawn.grid_list[x][y].in_refresh = 1;
	return 1;
}
//暂停模式
void Game::pause(){
	state = Pause;
	int x = whole_length / 2 - 1;
	int y = whole_width / 2 - 1;
	for ( int i = -1; i < 3; i++ ){
		for ( int j = 0; j < 3; j++ ){
			lawn.grid_list[x + i][y + j].in_refresh = 1;
			lawn.grid_list[x + i][y + j].out_refresh = 1;
		}
	}
	int p = grass_left + x * ( single_length + 1 );
	int q = grass_top + y * ( single_width + 1 );
	print_tombstone();
	set_cursor( p + single_length - 3 , q + 3 );
	print_in_color( "游戏暂停" , default_color );
	set_cursor( p + single_length - 5 , q + 8 );
	print_in_color( "按空格键返回" , default_color );
}
//子弹行动
void Game::bullet_action(){
	if ( bullet_list.empty() ) return;
	list<Bullet*>::iterator now;
	for ( now = bullet_list.begin(); now != bullet_list.end();){
		int p = ( ( *now )->x - grass_left ) / ( single_length + 1 );
		int q = ( ( *now )->y - grass_top ) / ( single_width + 1 );
		lawn.grid_list[p][q].in_refresh = 1;
		if ( !lawn.grid_list[p][q].zombie_list.empty() ){
			Zombie* now_zombie = lawn.grid_list[p][q].zombie_list.front();
			if ( ( *now )->type == snow ) slow_zombie( now_zombie );
			else if ( ( *now )->type == fire ) unslow_zombie( now_zombie );
			lawn.grid_list[p][q].zombie_minus( now_zombie ,
				( *now )->attack , *this );
			bullet_list.erase( now++ );
			lawn.grid_list[p][q].out_refresh = 1;
		}//子弹造成伤害
		else{
			( *now )->x += ( *now )->speed;
			if ( ( *now )->x >= screen_size_x - 1 ){
				bullet_list.erase( now++ );
				lawn.grid_list[p][q].out_refresh = 1;
			}//飞到最右边则清除
			else{
				int pp = ( ( *now )->x - grass_left ) / ( single_length + 1 );
				if ( p != pp ){
					set_cursor( ( *now )->x - ( *now )->speed + 1 , ( *now )->y );
					print_in_color( "#" , lawn.grid_list[p][q].color );
					//若越过草块边界则补全边框
					if ( lawn.grid_list[pp][q].plant != NULL &&
						lawn.grid_list[pp][q].plant->type == torchwood ){
						if ( ( *now )->type == pea ){
							Fire_bullet* new_fire = new Fire_bullet( ( *now )->x , ( *now )->y );
							bullet_list.erase( now++ );
							bullet_list.push_back( new_fire );
							continue;
						}
						else if ( ( *now )->type == snow ){
							Pea_bullet* new_pea = new Pea_bullet( ( *now )->x , ( *now )->y );
							bullet_list.erase( now++ );
							bullet_list.push_back( new_pea );
							continue;
						}
					}//如果经过了火炬树桩
				}
				if ( !lawn.grid_list[pp][q].zombie_list.empty() ){
					Zombie* now_zombie = lawn.grid_list[pp][q].
						zombie_list.front();
					if ( ( *now )->type == snow )  slow_zombie( now_zombie );
					else if ( ( *now )->type == fire ) unslow_zombie( now_zombie );
					lawn.grid_list[pp][q].zombie_minus( now_zombie ,
						( *now )->attack , *this );
					bullet_list.erase( now++ );
				}
				else now++;
			}
		}//子弹移动
	}
}
//打印子弹
void Game::print_bullet(){
	if ( bullet_list.empty() ) return;
	list<Bullet*>::iterator i;
	for ( i = bullet_list.begin(); i != bullet_list.end(); i++ ){
		int x = ( *i )->x;
		int y = ( *i )->y;
		set_cursor( x , y );
		print_in_color( "●" , ( *i )->color );
	}
}
//僵尸减速
void Game::slow_zombie( Zombie* zombie ){
	zombie->slowing = 101;
	if ( zombie->type == dancing ){
		if ( ( (Dancing*) zombie )->left != NULL )
			( (Dancing*) zombie )->left->slowing = 101;
		if ( ( (Dancing*) zombie )->right != NULL )
			( (Dancing*) zombie )->right->slowing = 101;
		if ( ( (Dancing*) zombie )->top != NULL )
			( (Dancing*) zombie )->top->slowing = 101;
		if ( ( (Dancing*) zombie )->bottom != NULL )
			( (Dancing*) zombie )->bottom->slowing = 101;
	}
	if ( zombie->type == back_up ){
		( (Back_up*) zombie )->dancing->slowing = 101;
		if ( ( (Back_up*) zombie )->dancing->left != NULL )
			( (Back_up*) zombie )->dancing->left->slowing = 101;
		if ( ( (Back_up*) zombie )->dancing->right != NULL )
			( (Back_up*) zombie )->dancing->right->slowing = 101;
		if ( ( (Back_up*) zombie )->dancing->top != NULL )
			( (Back_up*) zombie )->dancing->top->slowing = 101;
		if ( ( (Back_up*) zombie )->dancing->bottom != NULL )
			( (Back_up*) zombie )->dancing->bottom->slowing = 101;
	}//舞王与伴舞一同减速
}
//僵尸恢复速度
void Game::unslow_zombie( Zombie* zombie ){
	if ( zombie->slowing ) zombie->slowing = 1;
	/*	if ( zombie->type == dancing ){
			if ( ( (Dancing*) zombie )->left != NULL )
				( (Dancing*) zombie )->left->slowing = 1;
			if ( ( (Dancing*) zombie )->right != NULL )
				( (Dancing*) zombie )->right->slowing = 1;
			if ( ( (Dancing*) zombie )->top != NULL )
				( (Dancing*) zombie )->top->slowing = 1;
			if ( ( (Dancing*) zombie )->bottom != NULL )
				( (Dancing*) zombie )->bottom->slowing = 1;
		}
		if ( zombie->type == back_up ){
			( (Back_up*) zombie )->dancing->slowing = 1;
			if ( ( (Back_up*) zombie )->dancing->left != NULL )
				( (Back_up*) zombie )->dancing->left->slowing = 1;
			if ( ( (Back_up*) zombie )->dancing->right != NULL )
				( (Back_up*) zombie )->dancing->right->slowing = 1;
			if ( ( (Back_up*) zombie )->dancing->top != NULL )
				( (Back_up*) zombie )->dancing->top->slowing = 1;
			if ( ( (Back_up*) zombie )->dancing->bottom != NULL )
				( (Back_up*) zombie )->dancing->bottom->slowing = 1;
		}//舞王与伴舞一同恢复速度*/
}
//草坪行动
void Game::lawn_action() {
	for ( int i = 0; i < whole_length; i++ ){
		for ( int j = 0; j < whole_width; j++ ){
			if ( lawn.grid_list[i][j].plant == NULL ) continue;
			lawn.grid_list[i][j].plant_action( *this );
		}
	}
	lawn.make_zombie( *this );
	lawn.zombie_action( *this );
}
//商店行动
void Game::store_action( Game& game ) {
	store.refresh( game );
}
//失败
void Game::game_over() {
	int x = whole_length / 2 - 1;
	int y = whole_width / 2 - 1;
	int p = grass_left + x * ( single_length + 1 ) - 10;
	int q = grass_top + y * ( single_width + 1 );
	print_tombstone();
	set_cursor( p + single_length + 7 , q + 5 );
	printf( "游戏结束" );
	set_cursor( p + single_length + 3 , q + 7 );
	printf( "你的分数是：%d " , store.score );
	while ( true );
}
//打印墓碑
void Game::print_tombstone(){
	int x = whole_length / 2 - 1;
	int y = whole_width / 2 - 1;
	int p = grass_left + x * ( single_length + 1 ) - 10;
	int q = grass_top + y * ( single_width + 1 );
	set_color( grey );
	set_cursor( p + 14 , q );
	printf( "%s" , tombstone[0] );
	set_cursor( p + 11 , q + 1 );
	printf( "%s" , tombstone[1] );
	set_cursor( p + 8 , q + 2 );
	printf( "%s" , tombstone[2] );
	set_cursor( p + 6 , q + 3 );
	printf( "%s" , tombstone[3] );
	set_cursor( p + 6 , q + 4 );
	printf( "%s" , tombstone[4] );
	for ( int i = 5; i < 15; i++ ){
		set_cursor( p + 8 , q + i );
		printf( "%s" , tombstone[i] );
	}
	set_cursor( p + 4 , q + 15 );
	printf( "%s" , tombstone[15] );
	set_cursor( p + 4 , q + 16 );
	printf( "%s" , tombstone[16] );
	set_cursor( p , q + 17 );
	printf( "%s" , tombstone[17] );
	set_cursor( p , q + 18 );
	printf( "%s" , tombstone[18] );
	set_color( default_color );
}