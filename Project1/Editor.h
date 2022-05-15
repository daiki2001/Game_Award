#pragma once
#include "BaseScene.h"
#include "ISceneChanger.h"
#include "Sprite.h"
#include <string>

class Editor : public BaseScene
{
public: //仮想関数
	Editor(ISceneChanger* changer);
	~Editor() override {};
	void Initialize() override; //初期化処理をオーバーライド。
	void Finalize() override;   //終了処理をオーバーライド。
	void Update() override;     //更新処理をオーバーライド。
	void Draw() override;       //描画処理をオーバーライド。

private: //定数
	static const std::string directoryPath; //ディレクトリパス

private: //静的メンバ変数
	static std::string fileName; //ファイル名

private: //メンバ関数
	void Create();  //生成処理

	int SaveFile();
	int LoadFile();
	int Save(const char* fileName);

private: //メンバ変数
	// 背景画像
	Sprite backSprite;

	bool isOpen; //ファイルの読み込みがされているかどうか
	bool isSave; //セーブ中かどうか
	bool isLoad; //読み込み中かどうか
};
