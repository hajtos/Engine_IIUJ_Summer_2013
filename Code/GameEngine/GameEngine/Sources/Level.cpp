#include "Level.h"
#include <exception>
#include <string>
#include <list>
#include <map>

Level::Level(IrrlichtDevice* Device) {
	//Creates a simple, testing Level, more specified constructors to be implemented.
	device = Device;

	driver = device->getVideoDriver();
	smgr = device->getSceneManager();
	guienv = device->getGUIEnvironment();
	
	start = Point(-100, 200, 0);
	size = Point(1200, 900, 5);
	respawn = Point();
	player = new Player(this, 5, 100, 3, Point(0, 20, 0), Point(5, 10, 1),
		0, 0, 0, 100, 90, "ninja", "../media/player/ninja.b3d", Point(0, -5, 0), 0);
	custom_attribute1 = 0;
	custom_attribute2 = 0;
	custom_attribute3 = 0;
	std::map< std::string, Event* > Temp_ed;
	event_dictionary = Temp_ed;
	gravity = 9.81;
	lc_interval = 0;
	delta_time = 0;
	
	std::list<Field*> Temp_f;
	fields = Temp_f;
	fields.insert(fields.end(), player->main_field);
	std::list<Item*> Temp_i;
	items = Temp_i;
	active_range = Point(1200, 900, 2);
	time_left = -1; //forever?
	std::list<Monster*> Temp_m;
	monsters = Temp_m;
	std::list<Border*> Temp_b;
	boundaries = Temp_b;
	
	add_monster("temp1", Point(-10.0, 3.0, 0.0), Point(5.0, 10.0, 1.0));
	add_monster("temp2", Point(10.0, 6.0, 0.0), Point(5.0, 10.0, 1.0));
	add_monster("temp3", Point(20.0, 9.0, 0.0), Point(5.0, 10.0, 1.0));
	add_item("item", Point(15.0, 30.0, 0.0), Point(10.0, 10.0, 1.0));
	for (int i = 0; i < 10; i++)
		add_border(Point(-20 + 10*i, -10, 0), Point(10.0, 10.0, 1.0));
	for (int i = 1; i < 5; i++)
		add_border(Point(30, -10, i), Point(10.0, 10.0, 1.0));
	for (int i = 1; i < 5; i++)
		add_border(Point(30 + 10*i, -10, 4), Point(10.0, 10.0, 1.0));
}

Level::Level(IrrlichtDevice* Device, char* path) {
	//Loads a level from a file
	device = Device;

	driver = device->getVideoDriver();
	smgr = device->getSceneManager();
	guienv = device->getGUIEnvironment();

	//Creating temporary variables
	std::string TempLine = "";
	char animT[15];
	char modelP[30];
	std::string LINE;
	double lineOutput[25];

	//Loading first batch of data
	ifstream infile;
	infile.open(path);
	
	//Starting point
	LINE = getNextRelevantLine(infile);
	extractValues(LINE, lineOutput);
	start = Point(lineOutput[0], lineOutput[1], lineOutput[2]);
	
	//Level Size
	LINE = getNextRelevantLine(infile);
	extractValues(LINE, lineOutput);
	size = Point(lineOutput[0], lineOutput[1], lineOutput[2]);
	
	//Respawn/starting point
	LINE = getNextRelevantLine(infile);
	extractValues(LINE, lineOutput);
	respawn = Point(lineOutput[0], lineOutput[1], lineOutput[2]);
	
	//Custom attributes
	LINE = getNextRelevantLine(infile);
	extractValues(LINE, lineOutput);
	custom_attribute1 = lineOutput[0];
	custom_attribute2 = lineOutput[1];
	custom_attribute3 = lineOutput[2];

	//Gravity
	LINE = getNextRelevantLine(infile);
	extractValues(LINE, lineOutput);
	gravity = lineOutput[0];
	
	//Active range
	LINE = getNextRelevantLine(infile);
	extractValues(LINE, lineOutput);
	active_range = Point(lineOutput[0], lineOutput[1], lineOutput[2]);
	
	//Time left of the level
	LINE = getNextRelevantLine(infile);
	extractValues(LINE, lineOutput);
	time_left = lineOutput[0];
	
	//Initializing generic stuff
	lc_interval = 0;
	delta_time = 0;
	std::list<Field*> Temp_f;
	fields = Temp_f;
	
	//Loading second batch of data
	//Initializing events
	LINE = getNextRelevantLine(infile);
	std::map< std::string, Event* > Temp_ed;
	event_dictionary = Temp_ed;
	extractValues(LINE, lineOutput);
	for (int i = lineOutput[0]; 0 < i; i--)
	{
		LINE = getNextRelevantLine(infile);
		//=================
		// TO DO: Events
		//=================
	}

	//Initializing animation tables
	LINE = getNextRelevantLine(infile);
	std::map< std::string, AnimationTable* > Temp_at;
	animation_tables = Temp_at;
	extractValues(LINE, lineOutput);
	for (int i = lineOutput[0]; 0 < i; i--)
	{
		LINE = getNextRelevantLine(infile);

		//Creating the table
		std::string name = LINE;
		animation_tables.insert(std::pair< std::string, AnimationTable* >(name, new AnimationTable()));
		
		//Filling the table
		for (int j = 0; j < 12; j++)
		{
			LINE = getNextRelevantLine(infile);
			
			extractValues(LINE, lineOutput);
			int total = lineOutput[0];
			animation_tables.find(name)->second->push(j, total, -1);
			getline(infile, LINE);
			extractValues(LINE, lineOutput);
			for (int k = 0; k < total*2; k++)
				animation_tables.find(name)->second->push(j, k, lineOutput[k]);
		}
	}
	
	//Initializing player
	LINE = getNextRelevantLine(infile);
	TempLine = LINE;
	//Transforming std::strings to char arrays (animation table name)
	LINE = getNextRelevantLine(infile);
	for (int i = 0; i < 15; i++)
		animT[i] = 0;
	for (int i = 0; i < LINE.length(); i++)
		animT[i] = LINE[i];
	//Transforming std::strings to char arrays (model path)
	LINE = getNextRelevantLine(infile);
	for (int i = 0; i < 30; i++)
		modelP[i] = 0;
	for(int i = 0; i < LINE.length(); i++)
		modelP[i] = LINE[i];
	//Creating player
	extractValues(TempLine, lineOutput);
	player = new Player(this, lineOutput[0], lineOutput[1], lineOutput[2], //movement speed, hit points, lives
		Point(lineOutput[3], lineOutput[4], lineOutput[5]), //starting point
		Point(lineOutput[6], lineOutput[7], lineOutput[8]), //size
		lineOutput[9], lineOutput[10], lineOutput[11], //custom values
		lineOutput[12], lineOutput[13], animT, modelP, //gravity degree, fancing angle
		Point(lineOutput[14], lineOutput[15], lineOutput[16]), lineOutput[17]); //translation, animated?

	fields.insert(fields.end(), player->main_field);
	//Loading animator state
	LINE = getNextRelevantLine(infile);
	extractValues(LINE, lineOutput);
	if (lineOutput[0]) //if set is needed, else go with default
		player->animator->set(lineOutput[1], lineOutput[2], //bool active, bool looping
			lineOutput[3], lineOutput[4], //animation id, animation speed
			lineOutput[5], lineOutput[6], lineOutput[7]); //current frame, min frame, max frame

	//Initializing items
	LINE = getNextRelevantLine(infile);
	std::list<Item*> Temp_i;
	items = Temp_i;
	extractValues(LINE, lineOutput);
	for (int i = lineOutput[0]; 0 < i; i--)
	{
		LINE = getNextRelevantLine(infile);
		TempLine = LINE;
		//Transforming std::strings to char arrays (animation table name)
		LINE = getNextRelevantLine(infile);
		for (int i = 0; i < 15; i++)
			animT[i] = 0;
		for (int i = 0; i < LINE.length(); i++)
			animT[i] = LINE[i];
		//Transforming std::strings to char arrays (model path)
		LINE = getNextRelevantLine(infile);
		for (int i = 0; i < 30; i++)
			modelP[i] = 0;
		for(int i = 0; i < LINE.length(); i++)
			modelP[i] = LINE[i];
		
		//Creating item
		extractValues(TempLine, lineOutput);
		Item* p = new Item(this, lineOutput[0], //movement speed
			Point(lineOutput[1], lineOutput[2], lineOutput[3]), //position
			Point(lineOutput[4], lineOutput[5], lineOutput[6]), //size
			lineOutput[7], lineOutput[8], lineOutput[9], lineOutput[10], //custom attributes, gravity degree
			lineOutput[11], animT, modelP, //facing angle, animation table, model path
			Point(lineOutput[12], lineOutput[13], lineOutput[14]), //translation
			lineOutput[15], lineOutput[16], lineOutput[17], lineOutput[18]); //animated?, life time, active, always active
		fields.insert(fields.end(), p->main_field);
		items.insert(items.end(), p);

		//Loading animator state
		LINE = getNextRelevantLine(infile);
		extractValues(LINE, lineOutput);
		if (lineOutput[0]) //if set is needed, else go with default
			p->animator->set(lineOutput[1], lineOutput[2], //bool active, bool looping
				lineOutput[3], lineOutput[4], //animation id, animation speed
				lineOutput[5], lineOutput[6], lineOutput[7]); //current frame, min frame, max frame
	}
	
	//Initializing monsters
	LINE = getNextRelevantLine(infile);
	std::list<Monster*> Temp_m;
	monsters = Temp_m;
	extractValues(LINE, lineOutput);
	for (int i = lineOutput[0]; 0 < i; i--)
	{
		std::string lineName;
		std::string lineMonsterType;
		LINE = getNextRelevantLine(infile);
		TempLine = LINE;
		//Transforming std::strings to char arrays (animation table name)
		LINE = getNextRelevantLine(infile);
		for (int i = 0; i < 15; i++)
			animT[i] = 0;
		for (int i = 0; i < LINE.length(); i++)
			animT[i] = LINE[i];
		//Transforming std::strings to char arrays (model path)
		LINE = getNextRelevantLine(infile);
		for (int i = 0; i < 30; i++)
			modelP[i] = 0;
		for(int i = 0; i < LINE.length(); i++)
			modelP[i] = LINE[i];
		//Getting monster name and type
		lineName = getNextRelevantLine(infile);
		lineMonsterType = getNextRelevantLine(infile);

		extractValues(TempLine, lineOutput);
		Monster* m = new Monster(this, lineOutput[0], lineOutput[1], //movement speed, hit points
			lineName, lineMonsterType, //name, monster type,
			Point(lineOutput[2], lineOutput[3], lineOutput[4]), //position
			Point(lineOutput[5], lineOutput[6], lineOutput[7]), //size
			lineOutput[8], lineOutput[9], lineOutput[10], lineOutput[11], //custom attributes, gravity degree
			lineOutput[12], animT, modelP, //facing angle, animation table, model path
			Point(lineOutput[13], lineOutput[14], lineOutput[15]), //translation
			lineOutput[16], lineOutput[17], lineOutput[18], lineOutput[19]); //animated?, life time, active, always active
		fields.insert(fields.end(), m->main_field);
		monsters.insert(monsters.end(), m);
		
		//Loading animator state
		LINE = getNextRelevantLine(infile);
		extractValues(LINE, lineOutput);
		if (lineOutput[0]) //if set is needed, else go with default
			m->animator->set(lineOutput[1], lineOutput[2], //bool active, bool looping
				lineOutput[3], lineOutput[4], //animation id, animation speed
				lineOutput[5], lineOutput[6], lineOutput[7]); //current frame, min frame, max frame
	}
	
	//Initializing Borders
	LINE = getNextRelevantLine(infile);
	std::list<Border*> Temp_b;
	boundaries = Temp_b;
	extractValues(LINE, lineOutput);
	for (int i = lineOutput[0]; 0 < i; i--)
	{
		LINE = getNextRelevantLine(infile);
		TempLine = LINE;
		//Transforming std::strings to char arrays (animation table name)
		LINE = getNextRelevantLine(infile);
		for (int i = 0; i < 15; i++)
			animT[i] = 0;
		for (int i = 0; i < LINE.length(); i++)
			animT[i] = LINE[i];
		//Transforming std::strings to char arrays (model path)
		LINE = getNextRelevantLine(infile);
		for (int i = 0; i < 30; i++)
			modelP[i] = 0;
		for(int i = 0; i < LINE.length(); i++)
			modelP[i] = LINE[i];
		
		//Creating border
		extractValues(TempLine, lineOutput);
		Border* b = new Border(this, lineOutput[0], lineOutput[1], lineOutput[2], //movement speed, absolute, bouncing
			Point(lineOutput[3], lineOutput[4], lineOutput[5]), //position
			Point(lineOutput[6], lineOutput[7], lineOutput[8]), //size
			lineOutput[9], lineOutput[10], lineOutput[11], lineOutput[12], //custom attributes, gravity degree
			lineOutput[13], lineOutput[14], animT, modelP, //facing angle, model type, animation table, model path
			Point(lineOutput[15], lineOutput[16], lineOutput[17]), //translation
			lineOutput[18], lineOutput[19], lineOutput[20], lineOutput[21]); //animated?, life time, active, always active
		fields.insert(fields.end(), b->main_field);
		boundaries.insert(boundaries.end(), b);

		//Loading animator state
		LINE = getNextRelevantLine(infile);
		extractValues(LINE, lineOutput);
		if (lineOutput[0]) //if set is needed, else go with default
			b->animator->set(lineOutput[1], lineOutput[2], //bool active, bool looping
				lineOutput[3], lineOutput[4], //animation id, animation speed
				lineOutput[5], lineOutput[6], lineOutput[7]); //current frame, min frame, max frame
	}
	infile.close();
}

void Level::add_event(std::string init) {
	throw "Not yet implemented";
}

void Level::add_border(Point start, Point size) {
	//Border* b = new Border(start, size, this);
	//fields.insert(fields.end(), b->main_field);
	//boundaries.insert(boundaries.end(), b);
}

void Level::add_monster(std::string init, Point position, Point size) {
	//Monster* m = new Monster(init, this, position, size);
	//fields.insert(fields.end(), m->main_field);
	//monsters.insert(monsters.end(), m);
}

void Level::add_item(std::string init, Point position, Point size) {
	//Item* i = new Item(init, this, position, size);
	//fields.insert(fields.end(), i->main_field);
	//items.insert(items.end(), i);
}

void Level::advance_frame(ICameraSceneNode *cam) {
	//Updating positions/scales/rotations:
	for (std::list<Field*>::iterator i = fields.begin(); i != fields.end(); i++)
		(*i)->update();
	//clearing garbage
	for (std::list<Field*>::iterator i = garbage.begin(); i != garbage.end(); i++)
		if ((*i)->owner != 0)
			(*i)->owner->remove();
		else {
			fields.remove(*i);
			delete(*i);
		}
	garbage.clear();
	
	//centralizing camera on player (if exists)
	if (player != 0 && cam != 0) {
		//position
		cam->setPosition(core::vector3df(player->main_field->position.position_x,
			player->main_field->position.position_y+15,(player->main_field->position.layer-1)*10-40));
		//target
		cam->setTarget(core::vector3df(player->main_field->position.position_x,
			player->main_field->position.position_y,(player->main_field->position.layer-1)*10));
	}

	//handling player velocity changes and animation
	if (!player->main_field->velocity->finished())
	{
		if (player->animator->getAnimation() != 0)
			player->animator->setAnimation(0);
	}
	else
	{
		if (player->animator->getAnimation() != 1)
			player->animator->setAnimation(1);
	}

	//Handling player grounding
	player->main_field->position.position_y -= 1.0;
	//if (collision_detect(player->main_field))
	//	player->grounded = true;
	//else player->grounded = false;
	player->main_field->position.position_y += 1.0;
	//if (player->grounded)
	//	player->main_field->velocity.position_x = 0;
	//player->main_field->velocity.position_y = 0; //player->main_field->get_vy()

	//decrementing layer change delay
	if (lc_interval > 0)
		lc_interval--;
}

void Level::collision_detect() {
	std::list<Field*>::iterator target = fields.begin();
	while (target != fields.end())
	{
		std::list<Field*>::iterator finding = target;
		++finding;
		Point nextPos1 = (*target)->velocity->nextPos(&(*target)->position);
		Point nextPos2 = (*finding)->velocity->nextPos(&(*finding)->position);
		Point edge = (*target)->shape->edge()+nextPos1;
		while (edge.layer > nextPos2.layer || edge.position_x > nextPos2.position_x) {
			if ((*target)->shape->collidesWith((*finding)->shape,nextPos2-nextPos1)) {
				if ((*finding)->collision_effect && (*target)->owner && (*target)->owner->get_type()&(*finding)->type) {
					if ((*finding)->collision_effect->blocking) {
						do {
							(*target)->velocity->flatten(Point(0,0,1));
							nextPos1 = (*target)->velocity->nextPos(&(*target)->position);
						} while ((*target)->shape->collidesWith((*finding)->shape,nextPos2-nextPos1));
					}
					(*finding)->collision_effect->invokeEvent(*finding,*target);

				}
			}
			++finding;
		}
		/*
		//Checking for redundant comparisons (different z levels, source-source)
		if (source->position.layer < ((*target)->position.layer - (*target)->size.layer / 2))
		{
			++target;
			continue;
		}
		if (((*target)->position.layer + (*target)->size.layer / 2) < source->position.layer)
		{
			++target;
			continue;
		}
		if ((*target) == source)
		{
			++target;
			continue;
		}
		//Vefining values for further usage
		bool collided = false;

		double tx1 = (*target)->position.position_x - (*target)->size.position_x / 2;
		double tx2 = (*target)->position.position_x + (*target)->size.position_x / 2;
		double ty1 = (*target)->position.position_y - (*target)->size.position_y / 2;
		double ty2 = (*target)->position.position_y + (*target)->size.position_y / 2;

		double sx1 = source->position.position_x - source->size.position_x / 2;
		double sx2 = source->position.position_x + source->size.position_x / 2;
		double sy1 = source->position.position_y - source->size.position_y / 2;
		double sy2 = source->position.position_y + source->size.position_y / 2;

		//Collision is detected corner wise, checking if any of the 4 corners is inside of other object
		//Checking target inside source (vertical collision)
		if (sx1 <= tx1 && tx1 <= sx2)
		{
			if (sy1 <= ty1 && ty1 <= sy2)
				collided = true;
			if (sy1 <= ty2 && ty2 <= sy2)
				collided = true;
		}
		if (sx1 <= tx2 && tx2 <= sx2)
		{
			if (sy1 <= ty1 && ty1 <= sy2)
				collided = true;
			if (sy1 <= ty2 && ty2 <= sy2)
				collided = true;
		}
		//Checking source inside target (horizontal collision)
		if (tx1 < sx1 && sx1 < tx2)
		{
			if (ty1 < sy1 && sy1 < ty2)
				collided = true;
			if (ty1 < sy2 && sy2 < ty2)
				collided = true;
		}
		if (tx1 < sx2 && sx2 < tx2)
		{
			if (ty1 < sy1 && sy1 < ty2)
				collided = true;
			if (ty1 < sy2 && sy2 < ty2)
				collided = true;
		}
		
		//Handling collision (if any)
		if (collided)
		{
			if (source->owner!=NULL && ((source->owner)->get_type())&((*target)->type))
			{
						if((*target)->collision_effect!=NULL)
							(*target)->collision_effect->invokeEvent(*target,source);
			}
			if ((*target)->owner!=NULL && (((*target)->owner)->get_type())&(source->type))
			{
						if (source->collision_effect!=NULL)
							source->collision_effect->invokeEvent(source,*target);
			}
			p = true;
		}
		++target;*/
	}
}

void Level::move_field(Field* field) {
	field->position = field->velocity->nextPos(&field->position);
}

void Level::remove_player(Field* field) {
	if (field == 0)
		return;
	//Removing entity:
	if (player != 0) {
		delete(player);
		player = 0;
	}
	//Removing field:
	fields.remove(field);
	delete(field);
}

void Level::remove_border(Field* field, Border* entity) {
	if (field == 0)
		return;
	//Removing entity:
	if (player != 0) {
		boundaries.remove(entity);
		delete(entity);
	}
	//Removing field:
	fields.remove(field);
	delete(field);
}

void Level::remove_monster(Field* field, Monster* entity) {
	if (field == 0)
		return;
	//Removing entity:
	if (player != 0) {
		monsters.remove(entity);
		delete(entity);
	}
	//Removing field:
	fields.remove(field);
	delete(field);
}

void Level::remove_item(Field* field, Item* entity) {
	if (field == 0)
		return;
	//Removing entity:
	if (player != 0) {
		items.remove(entity);
		delete(entity);
	}
	//Removing field:
	fields.remove(field);
	delete(field);
}

void Level::trash(Field* field) {
	//field->destroy_event.invoke() ??
	garbage.insert(garbage.end(), field);
}

void Level::process_key(irr::EKEY_CODE keycode) {
	if (player == 0)
		return;
	if (keycode == irr::KEY_KEY_W)
		if (player->grounded)
			player->main_field->velocity = new StraightVelocity(0,player->movement_speed*2,0,-1);
	/*
	if (keycode == irr::KEY_KEY_S)
		if (player->grounded)
			player->main_field->velocity.position_y = -player->movement_speed*2;
	*/
	if (keycode == irr::KEY_KEY_D)
	{
		if (player->grounded)
		{
			player->facing_angle = 90;
			player->main_field->velocity = new StraightVelocity(player->movement_speed,0,0,-1);
		}
	}
	if (keycode == irr::KEY_KEY_A)
	{
		if (player->grounded)
		{
			player->facing_angle = 270;
			player->main_field->velocity = new StraightVelocity(-player->movement_speed,0,0,-1);
		}
	}
	if (keycode == irr::KEY_KEY_Q)
	{
		if (!player->main_field->velocity->grounded())
			return;
		if (lc_interval != 0)
			return;
		lc_interval = 30;
		player->main_field->velocity = new StraightVelocity(0,0,1,1);
	}
	if (keycode == irr::KEY_KEY_Z)
	{
		if (!player->main_field->velocity->grounded())
			return;
		if (lc_interval != 0)
			return;
		lc_interval = 30;
		player->main_field->velocity = new StraightVelocity(0,0,-1,1);
	}
}

inline std::string Level::getNextRelevantLine(ifstream& infile) {
	std::string ans = "";
	getline(infile, ans);
	//Skipping non-relevant lines
	while (ans.empty() || ans[0] == '#') //empty spacing line or comment
		getline(infile, ans);
	return ans;
}

void Level::extractValues(std::string source, double* output) {
	int n = 0;
	int i = 0;
	bool negative = false;
	double ans = 0.0;
	int decimal = 0;
	while (i < source.length())
	{
		if (source[i] == '-')
			negative = true;
		else
			if (source[i] == '.')
				decimal = 10;
			else
				if (source[i] != ' ')
				{
					if (decimal == 0)
						ans = ans*10 + source[i] - 48; //non-decimal
					else
					{
						//decimal
						ans += (source[i] - 48)/decimal;
						decimal *= 10;
					}
				}
				else
				{
					//Negative/positive and reset
					if (!negative)
						output[n++] = ans;
					else output[n++] = -ans;
					negative = false;
					ans = 0.0;
				}
		i++;
	}
	//Adding last value
	if (!negative)
		output[n++] = ans;
	else output[n++] = -ans;
}