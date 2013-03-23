///Includes
#include <irrlicht.h>
#include <Level.h>
#include <Background.h>
///Namespaces
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;
///Defs
#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

///Class Declarations
class KeyReciever : public IEventReceiver
{
public:
	virtual bool OnEvent(const SEvent& event) {
		if (event.EventType == irr::EET_KEY_INPUT_EVENT)
			KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;

		return false;
	}

	virtual bool IsKeyDown(EKEY_CODE keyCode) const {
		return KeyIsDown[keyCode];
	}
	
	KeyReciever() {
		for (u32 i=0; i<KEY_KEY_CODES_COUNT; ++i)
			KeyIsDown[i] = false;
	}

private:
	bool KeyIsDown[KEY_KEY_CODES_COUNT];
};

///Program Startup
int main()
{
	KeyReciever receiver;

	///Creating Game Window
	IrrlichtDevice *device =
		createDevice( video::EDT_OPENGL, dimension2d<u32>(800, 600), 16,
			false, false, false, &receiver);

	if (!device)
		return 1;

	device->setWindowCaption(L"Game Engine Demo");

	IVideoDriver* driver = device->getVideoDriver();
	ISceneManager* smgr = device->getSceneManager();
	IGUIEnvironment* guienv = device->getGUIEnvironment();
	
	//ICameraSceneNode *cam = smgr->addCameraSceneNode(0, vector3df(0,30,0), vector3df(0,0,0));
	ICameraSceneNode *cam = smgr->addCameraSceneNode(0, vector3df(0,15,-40), vector3df(0,0,0));

	///Creating level (From file, yay!)
	Level L = Level(device, "../Init/level1.ini");


	Background tlo_niebo;
	tlo_niebo = Background(vector3df(500,350,0), vector3df(1,1,1000), false, "../media/environment/sky16.JPG", 0.1, 1.0, device, L);

	Background tlo_drzewa;
	tlo_drzewa = Background(vector3df(20,10,0), vector3df(-300,1,300), true, "../media/environment/trees.png", 0.5, 3.1, device, L);

	Background tlo_plaza;
	tlo_plaza = Background(vector3df(800,200,0), vector3df(1,-1000,600), false, "../media/environment/beach.jpg", 5.1, 10.1, device, L);


	f32 FrameInterval = 1.0/60.0;
	u32 t2 = device->getTimer()->getTime();

	///Running the Game
	while(device->run())
	{
		if (device->isWindowActive())
		{
			u32 t1 = device->getTimer()->getTime();
			f32 frameDeltaTime = (f32)(t1 - t2) / 1000.f; // Time in seconds
			if (FrameInterval <= frameDeltaTime)
			{
				//Updating Time
				t2 = t1;
				driver->beginScene(true, true, SColor(255,100,101,140));
				L.delta_time = (frameDeltaTime < 3*FrameInterval) ? frameDeltaTime : 3*FrameInterval; //min, deltaTime or 3 frames
				
				//Handling Keys
				if(receiver.IsKeyDown(irr::KEY_KEY_W))
					L.process_key(irr::KEY_KEY_W);
				else if(receiver.IsKeyDown(irr::KEY_KEY_S))
					L.process_key(irr::KEY_KEY_S);
				if(receiver.IsKeyDown(irr::KEY_KEY_D)) {
					L.process_key(irr::KEY_KEY_D);
					tlo_niebo.moveLeft();
					tlo_drzewa.moveLeft();
					tlo_plaza.moveLeft();
				}
				else if(receiver.IsKeyDown(irr::KEY_KEY_A)) {
					L.process_key(irr::KEY_KEY_A);
					tlo_niebo.moveRight();
					tlo_drzewa.moveRight();
					tlo_plaza.moveRight();
				}
				else if(receiver.IsKeyDown(irr::KEY_KEY_Q)) {
					L.process_key(irr::KEY_KEY_Q);
					tlo_niebo.moveInwards();
					tlo_drzewa.moveOutwards();
					tlo_plaza.moveOutwards();
				}
				else if(receiver.IsKeyDown(irr::KEY_KEY_Z)) {
					L.process_key(irr::KEY_KEY_Z);
					tlo_niebo.moveOutwards();
					tlo_drzewa.moveInwards();
					tlo_plaza.moveInwards();
				}

				//Updating Level
				L.advance_frame(cam);

				smgr->drawAll();
				guienv->drawAll();

				driver->endScene();
			}
		}
	}
	device->drop();
	return 0;
}
