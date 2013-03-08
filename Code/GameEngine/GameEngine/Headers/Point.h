
#ifndef __Point_h__
#define __Point_h__

class Point;

class Point
{
	public:
		float position_x;
		float position_y;
		float layer;

		Point(float a,float b, float c);
		Point();
	friend Point operator+(Point a,Point b){
		Point p;
		p.layer = a.layer+b.layer;
		p.position_x = a.position_x+b.position_x;
		p.position_y = a.position_y+b.position_y;
		return p;
	}
	
	friend Point operator-(Point a,Point b){
		Point p;
		p.layer = a.layer-b.layer;
		p.position_x = a.position_x-b.position_x;
		p.position_y = a.position_y-b.position_y;
		return p;
	}

	friend Point operator*(Point a,float b){
		Point p;
		p.layer = a.layer*b;
		p.position_x = a.position_x*b;
		p.position_y = a.position_y*b;
		return p;
	}

	friend bool operator<(Point a,Point b){
		if (a.layer<b.layer)
			return true;
		if (a.layer>b.layer)
			return false;
		return a.position_x<b.position_x;
	}
};

#endif
