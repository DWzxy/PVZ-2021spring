#ifndef OBJECT_H
#define OBJECT_H
#include<QLabel>
#include<QWidget>
class Lawn;
class Object: public QLabel
{
    Q_OBJECT
    friend class Lawn;
    friend class Day_lawn;
    friend class Night_lawn;
protected:
    bool alive;
    Lawn* lawn;
public:
    Object(QWidget* parent = 0);
    virtual void action() {}
    int get_x();
    int get_y();//计算当前在哪一个草块
};

class Special: public Object
{
    friend class Cherry_bomb;
    friend class Potato_mine;
private:
    int life_time;
public:
    Special(int x, QWidget* parent = 0);
    ~Special();
    void action();
};//用于播放动图

#endif // OBJECT_H
