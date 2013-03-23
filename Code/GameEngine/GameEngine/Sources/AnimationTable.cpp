#include "AnimationTable.h"

AnimationTable::~AnimationTable() {
	for (int i = 0; i < 12; i++)
		free(animation[i]);
}

AnimationTable::AnimationTable() {
	for (int i = 0; i < 12; i++)
		animation[i] = 0;
}

void AnimationTable::push(int id, int n, int value) {
	if (value < 0)
	{
		animation[id] = (int*)malloc(2*n*sizeof(int));
		size[id] = n;
	}
	else
		animation[id][n] = value;
}