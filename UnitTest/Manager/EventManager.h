#pragma once

class EventManager : public SingletonBase<EventManager>
{
	friend class SingletonBase<EventManager>;
public :
	void Update();

	void BossCaution(void);
	void KillBoss();
	void KillEnemy();
	void DiePlayer();
private :
	EventManager();
	~EventManager();
	float currentTime = 0;
	bool bBossCaution = false;
};