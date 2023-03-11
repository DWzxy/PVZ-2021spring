#pragma once
using namespace std;
#include"plant.h"
class Game;
//ֲ������
class Store {
	friend class Game;
	friend class Plant;
	friend class Grid;
	friend class Peashooter;
	friend class Sunflower;
private:
	int page;//��ǰ�ڵڼ�ҳ
	int sun_cooling;//Ŀǰ���������������
	int sun_circle;//��������ļ��
	int sun;//��������
	int sun_flash;//������˸�׶�
	int chat_circle;//��ʾ��Ϣ��ʾʱ��
	int chat_cooling;//��ʾ��Ϣ����ʾʱ��
	int now_chat;//��ǰ��ʾ���
	Plant plant_list [ 3 ] [ 8 ];//�ɹ����ֲ��
	Plant_type now_plant;//��ǰҪ��ֲ��ֲ��
	int score;//����
	bool score_refresh;//�����Ƿ����
	char* chat [ 101 ];
public:
	//��ʼ��
	Store();
	//����
	void print_frame();
	//��ӡֲ����
	void print_all_plant();
	//��ҳ
	void turn_page( int page );
	//��ӡ����ֲ��
	void print_plant( int x , int y , int k,int page );
	//��ӡ����
	void print_sun( int x );
	//��ӡ����
	void print_score();
	//��ӡ����
	void print_shovel();
	//��ӡ������Ϣ
	void print_help();
	//ֲ����ȴ
	void refresh( Game& game );
	//������ʾ��Ϣ
	void set_chat( int x );
	//������ʾ��Ϣ
	void chat_refresh();
	//��ӡ��ʾ��Ϣ
	void print_chat( int x );
};