#pragma once

class Program : public IObject
{
public :
	virtual void Init() override;
	virtual void Destroy() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void PreRender() override;
	virtual void GUI() override;

private :
	void Push(IObject* obj);
	void Pop(IObject * obj);

	VPBuffer * vpb = nullptr;
	D3DXMATRIX view, proj;
	vector<IObject*> objs;

	class SceneTransition * sceneTransition;
};