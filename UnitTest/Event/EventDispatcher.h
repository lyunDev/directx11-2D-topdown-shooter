#pragma once

class EventController
{
private :
	unordered_map<string, vector<function<void(void)>>> m_theRouter;

	vector<string> m_permanentEvents;

public :
	unordered_map<string, vector<function<void(void)>>>& GetRouter()
	{
		return m_theRouter;
	}

	void MarkAsPermanent(string eventType)
	{
		m_permanentEvents.push_back(eventType);
	}

	// 해당 키값이 m_theRouter안에 있는지 확인
	bool ContainsEvent(string eventType)
	{
		for (auto pair : m_theRouter)
		{
			if (pair.first == eventType)
				return true;
		}
		return false;
	}

	void Cleaup()
	{
		vector<string> eventToRemove;

		for (auto pair : m_theRouter)
		{
			bool wasFound = false;
			for (auto Event : m_permanentEvents)
			{
				if (pair.first == Event)
				{
					wasFound = true;
					break;
				}
			}
			if (!wasFound)
				eventToRemove.push_back(pair.first);
		}
		for (auto Event : eventToRemove)
		{
			m_theRouter.erase(Event);
		}
	}

	void AddEventListener(string eventType, function<void(void)> handler)
	{
		auto router = m_theRouter[eventType];
		router.push_back(handler);
		m_theRouter[eventType] = router;
	}

	// 함수 비교가 불가능해서 
	// 특정 함수만 제거할 수 없음
	/*void RemoveEventListener(string eventType, function<void(void)> handler)
	{
		if (ContainsEvent(eventType))
		{
			auto router = m_theRouter[eventType];
			for (int i = 0; i < router.size(); i++)
			{

			}
		}
	}*/


	void TriggerEvent(string eventType)
	{
		vector<function<void(void)>> functionVec;

		if (!ContainsEvent(eventType))
			return;

		auto callbacks = m_theRouter[eventType];
		for (auto callback : callbacks)
		{
			try
			{
				callback();
			}
			catch (exception e)
			{
#ifdef _DEBUG
				cout << "event dispatcher exception : ";
				cout << e.what() << endl;
#endif
				continue;
			}
		}
	}
};

class EventDispatcher
{
public :
	static EventController m_eventController;
	
public :
	static unordered_map < string, vector<function<void(void)>>>& GetRouter()
	{
		return m_eventController.GetRouter();
	}

	static void MarkAsPermanent(string eventType)
	{
		m_eventController.MarkAsPermanent(eventType);
	}

	static void Cleanup()
	{
		m_eventController.Cleaup();
	}

	static void AddEventListener(string eventType, function<void(void)> handler)
	{
		m_eventController.AddEventListener(eventType, handler);
	}

	static void TriggerEvent(string eventType)
	{
#ifdef _DEBUG
		cout << "TriggerEvent : " << eventType << endl;
#endif // _DEBUG
		m_eventController.TriggerEvent(eventType);
	}
};
