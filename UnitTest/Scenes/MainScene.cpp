#include "stdafx.h"
#include "MainScene.h"
#include "UI/Button.h"
#include "UI/Pannel.h"
#include "Event/EventDispatcher.h"
#include "Event/EventTypes.h"
#include "Game/GameObjectManager.h"
#include "Game/RenderManager.h"
#include "GameUI/FadeInOut.h"

void MainScene::Init()
{
	Camera::Create();
	GameObjectManager::Create();
	RenderManager::Create();
	FadeInOut * fadeIn = new FadeInOut();
	isSceneTransition = false;
	fadeIn->FadeIn([]()
	{

	});

	mainScene = new Pannel(TexturePath + L"Main2.jpg", Vector3(WinMaxWidth / 2, WinMaxHeight / 2, 0), Vector3(WinMaxWidth, WinMaxHeight, 1), false);
	Button * button = new Button(Vector3(WinMaxWidth / 2, WinMaxHeight / 2, 0), Vector3(WinMaxWidth,  WinMaxHeight, 1), [&]() 
	{
		if (!isEditMode)
		{
			isSceneTransition = true;
			//EventDispatcher::TriggerEvent(SceneEvent::Transition + "TestStage");
			// ∆‰¿ÃµÂ æ∆øÙ µ«∏È æ¿ ∫Ø∞Ê
			//unique_ptr<FadeInOut> fadeOut = make_unique<FadeInOut>();
			FadeInOut * fadeOut = new FadeInOut;
			fadeOut->FadeOut([&]()
			{
				EventDispatcher::TriggerEvent(SceneEvent::Transition + "TestStage");
				//SAFE_DELETE(mainScene);
				//mainScene->Delete();
				//loading = new Pannel(TexturePath + L"Loading.jpg", Vector3(WinMaxWidth / 2, WinMaxHeight / 2, 0), Vector3(WinMaxWidth, WinMaxHeight, 1), false);
				//FadeInOut * fadeIn = new FadeInOut;
				//fadeIn->FadeIn([]()
				//{
				//	EventDispatcher::TriggerEvent(SceneEvent::Transition + "TestStage");
				//});
			});
		}
	});

	dataGenerator.ReadUnitData();
	dataGenerator.ReadUnitBullet();
	dataGenerator.ReadUnitMuzzleFlash();
	dataGenerator.ReadUnitRespawn();

}

void MainScene::Destroy()
{
	//GameObjectManager::Delete();
	GameObjectManager::Delete();
	//GameObjectManager::Get()->ReserveDeletion();
	RenderManager::Delete();
	Camera::Delete();
}

void MainScene::Update()
{
	Camera::Get()->Update();
	GameObjectManager::Get()->Update();
}

void MainScene::PreRender()
{
}

void MainScene::Render()
{
	Camera::Get()->Render();
	RenderManager::Get()->Render();
}

void MainScene::GUI()
{
	ImGui::SetNextWindowPos({50, 30});
	ImGui::SetNextWindowSize(ImVec2(300, 200));
	static bool bOpen = true;
	if (isSceneTransition == false)
	{
		ImGui::Begin
		(
			"EditModeBtn_Label",
			&bOpen,
			ImGuiWindowFlags_NoBackground |
			ImGuiWindowFlags_NoTitleBar |
			ImGuiWindowFlags_NoResize |
			ImGuiWindowFlags_NoMove
		);
		{
			if (ImGui::Button("Edit Mode", ImVec2(150, 70)))
			{
				isEditMode = !isEditMode;
			}
		}
		ImGui::End();
	}
	if (isEditMode)
	{
		float windowXOffset = -400;
		float windowYOffset = -300;
		ImGui::SetNextWindowPos(
			{
				WinMaxWidth * 0.5f + windowXOffset,
				WinMaxHeight * 0.5f + windowYOffset
			});
		ImGui::SetNextWindowSize(ImVec2(800, 600));
		ImGui::Begin
		(
			"Editor Window",
			&bOpen,
			ImGuiWindowFlags_NoCollapse |
			ImGuiWindowFlags_NoMove |
			ImGuiWindowFlags_NoResize |
			ImGuiWindowFlags_MenuBar
		);
		{
			if (ImGui::BeginMenuBar())
			{
				if(ImGui::BeginMenu("Menu"))
				{
					//ShowExampleMenuFile();
					if (ImGui::MenuItem("Save")) 
					{
						dataGenerator.SaveUnitData();
						dataGenerator.SaveUnitBullet();
						dataGenerator.SaveUnitMuzzleFlash();
						dataGenerator.SaveUnitRespawn();
					}
					if (ImGui::MenuItem("Load"))
					{
						dataGenerator.ReadUnitData();
						dataGenerator.ReadUnitBullet();
						dataGenerator.ReadUnitMuzzleFlash();
						dataGenerator.ReadUnitRespawn();
					}
					if (ImGui::MenuItem("Reset"))
					{
						dataGenerator.ReadUnitData();
						dataGenerator.ReadUnitBullet();
						dataGenerator.ReadUnitMuzzleFlash();
						dataGenerator.ReadUnitRespawn();
					}
					ImGui::EndMenu();
				}
				ImGui::EndMenuBar();
			}


			ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_None;
			if (ImGui::BeginTabBar("MyTabBar", tab_bar_flags))
			{
				if (ImGui::BeginTabItem("Unit Data"))
				{
					ShowCloneDataEdit();
					ShowAssaultDataEdit();
					ShowBrownAssaultDataEdit();
					ShowRedAssaultDataEdit();
					ShowCannoneerDataEdit();
					ShowEngineerDataEdit();
					ShowMedicDataEdit();
					ShowNebulizerDataEdit();
					ShowPyroDataEdit();
					ShowSniperDataEdit();
					ImGui::EndTabItem();
				}
				if (ImGui::BeginTabItem("Unit Bullet"))
				{
					ShowCloneBulletEdit();
					ShowAssaultBulletEdit();
					ShowBrownAssaultBulletEdit();
					ShowRedAssaultBulletEdit();
					ShowCannoneerBulletEdit();
					ShowEngineerBulletEdit();
					ShowMedicBulletEdit();
					ShowNebulizerBulletEdit();
					ShowPyroBulletEdit();
					ShowSniperBulletEdit();
					ImGui::EndTabItem();
				}
				if (ImGui::BeginTabItem("Unit MuzzleFlash"))
				{
					ShowCloneMuzzleFlashEdit();
					ShowAssaultMuzzleFlashEdit();
					ShowBrownAssaultMuzzleFlashEdit();
					ShowRedAssaultMuzzleFlashEdit();
					ShowCannoneerMuzzleFlashEdit();
					ShowEngineerMuzzleFlashEdit();
					ShowMedicMuzzleFlashEdit();
					ShowNebulizerMuzzleFlashEdit();
					ShowPyroMuzzleFlashEdit();
					ShowSniperMuzzleFlashEdit();
					ImGui::EndTabItem();
				}
				if (ImGui::BeginTabItem("Respawn Data"))
				{
					ShowCloneRespawnEdit();
					ShowAssaultRespawnEdit();
					ShowBrownAssaultRespawnEdit();
					ShowRedAssaultRespawnEdit();
					ShowCannoneerRespawnEdit();
					ShowEngineerRespawnEdit();
					ShowMedicRespawnEdit();
					ShowNebulizerRespawnEdit();
					ShowPyroRespawnEdit();
					ShowSniperRespawnEdit();
					ImGui::EndTabItem();
				}
				ImGui::EndTabBar();
			}
		}
		ImGui::End();
	}
}

void MainScene::ShowCloneDataEdit()
{
	ShowUnitDataEdit(EditData::UnitIndex::Clone);
}

void MainScene::ShowAssaultDataEdit()
{
	ShowUnitDataEdit(EditData::UnitIndex::Assault);
}

void MainScene::ShowBrownAssaultDataEdit()
{
	ShowUnitDataEdit(EditData::UnitIndex::BrownAssault);
}

void MainScene::ShowRedAssaultDataEdit()
{
	ShowUnitDataEdit(EditData::UnitIndex::RedAssault);
}

void MainScene::ShowCannoneerDataEdit()
{
	ShowUnitDataEdit(EditData::UnitIndex::Cannoneer);
}

void MainScene::ShowEngineerDataEdit()
{
	ShowUnitDataEdit(EditData::UnitIndex::Engineer);
}

void MainScene::ShowMedicDataEdit()
{
	ShowUnitDataEdit(EditData::UnitIndex::Medic);
}

void MainScene::ShowNebulizerDataEdit()
{
	ShowUnitDataEdit(EditData::UnitIndex::Nebulizer);
}

void MainScene::ShowPyroDataEdit()
{
	ShowUnitDataEdit(EditData::UnitIndex::Pyro);
}

void MainScene::ShowSniperDataEdit()
{
	ShowUnitDataEdit(EditData::UnitIndex::Sniper);
}

void MainScene::ShowUnitDataEdit(EditData::UnitIndex unitIndex)
{
	string unitName = dataGenerator.unitNames[(unsigned int)unitIndex];
	if (!ImGui::CollapsingHeader(unitName.c_str()))
		return;

	ImGui::TextUnformatted((unitName + " Texture Path").c_str());
	ImGui::SameLine();
	ImGui::PushItemWidth(ImGui::GetWindowWidth() * 0.5f );
	ImGui::InputText(("##" + unitName + " Texture Path").c_str(), dataGenerator.unitDatas[(unsigned int)unitIndex].texturePath, EditData::MaxPath);
	ImGui::SameLine();
	if (ImGui::Button((unitName + " Texture Load").c_str()))
	{
		string texturePath(dataGenerator.unitDatas[(unsigned int)unitIndex].texturePath);
		dataGenerator.unitDatas[(unsigned int)unitIndex].tex = new Texture2D(String::ToWstring(texturePath));
	}
	if (dataGenerator.unitDatas[(unsigned int)unitIndex].tex)
	{
		ImGuiIO& io = ImGui::GetIO();

		float my_tex_w = dataGenerator.unitDatas[(unsigned int)unitIndex].tex->GetWidth();
		float my_tex_h = dataGenerator.unitDatas[(unsigned int)unitIndex].tex->GetHeight();

		ImGui::Text("%.0fx%.0f", my_tex_w, my_tex_h);
		ImVec2 pos = ImGui::GetCursorScreenPos();
		ImGui::Image(dataGenerator.unitDatas[(unsigned int)unitIndex].tex->GetSRV(), ImVec2(my_tex_w, my_tex_h), ImVec2(0, 0), ImVec2(1, 1), ImVec4(1.0f, 1.0f, 1.0f, 1.0f), ImVec4(1.0f, 1.0f, 1.0f, 0.5f));
		if (ImGui::IsItemHovered())
		{
			ImGui::BeginTooltip();
			float region_sz = 32.0f;
			float region_x = io.MousePos.x - pos.x - region_sz * 0.5f; if (region_x < 0.0f) region_x = 0.0f; else if (region_x > my_tex_w - region_sz) region_x = my_tex_w - region_sz;
			float region_y = io.MousePos.y - pos.y - region_sz * 0.5f; if (region_y < 0.0f) region_y = 0.0f; else if (region_y > my_tex_h - region_sz) region_y = my_tex_h - region_sz;
			float zoom = 4.0f;
			ImGui::Text("Min: (%.2f, %.2f)", region_x, region_y);
			ImGui::Text("Max: (%.2f, %.2f)", region_x + region_sz, region_y + region_sz);
			ImVec2 uv0 = ImVec2((region_x) / my_tex_w, (region_y) / my_tex_h);
			ImVec2 uv1 = ImVec2((region_x + region_sz) / my_tex_w, (region_y + region_sz) / my_tex_h);
			ImGui::Image(dataGenerator.unitDatas[(unsigned int)unitIndex].tex->GetSRV(), ImVec2(region_sz * zoom, region_sz * zoom), uv0, uv1, ImVec4(1.0f, 1.0f, 1.0f, 1.0f), ImVec4(1.0f, 1.0f, 1.0f, 0.5f));
			ImGui::EndTooltip();
		}
	}
	ImGui::TextUnformatted((unitName + " Max HP").c_str());
	ImGui::SameLine();
	ImGui::InputInt(("##" + unitName + " Max HP").c_str(), &dataGenerator.unitDatas[(unsigned int)unitIndex].maxHp);
	//IMGUI_LEFT_LABEL(ImGui::InputInt, "Assault Max HP", &unitDatas[(unsigned int)EditData::UnitIndex::Assault].maxHp);
	
	ImGui::TextUnformatted((unitName + " Move Speed").c_str());
	ImGui::SameLine();
	ImGui::InputInt(("##" + unitName + " Move Speed").c_str(), &dataGenerator.unitDatas[(unsigned int)unitIndex].moveSpeed);
	//IMGUI_LEFT_LABEL(ImGui::InputInt, "Assault Move Speed", &unitDatas[(unsigned int)unitIndex].moveSpeed);
	
	ImGui::TextUnformatted((unitName + " Size").c_str());
	ImGui::SameLine();
	ImGui::InputFloat3(("##" + unitName + " Size").c_str(), dataGenerator.unitDatas[(unsigned int)unitIndex].size);
	//IMGUI_LEFT_LABEL(ImGui::InputFloat3, "Assault Size", unitDatas[(unsigned int)unitIndex].size);

	ImGui::TextUnformatted((unitName + " Fire Position Offset").c_str());
	ImGui::SameLine();
	ImGui::InputFloat3(("##" + unitName + " Fire Position Offset").c_str(), dataGenerator.unitDatas[(unsigned int)unitIndex].firePosOffset);
	//IMGUI_LEFT_LABEL(ImGui::InputFloat3, "Assault Fire Position Offset", unitDatas[(unsigned int)unitIndex].firePosOffset);

}

void MainScene::ShowCloneBulletEdit()
{
	ShowUnitBulletEdit(EditData::UnitIndex::Clone);
}

void MainScene::ShowAssaultBulletEdit()
{
	ShowUnitBulletEdit(EditData::UnitIndex::Assault);
}

void MainScene::ShowBrownAssaultBulletEdit()
{
	ShowUnitBulletEdit(EditData::UnitIndex::BrownAssault);
}

void MainScene::ShowRedAssaultBulletEdit()
{
	ShowUnitBulletEdit(EditData::UnitIndex::RedAssault);
}

void MainScene::ShowCannoneerBulletEdit()
{
	ShowUnitBulletEdit(EditData::UnitIndex::Cannoneer);
}

void MainScene::ShowEngineerBulletEdit()
{
	ShowUnitBulletEdit(EditData::UnitIndex::Engineer);
}

void MainScene::ShowMedicBulletEdit()
{
	ShowUnitBulletEdit(EditData::UnitIndex::Medic);
}

void MainScene::ShowNebulizerBulletEdit()
{
	ShowUnitBulletEdit(EditData::UnitIndex::Nebulizer);
}

void MainScene::ShowPyroBulletEdit()
{
	ShowUnitBulletEdit(EditData::UnitIndex::Pyro);
}

void MainScene::ShowSniperBulletEdit()
{
	ShowUnitBulletEdit(EditData::UnitIndex::Sniper);
}

void MainScene::ShowUnitBulletEdit(EditData::UnitIndex unitIndex)
{
	string unitName = dataGenerator.unitNames[(unsigned int)unitIndex];
	if (!ImGui::CollapsingHeader(unitName.c_str()))
		return;

	ImGui::TextUnformatted((unitName + " Texture Path").c_str());
	ImGui::SameLine();
	ImGui::PushItemWidth(ImGui::GetWindowWidth() * 0.5f);
	ImGui::InputText(("##" + unitName + " Texture Path").c_str(), dataGenerator.unitBullets[(unsigned int)unitIndex].texturePath, EditData::MaxPath);
	ImGui::SameLine();
	if (ImGui::Button((unitName + " Texture Load").c_str()))
	{
		string texturePath(dataGenerator.unitBullets[(unsigned int)unitIndex].texturePath);
		dataGenerator.unitBullets[(unsigned int)unitIndex].tex = new Texture2D(String::ToWstring(texturePath));
	}
	if (dataGenerator.unitBullets[(unsigned int)unitIndex].tex)
	{
		ImGuiIO& io = ImGui::GetIO();

		float my_tex_w = dataGenerator.unitBullets[(unsigned int)unitIndex].tex->GetWidth();
		float my_tex_h = dataGenerator.unitBullets[(unsigned int)unitIndex].tex->GetHeight();

		ImGui::Text("%.0fx%.0f", my_tex_w, my_tex_h);
		ImVec2 pos = ImGui::GetCursorScreenPos();
		ImGui::Image(dataGenerator.unitBullets[(unsigned int)unitIndex].tex->GetSRV(), ImVec2(my_tex_w, my_tex_h), ImVec2(0, 0), ImVec2(1, 1), ImVec4(1.0f, 1.0f, 1.0f, 1.0f), ImVec4(1.0f, 1.0f, 1.0f, 0.5f));
		if (ImGui::IsItemHovered())
		{
			ImGui::BeginTooltip();
			float region_sz = 32.0f;
			float region_x = io.MousePos.x - pos.x - region_sz * 0.5f; if (region_x < 0.0f) region_x = 0.0f; else if (region_x > my_tex_w - region_sz) region_x = my_tex_w - region_sz;
			float region_y = io.MousePos.y - pos.y - region_sz * 0.5f; if (region_y < 0.0f) region_y = 0.0f; else if (region_y > my_tex_h - region_sz) region_y = my_tex_h - region_sz;
			float zoom = 4.0f;
			ImGui::Text("Min: (%.2f, %.2f)", region_x, region_y);
			ImGui::Text("Max: (%.2f, %.2f)", region_x + region_sz, region_y + region_sz);
			ImVec2 uv0 = ImVec2((region_x) / my_tex_w, (region_y) / my_tex_h);
			ImVec2 uv1 = ImVec2((region_x + region_sz) / my_tex_w, (region_y + region_sz) / my_tex_h);
			ImGui::Image(dataGenerator.unitBullets[(unsigned int)unitIndex].tex->GetSRV(), ImVec2(region_sz * zoom, region_sz * zoom), uv0, uv1, ImVec4(1.0f, 1.0f, 1.0f, 1.0f), ImVec4(1.0f, 1.0f, 1.0f, 0.5f));
			ImGui::EndTooltip();
		}
	}

	ImGui::TextUnformatted((unitName + " Damage").c_str());
	ImGui::SameLine();
	ImGui::InputInt(("##" + unitName + " Damage").c_str(), &dataGenerator.unitBullets[(unsigned int)unitIndex].damage);

	ImGui::TextUnformatted((unitName + " Speed").c_str());
	ImGui::SameLine();
	ImGui::InputInt(("##" + unitName + " Speed").c_str(), &dataGenerator.unitBullets[(unsigned int)unitIndex].speed);

	ImGui::TextUnformatted((unitName + " Size").c_str());
	ImGui::SameLine();
	ImGui::InputFloat3(("##" + unitName + " Size").c_str(), dataGenerator.unitBullets[(unsigned int)unitIndex].size);

	ImGui::TextUnformatted((unitName + " Collision Size").c_str());
	ImGui::SameLine();
	ImGui::InputFloat3(("##" + unitName + " Collision Size").c_str(), dataGenerator.unitBullets[(unsigned int)unitIndex].collisionSize);

}

void MainScene::ShowCloneMuzzleFlashEdit()
{
	ShowUnitMuzzleFlashEdit(EditData::UnitIndex::Clone);
}

void MainScene::ShowAssaultMuzzleFlashEdit()
{
	ShowUnitMuzzleFlashEdit(EditData::UnitIndex::Assault);
}

void MainScene::ShowBrownAssaultMuzzleFlashEdit()
{
	ShowUnitMuzzleFlashEdit(EditData::UnitIndex::BrownAssault);
}

void MainScene::ShowRedAssaultMuzzleFlashEdit()
{
	ShowUnitMuzzleFlashEdit(EditData::UnitIndex::RedAssault);
}

void MainScene::ShowCannoneerMuzzleFlashEdit()
{
	ShowUnitMuzzleFlashEdit(EditData::UnitIndex::Cannoneer);
}

void MainScene::ShowEngineerMuzzleFlashEdit()
{
	ShowUnitMuzzleFlashEdit(EditData::UnitIndex::Engineer);
}

void MainScene::ShowMedicMuzzleFlashEdit()
{
	ShowUnitMuzzleFlashEdit(EditData::UnitIndex::Medic);
}

void MainScene::ShowNebulizerMuzzleFlashEdit()
{
	ShowUnitMuzzleFlashEdit(EditData::UnitIndex::Nebulizer);
}

void MainScene::ShowPyroMuzzleFlashEdit()
{
	ShowUnitMuzzleFlashEdit(EditData::UnitIndex::Pyro);
}

void MainScene::ShowSniperMuzzleFlashEdit()
{
	ShowUnitMuzzleFlashEdit(EditData::UnitIndex::Sniper);
}

void MainScene::ShowUnitMuzzleFlashEdit(EditData::UnitIndex unitIndex)
{
	string unitName = dataGenerator.unitNames[(unsigned int)unitIndex];
	if (!ImGui::CollapsingHeader(unitName.c_str()))
		return;

	ImGui::TextUnformatted((unitName + " Texture Path").c_str());
	ImGui::SameLine();
	ImGui::PushItemWidth(ImGui::GetWindowWidth() * 0.5f);
	ImGui::InputText(("##" + unitName + " Texture Path").c_str(), dataGenerator.unitMuzzleFlashes[(unsigned int)unitIndex].texturePath, EditData::MaxPath);
	ImGui::SameLine();
	if (ImGui::Button((unitName + " Texture Load").c_str()))
	{
		string texturePath(dataGenerator.unitMuzzleFlashes[(unsigned int)unitIndex].texturePath);
		dataGenerator.unitMuzzleFlashes[(unsigned int)unitIndex].tex = new Texture2D(String::ToWstring(texturePath));
	}
	if (dataGenerator.unitMuzzleFlashes[(unsigned int)unitIndex].tex)
	{
		ImGuiIO& io = ImGui::GetIO();

		float my_tex_w = dataGenerator.unitMuzzleFlashes[(unsigned int)unitIndex].tex->GetWidth();
		float my_tex_h = dataGenerator.unitMuzzleFlashes[(unsigned int)unitIndex].tex->GetHeight();

		ImGui::Text("%.0fx%.0f", my_tex_w, my_tex_h);
		ImVec2 pos = ImGui::GetCursorScreenPos();
		ImGui::Image(dataGenerator.unitMuzzleFlashes[(unsigned int)unitIndex].tex->GetSRV(), ImVec2(my_tex_w, my_tex_h), ImVec2(0, 0), ImVec2(1, 1), ImVec4(1.0f, 1.0f, 1.0f, 1.0f), ImVec4(1.0f, 1.0f, 1.0f, 0.5f));
		if (ImGui::IsItemHovered())
		{
			ImGui::BeginTooltip();
			float region_sz = 32.0f;
			float region_x = io.MousePos.x - pos.x - region_sz * 0.5f; if (region_x < 0.0f) region_x = 0.0f; else if (region_x > my_tex_w - region_sz) region_x = my_tex_w - region_sz;
			float region_y = io.MousePos.y - pos.y - region_sz * 0.5f; if (region_y < 0.0f) region_y = 0.0f; else if (region_y > my_tex_h - region_sz) region_y = my_tex_h - region_sz;
			float zoom = 4.0f;
			ImGui::Text("Min: (%.2f, %.2f)", region_x, region_y);
			ImGui::Text("Max: (%.2f, %.2f)", region_x + region_sz, region_y + region_sz);
			ImVec2 uv0 = ImVec2((region_x) / my_tex_w, (region_y) / my_tex_h);
			ImVec2 uv1 = ImVec2((region_x + region_sz) / my_tex_w, (region_y + region_sz) / my_tex_h);
			ImGui::Image(dataGenerator.unitMuzzleFlashes[(unsigned int)unitIndex].tex->GetSRV(), ImVec2(region_sz * zoom, region_sz * zoom), uv0, uv1, ImVec4(1.0f, 1.0f, 1.0f, 1.0f), ImVec4(1.0f, 1.0f, 1.0f, 0.5f));
			ImGui::EndTooltip();
		}
	}

	ImGui::TextUnformatted((unitName + " Size").c_str());
	ImGui::SameLine();
	ImGui::InputFloat3(("##" + unitName + " Size").c_str(), dataGenerator.unitMuzzleFlashes[(unsigned int)unitIndex].size);
}

void MainScene::ShowCloneRespawnEdit()
{
	ShowUnitRespawnEdit(EditData::UnitIndex::Clone);
}

void MainScene::ShowAssaultRespawnEdit()
{
	ShowUnitRespawnEdit(EditData::UnitIndex::Assault);
}

void MainScene::ShowBrownAssaultRespawnEdit()
{
	ShowUnitRespawnEdit(EditData::UnitIndex::BrownAssault);
}

void MainScene::ShowRedAssaultRespawnEdit()
{
	ShowUnitRespawnEdit(EditData::UnitIndex::RedAssault);
}

void MainScene::ShowCannoneerRespawnEdit()
{
	ShowUnitRespawnEdit(EditData::UnitIndex::Cannoneer);
}

void MainScene::ShowEngineerRespawnEdit()
{
	ShowUnitRespawnEdit(EditData::UnitIndex::Engineer);
}

void MainScene::ShowMedicRespawnEdit()
{
	ShowUnitRespawnEdit(EditData::UnitIndex::Medic);
}

void MainScene::ShowNebulizerRespawnEdit()
{
	ShowUnitRespawnEdit(EditData::UnitIndex::Nebulizer);
}

void MainScene::ShowPyroRespawnEdit()
{
	ShowUnitRespawnEdit(EditData::UnitIndex::Pyro);
}

void MainScene::ShowSniperRespawnEdit()
{
	ShowUnitRespawnEdit(EditData::UnitIndex::Sniper);
}

void MainScene::ShowUnitRespawnEdit(EditData::UnitIndex unitIndex)
{
	string unitName = dataGenerator.unitNames[(unsigned int)unitIndex];
	if (!ImGui::CollapsingHeader(unitName.c_str()))
		return;

	ImGui::TextUnformatted((unitName + " Respawn Delay").c_str());
	ImGui::SameLine();
	ImGui::InputFloat(("##" + unitName + " Respawn Delay").c_str(), &dataGenerator.unitRespawns[(unsigned int)unitIndex].delay);

	ImGui::TextUnformatted((unitName + " Pool Maximum").c_str());
	ImGui::SameLine();
	ImGui::InputInt(("##" + unitName + " Pool Maximum").c_str(), (int*)&dataGenerator.unitRespawns[(unsigned int)unitIndex].poolMaximum);

	ImGui::TextUnformatted((unitName + " Start Respawn Time").c_str());
	ImGui::SameLine();
	ImGui::InputFloat(("##" + unitName + " Start Respawn Time").c_str(), &dataGenerator.unitRespawns[(unsigned int)unitIndex].startRespawnTime);


	ImGui::TextUnformatted((unitName + " End Respawn Time").c_str());
	ImGui::SameLine();
	ImGui::InputFloat(("##" + unitName + " End Respawn Time").c_str(), &dataGenerator.unitRespawns[(unsigned int)unitIndex].endRespawnTime);
}


