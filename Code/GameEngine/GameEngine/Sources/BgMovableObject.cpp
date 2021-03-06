#include "BgMovableObject.h"
#include <exception>

BgMovableObject::BgMovableObject(IrrlichtDevice* Device, vector3df scale, Point position, char* TexturePath, int t){

	type = t;
	IVideoDriver* driver = Device->getVideoDriver();
	ISceneManager* smgr = Device->getSceneManager();

	graphic_model= smgr->addCubeSceneNode();
	graphic_model->setMaterialFlag(video::EMF_LIGHTING, true);
	graphic_model->setMaterialTexture(0, driver->getTexture(TexturePath));
	graphic_model->setMaterialFlag(video::EMF_LIGHTING, false);
		
	graphic_model->setPosition(core::vector3df(position.position_x, position.position_y, position.layer));
	graphic_model->setScale(scale);
	graphic_model->setMaterialType(video::EMT_TRANSPARENT_ALPHA_CHANNEL);
}

void BgMovableObject::move(){
	switch(type){
		case 1:	
				if (graphic_model->getPosition().X > -500)
					graphic_model->setPosition(graphic_model->getPosition() - vector3df(0.5, 0, 0)); 
				else
					graphic_model->setPosition(vector3df(500, graphic_model->getPosition().Y, graphic_model->getPosition().Z));
				break;
		case 2:
				if (graphic_model->getPosition().X > -500){
					if (graphic_model->getPosition().Y > -100)
						graphic_model->setPosition(graphic_model->getPosition() - vector3df(0.2, 0.2, 0)); 
					else
						graphic_model->setPosition(vector3df(graphic_model->getPosition().X, 100, graphic_model->getPosition().Z));
				}else
					graphic_model->setPosition(vector3df(500, graphic_model->getPosition().Y, graphic_model->getPosition().Z));
				break;
	}			

}
