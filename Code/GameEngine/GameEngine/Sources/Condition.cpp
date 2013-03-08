#include <exception>
using namespace std;

#include "Condition.h"
bool Condition::check_condition() {
	int a=0,b=0;
	//tu bedzie jakis switch z wieloma opcjami przypisujacy a i b w zaleznosci od parameter_identifier1 i 2
	a = a*scale1+addition1;
	b = b*scale2+addition2;
	switch(comparison_type) {
		case'=':return a==b;
			break;
		case'<':return a<b;
			break;
		case'>':return a>b;
			break;
		case',':return a<=b;
			break;
		case'.':return a>=b;
			break;
		default: return true;
	}
}
