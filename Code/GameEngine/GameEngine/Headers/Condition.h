#include <exception>
using namespace std;

#ifndef __Condition_h__
#define __Condition_h__

class Condition;

class Condition
{
	public:

		bool check_condition();
	private:
		int parameter_identifier1;
		int parameter_identifier2;
		char comparison_type;
		int scale1;
		int scale2;
		int addition1;
		int addition2;

};

#endif
