#include "Editor.h"
#include "InputManger.h"
#include "Stage.h"
#include "Player.h"
#include "Raki_imguiMgr.h"

#define EF (-1) //Error Function

namespace
{
Stage* stage = Stage::Get();

static char name[256] = { 0 };
}

const std::string Editor::directoryPath = "./Resources/stage/";
std::string Editor::fileName = {};

Editor::Editor(ISceneChanger* changer) :
	BaseScene(changer),
	isOpen(false),
	isSave(false),
	isLoad(false),
	backSprite{}
{
	Initialize();
}

void Editor::Initialize()
{
	Create();

	isOpen = false;
	isSave = false;
	isLoad = false;
}

void Editor::Finalize()
{
}

void Editor::Update()
{
	static bool isChange = false; //ƒV[ƒ“Ø‚è‘Ö‚¦‚ð‚·‚é‚©‚Ç‚¤‚©
	isChange = false;

	if (Input::isKeyTrigger(DIK_F5))
	{
		if (isOpen)
		{
			isChange = true;
		}
		else
		{
			isSave = true;
		}
	}

	if (isChange)
	{
		mSceneChanger->ChangeScene(eScene_Game);
	}
}

void Editor::Draw()
{
	Raki_DX12B::Get()->StartDrawRenderTarget();
	Raki_DX12B::Get()->StartDrawBackbuffer();

	backSprite.DrawSprite(0, 0);
	backSprite.Draw();

	if (isSave)
	{
		SaveFile();
	}
	else if (isLoad)
	{
		LoadFile();
	}
	//ImGui::Text(fileName.c_str());

	//•`‰æI—¹
	Raki_DX12B::Get()->CloseDraw();
}

void Editor::Create()
{
	if ((backSprite.spdata->size.x <= 0) || (backSprite.spdata->size.y <= 0))
	{
		backSprite.Create(TexManager::LoadTexture("Resources/background03.png"));
	}
}

int Editor::SaveFile()
{
	if (isSave == false)
	{
		return EF;
	}

	static char name[256] = { 0 };

	ImguiMgr::Get()->StartDrawImgui("SaveFile", 100.0f, 100.0f);
	ImGui::InputText(".csv", name, sizeof(name) / sizeof(name[0]));
	ImguiMgr::Get()->EndDrawImgui();


	if (Input::isKeyTrigger(DIK_RETURN))
	{
		fileName = name;
		fileName = directoryPath + fileName + ".csv";
		Save(fileName.c_str());
		stage->LoadStage(fileName.c_str(), Player::Get()->playerTile);

		isOpen = true;
		isSave = false;
	}

	return 0;
}

int Editor::LoadFile()
{
	if (isLoad == false)
	{
		return EF;
	}

	ImguiMgr::Get()->StartDrawImgui("LoadFile", 100.0f, 100.0f);
	ImGui::InputText(".csv", name, sizeof(name) / sizeof(name[0]));
	ImguiMgr::Get()->EndDrawImgui();

	if (Input::isKeyTrigger(DIK_RETURN))
	{
		fileName = name;
		fileName = directoryPath + fileName;
		stage->LoadStage(fileName.c_str(), Player::Get()->playerTile);

		isOpen = true;
		isLoad = false;
	}

	return 0;
}

int Editor::Save(const char* fileName)
{
	static FILE* fileHandle;

	return 0;
}
