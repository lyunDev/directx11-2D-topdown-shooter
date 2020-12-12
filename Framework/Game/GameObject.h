#pragma once
#include "RenderManager.h"
#include"Utilities/Layers.h"
#include "GameObjectManager.h"
class Transform;
class CollisionBox;
class Animator;
class AlphaBuffer;
class DissolveBuffer;
class ColorBuffer;
class GameObject 
{
	friend class GameObjectManager;
	friend class RenderManager;
public :
	GameObject(Vector3 position, Vector3 size, float rotation, bool hasAnimation);
	GameObject(const GameObject& ref) = default;
	virtual ~GameObject();

private:
	void Update();
	void PreRender();
	void Render();
public:
	void SetActive(bool active);
	bool GetActive();
	RenderLayer GetRenderLayer();
	ObjectLayer GetObjectLayer();
	string GetTag()const { return tag; }
	CollisionBox * GetCollisionBox();

	AlphaBuffer * GetAlphaBuffer();
	ColorBuffer * GetColorBuffer();
	DissolveBuffer * GetDissolveBuffer();
	bool IsRigidbody()
	{
		return isRigidbody;
	}
	virtual void Delete()
	{
		GameObjectManager::Get()->DeleteGameObject(this);
	}
protected :
	virtual void OnPreUpdate();
	virtual void OnUpdate(); 
	virtual void OnPostUpdate();
	virtual void OnPreRender();
	virtual void OnRender();
	virtual void OnPostRender();
	void GeometryUpdate();
	// OnPreEnable, OnPreDisable
	// 위 함수를 통해 오브젝트가 나타나기 전 혹은 사라지기 전에
	// 처리하고 싶은 내용을 모두 처리한 후 나타나거나 사라지게 할 수 있다.

	// caution : preEnable을 사용할 경우 반드시
	// 인자 OnSetAcitve를 호출해줄것
	virtual void OnPreEnable(function<void(void)> OnSetActive);
	virtual void OnEnable();
	// caution : preEnable을 사용할 경우 반드시
	// 인자 OnSetAcitve를 호출해줄것
	virtual void OnPreDisable(function<void(void)> OnSetActive);
	virtual void OnDisable();

public :
	virtual void OnCollisionEnter(GameObject* other) 
	{
		if (isRigidbody && other->IsRigidbody() == false)
			other->OnCollisionEnter(this);
	}
	virtual void OnCollisionStay(GameObject* other) 
	{
		if (isRigidbody && other->IsRigidbody() == false)
			other->OnCollisionStay(this);
	}
	virtual void OnCollisionExit(GameObject* other) 
	{
		if (isRigidbody && other->IsRigidbody() == false)
			other->OnCollisionExit(this);
	}

protected :
	void SetDirty(bool dirty);
	bool GetDirty();

	void SetRenderToCollisionBox(bool b);
	void SetSRV(ID3D11ShaderResourceView * srv);
	void SetShader(wstring shaderPath);
	
	void SetCollisionTr(Vector3 * position, Vector3 * scale, float * rotation);
	void SetTag(string tag) { this->tag = tag; }
	

	void SetRenderLayer(RenderLayer renderLayer);
	void SetObjectLayer(ObjectLayer objectLayer);


public :
	ID3D11ShaderResourceView * GetSRV()
	{
		return srv;
	}
	ID3D11ShaderResourceView * GetOriginalSRV()
	{
		return originalSRV;
	}
	Animator * GetAnimator();
	void SetRigidbody(bool isRigidbody)
	{
		this->isRigidbody = isRigidbody;
	}
public :
	class Transform * transform;

private :

private :

	class IntegratedRect * integratedRect = nullptr;
	class AnimationRect* animRect = nullptr;
	class CollisionBox * collisionBox = nullptr;
private :
	bool isDirty = false;
	bool bRenderCollisionBox = false;
	bool isActive = true;
	bool isRigidbody = false;
	string tag = "default";
	ID3D11ShaderResourceView * srv = nullptr;
	ID3D11ShaderResourceView * originalSRV = nullptr; // 최초의 SRV
	 
	RenderLayer renderLayer = RenderLayer::DEFAULT;
	ObjectLayer objectLayer = ObjectLayer::DEFAULT;
};