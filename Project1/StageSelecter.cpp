﻿#include "StageSelecter.h"
#include <string>
#include <Raki_WinAPI.h>
#include <Raki_imguiMgr.h>

#include "Stage.h"
#include "Player.h"
#include "InputManger.h"
#include "TitleAudio.h"

namespace
{
	static InputManger* inputManager = InputManger::Get();
	Stage* stagePtr = Stage::Get();
	Player* playerPtr = Player::Get();
}

StageSelecter::StageSelecter()
{

}

StageSelecter::~StageSelecter()
{
}

void StageSelecter::Init()
{
	LoadSprite();

	float icon_posx_offset = static_cast<float>(Raki_WinAPI::window_width) / 5.0f;
	float icon_posy_offset = Raki_WinAPI::window_height / 2;

	float icon_x_offsets[4] = {};
	float icon_y_offsets[4] = { icon_posy_offset,icon_posy_offset ,icon_posy_offset ,icon_posy_offset };
	for (int i = 0; i < 4; i++) {
		icon_x_offsets[i] = icon_posx_offset * (i + 1);
	}
	//アイコン画像のロード
	UINT cursorRHandle = TexManager::LoadTexture("Resources/CC/selectBack.png");
	//ページグラフィックの初期化
	for (int i = 0; i < stagePage.size(); i++) {
		std::array<UINT, 4> graphArrays;
		graphArrays = LoadStageIcons(i);

		stagePage[i].Init(icon_x_offsets, icon_y_offsets, graphArrays, cursorRHandle, cursorRHandle
			, backAnimationGraph);
	}

	nowpage = page_1_4;
	nextpage = nowpage;

	//ステージ1を選択中
	user_selecting = UI_STAGEBOX_1;

	nowDisplayNum = 0;

	uiMoveSound = Audio::LoadSound_wav("Resources/sound/SE/mouse02.wav");
}

void StageSelecter::Update()
{
	CheckToStageChangeInput();

	CheckToPageChangeInput();

	PageChange();

	//ページリソースを更新
	for (auto& pages : stagePage) {
		pages.Update();
	}

	Audio::volume = 0.5f;
	TitleAudio::Get()->Play();
}

void StageSelecter::Draw()
{

	for (int i = stagePage.size() - 1; i >= 0; i--) {
		stagePage[i].Draw();
	}

	if (nowpage != StageSelecter::page_1_4)
	{
		SelectLeft.DrawSprite(29, 623);
		SelectLeft.Draw();
	}
	if (nowpage != StageSelecter::page_17_20)
	{
		SelectRight.DrawSprite(1184, 623);
		SelectRight.Draw();
	}

	//カーソル描画
	DrawCursor();

}

void StageSelecter::Finalize()
{
	TitleAudio::Get()->Stop();
}

void StageSelecter::GoNextStage()
{
	if (_nowStageNumber == 20) { return; }

	_nowStageNumber++;

	LoadStage(_nowStageNumber);
}

void StageSelecter::Changing_UI_Number()
{
	for (auto& p : stagePage) {
		if (p.displayNum != 0 && p.displayNum != 19) {
			return;
		}
	}

	//入力によってインクリメント、デクリメント
	int select_number = static_cast<int>(user_selecting);
	if (inputManager->LeftTrigger() || Input::isKeyTrigger(DIK_LEFT)) {
		if (user_selecting != UI_BACK && (nowpage != StageSelecter::page_1_4 || user_selecting != UI_STAGEBOX_1)) { 
			select_number--; 
			Audio::PlayLoadedSound(uiMoveSound, true);
		}
	}

	if (inputManager->RightTrigger() || Input::isKeyTrigger(DIK_RIGHT)) {
		if (user_selecting != UI_FRONT && (nowpage != StageSelecter::page_17_20 || user_selecting != UI_STAGEBOX_4))
		{
			select_number++;
			Audio::PlayLoadedSound(uiMoveSound, true);
		}
	}
	user_selecting = static_cast<NOW_SELECTING>(select_number);
}

void StageSelecter::LoadSprite()
{
	std::string fullImgPath = "Resources/selectAnime/";
	std::string pageAnimPath = "pageAnime/select";
	std::string filename = ".png";

	for (int i = 0; i < 20; i++) {
		std::string number = std::to_string(i + 1);
		std::string fullPath = fullImgPath + pageAnimPath + number + filename;
		backAnimationGraph[i] = TexManager::LoadTexture(fullPath);
	}

	selectCursor.CreateAndSetDivisionUVOffsets(cursorSpriteCount, 2, 2, 50, 50, TexManager::LoadTexture("Resources/UI/Cursor/stageSelect.png"));
	SelectLeft.Create(TexManager::LoadTexture(fullImgPath + "SelectLeft" + filename));
	SelectRight.Create(TexManager::LoadTexture(fullImgPath + "SelectRight" + filename));
}

std::array< UINT, 4> StageSelecter::LoadStageIcons(int pageNumber)
{
	std::array<UINT,4> handleTemp;

	string folderPath = "Resources/CC/stageNumber/stageNumber";
	string filename = ".png";

	for (int i = 0; i < 4; i++) {
		string number = std::to_string((i + 1) + pageNumber * 4);
		string fullPath = folderPath + number + filename;
		handleTemp[i] = TexManager::LoadTexture(fullPath);
	}

	return handleTemp;
}

void StageSelecter::CheckToPageChangeInput()
{
	//繧ｹ繝・・繧ｸ驕ｸ謚樔ｸｭ縺ｧ縺ｪ縺・↑繧牙・逅・＠縺ｪ縺・
	if (state != is_selecting)
	{
		return;
	}

	//入力に応じてUI番号変更
	Changing_UI_Number();

	switch (user_selecting)
	{
	case StageSelecter::UI_BACK:

		if (nowpage != page_1_4) {
			//移動方向設定
			pageMoveDir = is_back;
			//前ページ設定
			int pageNum = static_cast<int>(nowpage);
			pageNum--;
			nowpage = static_cast<STAGE_PAGE>(pageNum);
			stagePage[pageNum].ChangeDisplayMode();
			user_selecting = NOW_SELECTING::UI_STAGEBOX_4;
		}

		break;
	case StageSelecter::UI_FRONT:

		if (nowpage != page_17_20) {
			//移動方向設定
			pageMoveDir = is_front;
			//次ページ設定
			int pageNum = static_cast<int>(nowpage);
			pageNum++;
			nowpage = static_cast<STAGE_PAGE>(pageNum);
			stagePage[pageNum - 1].ChangeDisplayMode();
			user_selecting = NOW_SELECTING::UI_STAGEBOX_1;
		}

		break;
	default:
		break;
	}

}

void StageSelecter::PageChange()
{

}

void StageSelecter::CheckLoadStage(int boxnum)
{
	int pageNumber = static_cast<int>(nowpage);

	int LoadStageNumber = (pageNumber * 4) + (boxnum) + 1;

	SelectStageNum = LoadStageNumber;
}

void StageSelecter::CheckToStageChangeInput()
{
	if (state != is_selecting)
	{
		return;
	}

	bool selected = false;
	int select_Stage_num = 0;
	switch (user_selecting)
	{
	case StageSelecter::UI_STAGEBOX_1:
		if (inputManager->DecisionTrigger()) {
			select_Stage_num = 0;
			selected = true;
		}
		break;
	case StageSelecter::UI_STAGEBOX_2:
		if (inputManager->DecisionTrigger()) {
			select_Stage_num = 1;
			selected = true;
		}
		break;
	case StageSelecter::UI_STAGEBOX_3:
		if (inputManager->DecisionTrigger()) {
			select_Stage_num = 2;
			selected = true;
		}
		break;
	case StageSelecter::UI_STAGEBOX_4:
		if (inputManager->DecisionTrigger()) {
			select_Stage_num = 3;
			selected = true;
		}
		break;
	default:
		break;
	}
	if (selected) { 
		//ボタン押す
		stagePage[static_cast<int>(nowpage)].stageIconButton[select_Stage_num].UI_Push();
		CheckLoadStage(select_Stage_num);
		state = is_stageSelected_waiting;
		//これでステージ開始
		isChanging_GameMain = true;
	}

}

void StageSelecter::DrawCursor()
{
	int changecount = 0;
	for (int a = 0; a < 5; a++)
	{
		if (stagePage[a].displayNum > 0 && stagePage[a].displayNum < 19)
		{
			changecount++;
		}
	}

	if (changecount > 0)
	{
		return;
	}

	std::array<int, 4> boxLeft;
	for (int i = 0; i < 4; i++)
	{
		boxLeft[i] = NUMBOX_START_X + (NUMBOX_SIZE * i) + (NUMBOX_SPACE * i);
	}

	for (int i = 0; i < cursorSpriteCount; i++)
	{
		static float x = 0.0f, y = 0.0f;
		selectCursor.uvOffsetHandle = i;

		switch (user_selecting)
		{
		case StageSelecter::UI_BACK:
			x = PAGEMOVE_LEFT_X + PAGEMOVE_SIZE * (i % 2);
			y = PAGEMOVE_Y + PAGEMOVE_SIZE * (i / 2);
			selectCursor.DrawExtendSprite(x - PAGEMOVE_SIZE / 4.0f, y - PAGEMOVE_SIZE / 4.0f,
										  x + PAGEMOVE_SIZE / 4.0f, y + PAGEMOVE_SIZE / 4.0f);
			break;
		case StageSelecter::UI_STAGEBOX_1:
			x = boxLeft[0] + NUMBOX_SIZE * (i % 2);
			y = NUMBOX_START_Y + NUMBOX_SIZE * (i / 2);
			selectCursor.DrawExtendSprite(x - NUMBOX_SIZE / 4.0f, y - NUMBOX_SIZE / 4.0f,
										  x + NUMBOX_SIZE / 4.0f, y + NUMBOX_SIZE / 4.0f);
			break;
		case StageSelecter::UI_STAGEBOX_2:
			x = boxLeft[1] + NUMBOX_SIZE * (i % 2);
			y = NUMBOX_START_Y + NUMBOX_SIZE * (i / 2);
			selectCursor.DrawExtendSprite(x - NUMBOX_SIZE / 4.0f, y - NUMBOX_SIZE / 4.0f,
										  x + NUMBOX_SIZE / 4.0f, y + NUMBOX_SIZE / 4.0f);
			break;
		case StageSelecter::UI_STAGEBOX_3:
			x = boxLeft[2] + NUMBOX_SIZE * (i % 2);
			y = NUMBOX_START_Y + NUMBOX_SIZE * (i / 2);
			selectCursor.DrawExtendSprite(x - NUMBOX_SIZE / 4.0f, y - NUMBOX_SIZE / 4.0f,
										  x + NUMBOX_SIZE / 4.0f, y + NUMBOX_SIZE / 4.0f);
			break;
		case StageSelecter::UI_STAGEBOX_4:
			x = boxLeft[3] + NUMBOX_SIZE * (i % 2);
			y = NUMBOX_START_Y + NUMBOX_SIZE * (i / 2);
			selectCursor.DrawExtendSprite(x - NUMBOX_SIZE / 4.0f, y - NUMBOX_SIZE / 4.0f,
										  x + NUMBOX_SIZE / 4.0f, y + NUMBOX_SIZE / 4.0f);
			break;
		case StageSelecter::UI_FRONT:
			x = PAGEMOVE_RIGHT_X + PAGEMOVE_SIZE * (i % 2);
			y = PAGEMOVE_Y + PAGEMOVE_SIZE * (i / 2);
			selectCursor.DrawExtendSprite(x - PAGEMOVE_SIZE / 4.0f, y - PAGEMOVE_SIZE / 4.0f,
										  x + PAGEMOVE_SIZE / 4.0f, y + PAGEMOVE_SIZE / 4.0f);
			break;
		default:
			break;
		}
	}

	selectCursor.Draw();
}

void StageSelecter::LoadStage(int stagenum)
{
	string stageNumber = std::to_string(stagenum);

	string stageFilePath = "./Resources/stage/stage";
	string filename = ".csv";

	string stageFullPath = stageFilePath + stageNumber + filename;

	SelectStageNum = stagenum;

	stagePtr->LoadStage(stageFullPath.c_str(), playerPtr->playerTile);
	playerPtr->Init();
	playerPtr->BodySetUp(playerPtr->playerTile);
}

void StageSelecter::IconReset()
{
	for (auto& page : stagePage) {
		for (int i = 0; i < page.stageIconButton.size(); i++) {
			page.stageIconButton[i].Reset();
		}
	}
	//直前のステージのページに合わせて、選択位置も合わせておく
	int page = (SelectStageNum - 1) / 4;
	nowpage = static_cast<STAGE_PAGE>(page);
	stagePage[page].isDisplay = true;
	for (int i = page - 1; i >= 0; i--) {
		stagePage[i].isDisplay = false;
	}

	int selectedBoxNum = SelectStageNum % 4;

	switch (selectedBoxNum)
	{
	case 1:
		user_selecting = UI_STAGEBOX_1;
		break;

	case 2:
		user_selecting = UI_STAGEBOX_2;
		break;

	case 3:
		user_selecting = UI_STAGEBOX_3;
		break;

	case 0:
		user_selecting = UI_STAGEBOX_4;
		break;
	default:
		break;
	}

}

void Page::Init(float xicons[], float yicons[], std::array<UINT,4> uiGraphHandles, UINT cursorR, UINT cursorL, std::array<UINT, 20> backTexture)
{
	//各種リソース初期化
	for (int i = 0; i < 4; i++) {
		iconX[i] = xicons[i];
		iconY[i] = yicons[i];
		stageIconButton[i].Init(60, uiGraphHandles[i], 144, 144);
		this->cursorL.Create(cursorL);
		this->cursorR.Create(cursorR);
	}
	//ウィンドウサイズと同じ解像度のレンダーテクスチャ
	rtHandle = RenderTargetManager::GetInstance()->CreateRenderTexture(Raki_WinAPI::window_width, Raki_WinAPI::window_height);
	//それを描画するスプライト
	rtSprite.CreateRtexSprite(rtHandle);
	//背景
	backSprite.Create(TexManager::LoadTexture("Resources/CC/pageAnime/select1.png"));

	drawLTpos = RVector3(-1280.0f, 0.0f, 0.0f);

	//背景アニメーションスプライト生成
	for (int i = 0; i < backAnimation.size(); i++) {
		backAnimation[i].Create(backTexture[i]);
	}
	
	
	//表示フラグ有効化
	isDisplay = true;
}

void Page::Update()
{
	for (auto& ui : stageIconButton) {
		ui.Update();
	}

	float rate = static_cast<float>(frame) / static_cast<float>(EASE_FRAME);
	//アニメーション処理

	//表示状態かつ、アニメーションの表示番号が0じゃない
	if (isDisplay && displayNum > 0) {
		frame++;
		if (frame % ANIMATION_SPEED == 0) {
			displayNum--;
		}
	}
	//非表示状態かつ、アニメーションの表示番号が19じゃない
	else if (!isDisplay && displayNum < backAnimation.size() - 1) {
		frame++;
		if (frame % ANIMATION_SPEED == 0) {
			displayNum++;
		}
	}

}

void Page::Draw()
{
	//背景
	backAnimation[displayNum].DrawSprite(0, 0);
	backAnimation[displayNum].Draw();
	//ui
	if (isDisplay && displayNum == 0) {
		for (int i = 0; i < stageIconButton.size(); i++) {
			stageIconButton[i].Draw(iconX[i], iconY[i]);
		}
	}

	//左右表示（あとで）

	//ページ描画
	rtSprite.DrawRTexSprite(rtHandle, drawLTpos.x, drawLTpos.y, drawLTpos.x + 1280.0f, drawLTpos.y + 720.0f, 0.0f);
	rtSprite.Draw();
}

void Page::ChangeDisplayMode()
{
	if (isDisplay) {
		isDisplay = false;
		frame = 0;
	}
	else {
		isDisplay = true;
		frame = 0;
	}
}
