#pragma once


enum class RenderLayer
{
	BACKGROUND = 10,
	PROJECTILE = 13,
	GAMEOBJECT = 15,
	BLOOM = 16,
	ENEMY = 14,
	DEFAULT = 20,
	UI = 50,
	UI2 = 51,
};

class GameObject;
class RenderManager : public SingletonBase<RenderManager>
{
public :
	friend class SingletonBase<RenderManager>;

	void PushRenderable(GameObject* gameObject);
	void PopRenderable(GameObject* gameObject);
	void PreRender();
	void Render();
	void SortRenderable();
private :
	RenderManager();
	~RenderManager();
private :
	vector<GameObject*> renderables;
};