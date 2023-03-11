#pragma once
#include"plant.h"
#include"zombie.h"
#include"overall.h"
#include<list>
using namespace std;
class Grid {
	friend class Game;
	friend class Lawn;
	friend class Plant;
	friend class Store;
	friend class Peashooter;
	friend class Sunflower;
	friend class Cherry_bomb;
	friend class Wall_nut;
	friend class Snow_pea;
	friend class Squash;
	friend class Repeater;
	friend class Tall_nut;
	friend class Pumpkin;
	friend class Garlic;
	friend class Spikeweed;
	friend class Jalapeno;
	friend class Potato_mine;
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
	int x;
	int y;//����λ��
	int sta_x;
	int sta_y;//���λ��
	Plant* plant;//�ø����ϵ�ֲ��
	Pumpkin* pumpkin;//�ø����ϵ��Ϲ�ͷ
	list<Zombie*>zombie_list;//�ø����ϵĽ�ʬ
	bool in_refresh;//�ڲ��Ƿ���Ҫ���»���
	bool out_refresh;//�ⲿ�Ƿ���Ҫ���»���
	int color;//��ǰ��ɫ������Ϸ״̬�����λ��Ӱ�죩

	int bombing;//��ըʱ���
	int squashing;//�ѹ�ʱ���
	int flashing;//�����ƹ�ʱ���
public:
	//��ʼ��
	void init( int x , int y );
	//���ֲ��
	void add_plant( Plant* x);
	//����ڲ�
	void clear();
	//��ӡֲ���ʬ
	void print( Game& game );
	//��ӡ����ֵ
	void print_defence( int x , int y , int z,int w);
	//��ӡ����
	void print_name( string x , int y,int z , int w );
	//ֲ���ж�
	void plant_action( Game& game );
	//��ʬ��Ѫ
	void zombie_minus( Zombie* zombie, int x , Game& game );
	//ֲ���Ѫ
	void plant_minus( Plant*plant,int x );
	//��ӡ�߿�
	void print_circle(Game&game);
	//����
	void refresh(Game&game);
	//��������Ľ�ʬ
	void clear_zombie();
};
class Lawn {
	friend class Game;
	friend class Plant;
	friend class Grid;
	friend class Peashooter;
	friend class Sunflower;
	friend class Cherry_bomb;
	friend class Wall_nut;
	friend class Snow_pea;
	friend class Squash;
	friend class Repeater;
	friend class Jalapeno;
	friend class Tall_nut;
	friend class Pumpkin;
	friend class Garlic;
	friend class Spikeweed;
	friend class Potato_mine;
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
	int zombie_cooling;//����������ʬ�Ľ���
	int zombie_circle [ 21 ] [ 2 ];//��ʬ������ʱ��������Ŀ
	int whole_wave;//������һ�ְ�����ʱ������Ŀ
	Grid grid_list [ whole_length ] [ whole_width ];
	bool flag;//�Ƿ��ѳ���ҡ�콩ʬ
public:
	Lawn();
	//����
	void refresh( Game& game );
	//������ʬ
	void make_zombie(Game&game);
	//��ʬ�ж�
	void zombie_action( Game& game );
};