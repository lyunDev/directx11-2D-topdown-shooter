#pragma once
#include <queue>

class ActionSequencer
{
public :
	ActionSequencer();
	~ActionSequencer();

	void Update();

	void AddAction(function<bool(void)> action);
private :
	std::queue<function<bool(void)>>  actionQueue;
};