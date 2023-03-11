#include "object.h"
#include"overall.h"

Object::Object(QWidget* parent): QLabel(parent)
{
    alive = 1;
    setMouseTracking(true);
    lawn = (Lawn*)parent;
}

int Object::get_x()
{
    return (pos().x() + width() / 2 - grass_left) / single_length;
}
int Object::get_y()
{
    return (pos().y() + height() / 2 - grass_top) / single_width;
}

Special::Special(int x, QWidget* parent): Object(parent)
{
    life_time = x;
    setScaledContents(true);
    raise();
}
Special::~Special()
{
    delete movie();
}
void Special::action()
{
    if (movie()->currentFrameNumber() < movie()->frameCount() - 1) return;
    movie()->stop();
    life_time--;
    //   if (movie() == NULL) return;
    if (life_time == 0) alive = 0;
}
