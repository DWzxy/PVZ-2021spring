#pragma once
#include"lawn.h"
#include"zombie.h"
#include"plant.h"
#include"store.h"
#include<list>
using namespace std;
class Game {
	friend class Store;
	friend class Plant;
	friend class Lawn;
	friend class Bullet;
	friend class Grid;
	friend class Peashooter;
	friend class Sunflower;
	friend class Cherry_bomb;
	friend class Wall_nut;
	friend class Snow_pea;
	friend class Squash;
	friend class Repeater;
	friend class Torchwood;
	friend class Tall_nut;
	friend class Pumpkin;
	friend class Jalapeno;
	friend class Spikeweed;
	friend class Garlic;
	friend class Potato_mine;
	friend class Threepeater;
	friend class Chomper;
	friend class Zombie;
	friend class Ordinary;
	friend class Flag;
	friend class Conehead;
	friend class Pole_vaulting;
	friend class Bucket;
	friend class Newspaper;
	friend class Dancing;
	friend class Back_up;
	friend class Jack_in_the_box;
	friend class Catapult;
private:
	Lawn lawn;
	Store store;
	list<Bullet*>bullet_list;//子弹列表
	enum State { Shopping , Planting , Wiping , Pause }state;//状态
	int store_plant_x;
	int store_plant_y;//当前要种植的植物相对坐标
	int x;
	int y;//当前光标相对位置，与状态有关
	char tombstone [ 3 * ( 11 + 1 ) + 1 ] [ 50 ];//墓碑
public:
	//初始化
	Game();
	//开始循环
	void start();

	//商店模式
	void shop();
	//是否选中商店植物
	void plant_selected( int x , int y , int z );
	//是否取消种植
	void unplant( int z );
	//购买植物
	bool buy( int z , int w );

	//种植模式
	bool plant( int z , int w );
	//选中草块
	void grid_selected( int x , int y , int z );
	//取消选中草块
	void grid_unselected( int x , int y );

	//铲除模式
	void wipe();
	//是否选中铲除
	void shovel_selected( int z );
	//是否取消铲除
	void uncancel( int z );
	//将植物铲除
	bool cancel_plant( int x , int y );

	//暂停模式
	void pause();

	//子弹行动
	void bullet_action();
	//打印子弹
	void print_bullet();
	//僵尸减速
	void slow_zombie(Zombie*zombie);
	//僵尸恢复速度
	void unslow_zombie( Zombie* zombie );
	//草坪行动
	void lawn_action();
	//商店行动
	void store_action( Game& game );

	//失败
	void game_over();
	//打印墓碑
	void print_tombstone();
};