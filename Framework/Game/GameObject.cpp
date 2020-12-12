#include "Framework.h"
#include "GameObject.h"
#include "Transform.h"
#include "Geometries/TextureRect.h"
#include "Geometries/AnimationRect.h"
#include "Geometries/IntegratedRect.h"
#include "Utilities/CollisionBox.h"
#include "Geometries/Rect.h"
#include "Utilities/Animator.h"
#include "GameObjectManager.h"
#include "Effects/Dissolve.h"
#include "ShaderBuffers/AlphaBuffer.h"
#include "ShaderBuffers/ColorBuffer.h"



GameObject::GameObject(Vector3 position, Vector3 size, float rotation, bool hasAnimation)
{
	transform = new Transform();
	transform->position = position;
	transform->size = size;
	transform->rotation = rotation;

	collisionBox = new CollisionBox(&this->transform->position, &this->transform->size, &this->transform->rotation);

	if (hasAnimation)
	{
		// animRect 사용
		// TODO
		animRect = new AnimationRect(transform);
	}
	else
	{
		// textureRect 사용
		integratedRect = new IntegratedRect(transform);

	}
	// Push GameObjectManager
	GameObjectManager::Get()->PushGameObject(this);
	RenderManager::Get()->PushRenderable(this);
}

GameObject::~GameObject()
{
	GameObjectManager::Get()->PopGameObject(this);
	RenderManager::Get()->PopRenderable(this);
	SAFE_DELETE(transform);
	SAFE_DELETE(integratedRect);
	SAFE_DELETE(animRect);
}

void GameObject::Update()
{
	OnPreUpdate();





	

	OnUpdate();

	GeometryUpdate();

	OnPostUpdate();
}

void GameObject::PreRender()
{
	OnPreRender();
}

void GameObject::Render()
{

	OnRender();
	if (isActive == false)
		return;
	if (integratedRect)
		integratedRect->Render();
	if (animRect)
		animRect->Render();

	if (bRenderCollisionBox)
		collisionBox->Render();

	


	OnPostRender();
}

void GameObject::OnPreUpdate()
{
}

void GameObject::OnUpdate()
{
}

void GameObject::OnPostUpdate()
{
}

void GameObject::OnPreRender()
{
}

void GameObject::OnRender()
{
}

void GameObject::OnPostRender()
{
}

void GameObject::GeometryUpdate()
{
	if (integratedRect)
		integratedRect->Update();
	if (animRect)
		animRect->Update();
	if (bRenderCollisionBox)
		collisionBox->Update();
}

void GameObject::OnPreEnable(function<void(void)> OnSetActive)
{
	OnSetActive();
}

void GameObject::OnEnable()
{
}

void GameObject::OnPreDisable(function<void(void)> OnSetActive)
{
	OnSetActive();
}

void GameObject::OnDisable()
{
}



void GameObject::SetDirty(bool dirty)
{
	isDirty = dirty;
}

bool GameObject::GetDirty()
{
	return isDirty;
}

CollisionBox * GameObject::GetCollisionBox()
{
	return collisionBox;
}

AlphaBuffer * GameObject::GetAlphaBuffer()
{
	if (integratedRect)
		return integratedRect->alphaBuffer;
	if (animRect)
		return animRect->alphaBuffer;
}

ColorBuffer * GameObject::GetColorBuffer()
{
	if (integratedRect)
		return integratedRect->colorBuffer;
	if (animRect)
		return animRect->colorBuffer;
}

DissolveBuffer * GameObject::GetDissolveBuffer()
{
	if (integratedRect)
		return integratedRect->dissolveBuffer;
	if (animRect)
		return animRect->dissolveBuffer;
}

void GameObject::SetRenderToCollisionBox(bool b)
{
	bRenderCollisionBox = b;
}


void GameObject::SetSRV(ID3D11ShaderResourceView * srv)
{
	if (this->originalSRV == nullptr)
		originalSRV = srv;
	this->srv = srv;
	if(integratedRect)
		integratedRect->SetSRV(srv);
	if (animRect)
		animRect->SetSRV(srv);
}

void GameObject::SetShader(wstring shaderPath)
{
	if(integratedRect)
		integratedRect->SetShader(shaderPath);
	if (animRect)
		animRect->SetShader(shaderPath);
}

void GameObject::SetActive(bool active)
{
	if (isActive != active && active == true)
	{
		OnPreEnable([&]() 
		{
			isActive = active; 
			OnEnable();
		});
	}
	if (isActive != active && active == false)
	{
		OnPreDisable([&]()
		{
			isActive = active;
			OnDisable();
		});
	}
}

bool GameObject::GetActive()
{
	return isActive;
}

void GameObject::SetCollisionTr(Vector3 * position, Vector3 * scale , float * rotation)
{
	collisionBox->SetTransform(position, scale, rotation);
}

void GameObject::SetRenderLayer(RenderLayer renderLayer)
{
	this->renderLayer = renderLayer;
	RenderManager::Get()->SortRenderable();
}

void GameObject::SetObjectLayer(ObjectLayer objectLayer)
{
	this->objectLayer = objectLayer;
	GameObjectManager::Get()->LayerChanged();
}

RenderLayer GameObject::GetRenderLayer() { return this->renderLayer; }

ObjectLayer GameObject::GetObjectLayer()
{
	return objectLayer;
}
Animator * GameObject::GetAnimator()
{
	if (animRect)
		return animRect->animator;
	return nullptr;
}
//void GameObject::SyncTransform()
//{
//	/*if(texture)
//		texture->SyncTransform(transform->position, transform->size, transform->rotation);*/
//	// TODO : Anim
//	
//	gizmo->SyncTransform(transform->position, transform->size, transform->rotation);
//
//}
