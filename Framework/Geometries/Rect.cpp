#include "Framework.h"

#include "Rect.h"

// AABB
// Axis aligned bounding box

Rect::Rect(Vector3 position, Vector3 size, float rotation)
	: position(position), size(size), rotation(rotation)
{

	//vertices

	{

		vertices.assign(4, VertexColor());



		vertices[0].position = D3DXVECTOR3(-0.5f, -0.5f, 0.0f); // left bottom

		vertices[0].color = Color(1, 0, 0, 1);



		vertices[1].position = D3DXVECTOR3(-0.5f, 0.5f, 0.0f); // left top

		vertices[1].color = Color(1, 0, 0, 1);



		vertices[2].position = D3DXVECTOR3(0.5f, -0.5f, 0.0f); // right bottom

		vertices[2].color = Color(1, 0, 0, 1);



		vertices[3].position = D3DXVECTOR3(0.5f, 0.5f, 0.0f); // right top

		vertices[3].color = Color(1, 0, 0, 1);

	}



	//vertexBuffer

	{
		vb = new VertexBuffer();

		vb->Create(vertices, D3D11_USAGE_DYNAMIC);
	}



	//indexBuffer

	{

		indices = { 0, 1, 2, 2, 1, 3 };



		ib = new IndexBuffer();

		ib->Create(indices, D3D11_USAGE_IMMUTABLE);

	}



	//vertexShader

	{

		vs = new VertexShader();

		vs->Create(ShaderPath + L"VertexColor.hlsl", "VS");
	}



	//inputLayout

	{

		il = new InputLayout();

		il->Create(VertexColor::descs, VertexColor::count, vs->GetBlob());

	}



	//pixelShader

	{

		ps = new PixelShader();

		ps->Create(ShaderPath + L"VertexColor.hlsl", "PS");

	}
	D3D11_BLEND_DESC desc;
	States::GetBlendDesc(&desc);
	// 블렌드 적용 안되는 BlendState
	States::CreateBlend(&desc, &blendState[0]); 

	// 블렌드 적용 되는 BlendState
	desc.RenderTarget[0].BlendEnable = true;
	States::CreateBlend(&desc, &blendState[1]);

	wb = new WorldBuffer();

	UpdateWorld();
	//box = new BoundingBox(&edge);
	//box->Init();
}



Rect::~Rect()
{
	//SAFE_DELETE(box);

	SAFE_RELEASE(blendState[1]);
	SAFE_RELEASE(blendState[0]);
	SAFE_DELETE(wb);



	SAFE_DELETE(ps);



	SAFE_DELETE(il);



	SAFE_DELETE(vs);



	SAFE_DELETE(ib);

	SAFE_DELETE(vb);

}



void Rect::Update()
{
	UpdateWorld();
	//box->Update();
}



void Rect::Render()
{
	vb->SetIA();
	ib->SetIA();
	il->SetIA();
	DC->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	vs->SetShader();

	wb->SetVSBuffer(0); // set constant buffer (transform buffer)

	ps->SetShader();

	DC->OMSetBlendState(blendState[0], nullptr, 0xFFFFFFFF);
	DC->DrawIndexed(ib->GetCount(), 0, 0);
	DC->OMSetBlendState(blendState[1], nullptr, 0xFFFFFFFF);
	//box->Render();
}

void Rect::GUI()
{
	//ImGui::Begin("Rect", &bOpen);
	{
		ImGui::InputFloat3(MakeLabel("Pos").c_str(), position, 2);
		ImGui::InputFloat3(MakeLabel("Size").c_str(), size, 2);
		//ImGui::InputFloat("Rot", &rotation, 2);
		//ImGui::DragFloat("Rot", &rotation, 1, 0, 360, "%.1f");
		//float rot = D3DXToRadian(rotation);

		ImGui::SliderAngle(MakeLabel("Rot").c_str(), &rotation);
		//rotation = D3DXToDegree(rot);

		if (ImGui::ColorPicker4(MakeLabel("Color").c_str(), color))
			UpdateColor();
	}
	//ImGui::End();
}

void Rect::Move()
{
	if (Keyboard::Get()->Press('W'))
		position.y += 100 * Time::Delta();
	else if (Keyboard::Get()->Press('S'))
		position.y -= 100 * Time::Delta();
	if (Keyboard::Get()->Press('A'))
		position.x -= 100 * Time::Delta();
	else if (Keyboard::Get()->Press('D'))
		position.x += 100 * Time::Delta();
}

void Rect::UpdateColor()
{
	D3D11_MAPPED_SUBRESOURCE subResource;
	DC->Map(vb->GetResource(), 0, D3D11_MAP_WRITE_DISCARD, 0, &subResource);
	{
		for (VertexColor& v : vertices)
		{
			v.color = this->color;
		}
		memcpy(subResource.pData, vertices.data(), vb->GetCount() * vb->GetStride());
	}
	DC->Unmap(vb->GetResource(), 0);
}

string Rect::MakeLabel(string preFix)
{
	string label = preFix + "##" + to_string((uint)this);
	return label;
}

void Rect::UpdateWorld()
{
	D3DXMatrixTranslation(&T, position.x, position.y, position.z);
	D3DXMatrixScaling(&S, size.x, size.y, size.z);
	D3DXMatrixRotationZ(&R, (float)D3DXToRadian(rotation));
	//D3DXMatrixRotationZ(&R, rotation);
	
	world = S * R * T;
	wb->SetWorld(world);

	//D3DXVec3TransformCoord(&edge.LT, &vertices[1].position, &world);
	//D3DXVec3TransformCoord(&edge.RB, &vertices[2].position, &world);
}