#pragma once
#include "Editor/EditData.h"
#include "Editor/DataGenerator.h"
#define IMGUI_LEFT_LABEL(func, label, ...) (ImGui::TextUnformatted(label), ImGui::SameLine(), func("##" label, __VA_ARGS__))


class MainScene : public IObject
{
public:
	// IObject을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Destroy() override;
	virtual void Update() override;
	virtual void PreRender() override;
	virtual void Render() override;
	virtual void GUI() override;

private: // unit data tap
	void ShowCloneDataEdit();
	void ShowAssaultDataEdit();
	void ShowBrownAssaultDataEdit();
	void ShowRedAssaultDataEdit();
	void ShowCannoneerDataEdit();
	void ShowEngineerDataEdit();
	void ShowMedicDataEdit();
	void ShowNebulizerDataEdit();
	void ShowPyroDataEdit();
	void ShowSniperDataEdit();

	void ShowUnitDataEdit(EditData::UnitIndex unitIndex);
private: // unit bullet tap
	
	void ShowCloneBulletEdit();
	void ShowAssaultBulletEdit();
	void ShowBrownAssaultBulletEdit();
	void ShowRedAssaultBulletEdit();
	void ShowCannoneerBulletEdit();
	void ShowEngineerBulletEdit();
	void ShowMedicBulletEdit();
	void ShowNebulizerBulletEdit();
	void ShowPyroBulletEdit();
	void ShowSniperBulletEdit();


	void ShowUnitBulletEdit(EditData::UnitIndex unitIndex);

private :
	void ShowCloneMuzzleFlashEdit();
	void ShowAssaultMuzzleFlashEdit();
	void ShowBrownAssaultMuzzleFlashEdit();
	void ShowRedAssaultMuzzleFlashEdit();
	void ShowCannoneerMuzzleFlashEdit();
	void ShowEngineerMuzzleFlashEdit();
	void ShowMedicMuzzleFlashEdit();
	void ShowNebulizerMuzzleFlashEdit();
	void ShowPyroMuzzleFlashEdit();
	void ShowSniperMuzzleFlashEdit();


	void ShowUnitMuzzleFlashEdit(EditData::UnitIndex unitIndex);

private: // resapwn data tap

	void ShowCloneRespawnEdit();
	void ShowAssaultRespawnEdit();
	void ShowBrownAssaultRespawnEdit();
	void ShowRedAssaultRespawnEdit();
	void ShowCannoneerRespawnEdit();
	void ShowEngineerRespawnEdit();
	void ShowMedicRespawnEdit();
	void ShowNebulizerRespawnEdit();
	void ShowPyroRespawnEdit();
	void ShowSniperRespawnEdit();


	void ShowUnitRespawnEdit(EditData::UnitIndex unitIndex);

private:
	DataGenerator dataGenerator;

private:

private:
	class Pannel * mainScene = nullptr;
	class  Pannel * loading = nullptr;

	bool isEditMode = false;
	bool isSceneTransition = false;
};








