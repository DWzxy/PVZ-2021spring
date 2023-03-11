#include"overall.h"
//设置窗口名称

int get_x_num(int x)
{
    if (x < grass_left) return -1;
    int now = (x - grass_left) / (single_length);
    return now;
}
int get_y_num(int y)
{
    if (y < grass_top) return -1;
    int now = (y - grass_top) / (single_width);
    return now;
}
