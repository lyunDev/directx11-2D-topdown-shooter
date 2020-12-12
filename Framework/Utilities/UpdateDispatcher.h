#pragma once

class UpdateDispatcher
{
public :
	static void Dispatch(function<bool(void)> onUpdate, function<void(void)> onCompleted)
	{
		updates.push_back(onUpdate);
		onCompletes.push_back(onCompleted);
	}
	static void Update()
	{
		for (int i = 0; i < updates.size(); i++)
		{
			if (updates[i]() == true) // ³¡
			{
				onCompletes[i]();
				updates.erase(updates.begin() + i);
				onCompletes.erase(onCompletes.begin() + i);
			}
		}

	}

private:
	static vector<function<bool(void)>> updates;
	static vector<function<void(void)>> onCompletes;
};

