#include"Load.h"

Loading::Loading() {
	this->x = UserDefault::getInstance()->getDoubleForKey("Sprite_x", x);
	this->y = UserDefault::getInstance()->getDoubleForKey("Sprite_y", y);
	this->mapName = UserDefault::getInstance()->getStringForKey("CurrentMap", mapName);

}
double Loading:: getPositionX() {
	return this->x;
};
double Loading:: getPositionY() {
	return this->y;
};
string Loading:: getMapName() {
	return this->mapName;
}