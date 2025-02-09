﻿#pragma once
#include "PlayerBody.h"
#include "PlayerFoot.h"
#include <RVector.h>
#include <TexManager.h>
#include "Sprite.h"
#include <Audio.h>

class Player final
{
public: //シングルトン化
	static Player* Get();
private:
	Player();
	Player(const Player&) = delete;
	~Player();
	Player operator=(const Player&) = delete;

public: //メンバ関数
	// 初期化
	void Init();
	// 更新
	void Update(int offsetX, int offsetY);
	// 描画
	void Draw(int offsetX, int offsetY);
	//体の描画
	void DrawBodys(int offsetX, int offsetY);
	// 生成
	void Create();

	//キー操作
	//移動
	void Key_Move();
	//折る・開く
	void Key_FoldOpen();
	//スライド
	void Key_Slide();

	//マウス操作
	//入力状態
	void Mouse_Input(int offsetX, int offsetY);
	//移動
	void Mouse_Move(int offsetX, int offsetY);
	//折る・開く
	void Mouse_FoldOpen(int offsetX, int offsetY);
	//クリックした時のタイル状のマウス座標とプレイヤーのタイル状の座標を比較
	bool IsMouseClickFold(BodyType Direction);
	bool IsMouseClickOpen(BodyType Direction);

	//クリックした場所がステージ内かどうか
	bool IsPressInStage();

	//移動速度の制御
	void MoveSpeedUpdate();

	/// <summary>
	/// どの体を有効化するか
	/// </summary>
	/// <param name="one">body_one</param>
	/// <param name="two">body_two</param>
	/// <param name="three">body_three</param>
	void BodySetUp(bool one, int one_type, bool two, int two_type, bool three, int three_type, bool four, int four_type);
	void BodySetUp(const unsigned char foldCount[4]);

	//プレイヤーが今いるステージがタイル一枚のみのステージなのかどうか
	bool IsPlayerStageOnly();

	//折る
	void Fold();

	//開く
	void Open();

	//顔の当たり判定
	void IsHitPlayerBody();

	//場外判定(顔)
	void IsOutsideFace();

	//body_twoのみ引っかかっているかどうか(trueであればジャンプできない)
	bool IsOnlyHitBody_Two() {}

	//各体・顔の落下判定
	bool IsFall();

	//各体の状態を配列にセット(セットする順番はstage.FoldAndOpenの判定順)
	void SetBodyStatus(bool arrangement[4]);

	//反転したタイルと顔の四隅との判定(折る)
	bool IsReverseHitFace(const unsigned char& direction);

	//反転したタイルと顔の四隅との判定(折る)
	bool IsReverseHitFaceOpen(const unsigned char& direction);

	//任意の方向に折ったあとのブロックとかぶらないか
	bool IsDirectionFoldAll(BodyType foldtype);

	//任意の方向に開いたあとのブロックとかぶらないか
	bool IsDirectionOpenAll(int opentype);

	//有効化されている体の数を取得
	int ActivateBodyCount();

	//顔の下に体があるかどうか
	void IsdownBody();

	//十字方向にブロックがあるかどうか
	void IsAroundBlock();

	//ブロックに邪魔されずにスライドできるかどうか
	void IsSlideBlock();

	//ブロックに邪魔されずに開けるかどうか
	bool IsOpenBlock(BodyType opentype);

	void DeathAnimation();

	// プレイヤーのサウンドの読み込み
	void LoadPlayerSound();
	// プレイヤーのサウンドデータの削除
	void DeletePlayerSound();

public: //メンバ変数
	//床の高さ
	float FloorHeight;

	//顔の中心座標
	RVector3 CenterPosition;

	//向いている方向
	bool IsLeft;
	bool IsRight;

	//歩くかどうか
	bool IsWalk = false;

	//マウスドラッグで折るかどうか
	bool IsDragFold = false;
	XMFLOAT2 DragDis = {};

	//マウスを押している間のカウント
	int PressCount = 0;

	//体(折るほう)
	PlayerBody Body_One;
	PlayerBody Body_Two;
	PlayerBody Body_Three;
	PlayerBody Body_Four;

	//上がふさがっていないか
	bool IsUpBlocked;

	//どの方向を折るか(4方向)
	bool IsLeftFold;
	bool IsUpFold;
	bool IsRightFold;
	bool IsDownFold;

	//どの方向を開くか(4方向)
	bool IsLeftOpen;
	bool IsUpOpen;
	bool IsRightOpen;
	bool IsDownOpen;

	//スライドできるかどうか
	bool IsLeftSlide;
	bool IsUpSlide;
	bool IsRightSlide;
	bool IsDownSlide;

	//十字方向にブロックがあるかどうか
	bool IsLeftBlockFace;
	bool IsRightBlockFace;
	bool IsUpBlockFace;
	bool IsDownBlockFace;

	//上下左右の衝突判定
	bool IsHitLeft = false;
	bool IsHitUp = false;
	bool IsHitRight = false;
	bool IsHitDown = false;

	//上下左右の外枠判定
	bool IsOutSideLeft = false;
	bool IsOutSideUp = false;
	bool IsOutSideRight = false;
	bool IsOutSideDown = false;

	//開くまでに数フレーム空ける用
	int OpenCount = 0;

	//カウントを始めるかどうか
	bool IsOpenCountStart = false;

	//移動速度
	float SideMoveSpeed = 2.0f;

	//ジャンプ
	bool IsJump;
	float JumpSpeed;
	float FallSpeed;

	//ジャンプ入力保持
	bool IsInitJump = false;

	//落下判定(顔のみ)
	bool IsFaceFall;

	//体と顔すべてを考慮した落下判定
	bool IsAllFall;

	//落下中・ジャンプ中にジャンプ入力が入っているかどうか
	bool IsInputjump;

	//どれか一つでも体を動かしていたらtrue
	bool Player_IsAction;

	//画像ハンドル(顔)
	UINT FaceHandle[2];

	//スタートしたかどうか
	bool IsStart;

	//ゴールに触れているかどうか
	bool IsGoal;
	bool isGoalPlayAudio; //ゴール時の音が再生されたかどうか

	//ブロックに当たっているかどうか
	bool IsColide;

	//下に体があるかどうか
	bool IsDownBody;

	bool isRespawn; //リスポーンするかどうか

	//足
	PlayerFoot FaceLeg;

	//描画用スプライト
	Sprite PlayerSprite;
	Sprite PlayerSpriteAction;
	Sprite deathSprite;

	XMFLOAT2 deathPos;      //死んだときの座標
	bool isDeath;           //死んだときのアニメーション中かどうか
	size_t deathFrameCount; //死んだときのアニメーションカウント

	Sprite goalSprite;
	size_t goalFrameCount;

	//マウスのクリック座標
	XMFLOAT2 PressPos = { 0, 0 };
	XMFLOAT2 ReleasePos = { 0, 0 };

	unsigned char playerTile[4] = { 0 };
private:
	// サウンド
	SoundData jumpSound;    //ジャンプ時のSE
	SoundData landingSound; //着地時のSE
	SoundData runSound;     //歩いている時のSE
	SoundData clearSound;   //クリア時のSE
};
