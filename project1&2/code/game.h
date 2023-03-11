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
	list<Bullet*>bullet_list;//�ӵ��б�
	enum State { Shopping , Planting , Wiping , Pause }state;//״̬
	int store_plant_x;
	int store_plant_y;//��ǰҪ��ֲ��ֲ���������
	int x;
	int y;//��ǰ������λ�ã���״̬�й�
	char tombstone [ 3 * ( 11 + 1 ) + 1 ] [ 50 ];//Ĺ��
public:
	//��ʼ��
	Game();
	//��ʼѭ��
	void start();

	//�̵�ģʽ
	void shop();
	//�Ƿ�ѡ���̵�ֲ��
	void plant_selected( int x , int y , int z );
	//�Ƿ�ȡ����ֲ
	void unplant( int z );
	//����ֲ��
	bool buy( int z , int w );

	//��ֲģʽ
	bool plant( int z , int w );
	//ѡ�вݿ�
	void grid_selected( int x , int y , int z );
	//ȡ��ѡ�вݿ�
	void grid_unselected( int x , int y );

	//����ģʽ
	void wipe();
	//�Ƿ�ѡ�в���
	void shovel_selected( int z );
	//�Ƿ�ȡ������
	void uncancel( int z );
	//��ֲ�����
	bool cancel_plant( int x , int y );

	//��ͣģʽ
	void pause();

	//�ӵ��ж�
	void bullet_action();
	//��ӡ�ӵ�
	void print_bullet();
	//��ʬ����
	void slow_zombie(Zombie*zombie);
	//��ʬ�ָ��ٶ�
	void unslow_zombie( Zombie* zombie );
	//��ƺ�ж�
	void lawn_action();
	//�̵��ж�
	void store_action( Game& game );

	//ʧ��
	void game_over();
	//��ӡĹ��
	void print_tombstone();
};