#include"save.h"

Save::Save(double Sprite_x, double Sprite_y, string CurrentMap) {
	this->x = Sprite_x;
	this->y = Sprite_y;
	this->mapName = CurrentMap;
	SaveInFile();
};

void Save::SaveInFile(){

	UserDefault::getInstance()->setDoubleForKey("Sprite_x", x);
	UserDefault::getInstance()->setDoubleForKey("Sprite_y", y);
	UserDefault::getInstance()->setStringForKey("CurrentMap", mapName);

}