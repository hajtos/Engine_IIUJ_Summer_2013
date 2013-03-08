#include "Cloud.h"
#include <exception>

Cloud::Cloud(IrrlichtDevice* Device, Point position){

	IVideoDriver* driver = Device->getVideoDriver();
	ISceneManager* smgr = Device->getSceneManager();
	IGUIEnvironment* guienv = Device->getGUIEnvironment();

	graphic_model= smgr->addCubeSceneNode();
	graphic_model->setMaterialFlag(video::EMF_LIGHTING, true);
	graphic_model->setMaterialTexture(0, driver->getTexture("../media/environment/cloud.png"));
	graphic_model->setMaterialFlag(video::EMF_LIGHTING, false);
		
	graphic_model->setPosition(core::vector3df(position.position_x, position.position_y, position.layer));
	graphic_model->setScale(core::vector3df(25,5,0));
	graphic_model->setMaterialType(video::EMT_TRANSPARENT_ALPHA_CHANNEL);
}

void Cloud::cloud_move(){
	if (graphic_model->getPosition().X > -500)
		graphic_model->setPosition(graphic_model->getPosition() - vector3df(0.5, 0, 0)); 
	else
		graphic_model->setPosition(vector3df(500, graphic_model->getPosition().Y, graphic_model->getPosition().Z));
}