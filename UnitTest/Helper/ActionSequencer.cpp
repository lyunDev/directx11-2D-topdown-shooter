#include "stdafx.h"
#include "ActionSequencer.h"

ActionSequencer::ActionSequencer()
{
}

ActionSequencer::~ActionSequencer()
{
}

void ActionSequencer::Update()
{
	if (actionQueue.size() > 0)
	{
		bool isCompleted = actionQueue.front()();
		if (isCompleted)
			actionQueue.pop();
	}
}

void ActionSequencer::AddAction( function<bool(void)> action)
{
	actionQueue.push(action);
}
