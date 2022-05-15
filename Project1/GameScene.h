#pragma once
#include "BaseScene.h"
#include "ISceneChanger.h"
#include "NY_Object3DMgr.h"
#include "SpriteManager.h"
#include "Audio.h"
#include "../RakiEngine_Library/SpriteManager.h"

#include "testParticle.h"
#include "Player.h"
#include "Stage.h"

#include "StageSelecter.h"
#include "GameMainManager.h"

class GameScene : public BaseScene {
public:
    GameScene::GameScene(ISceneChanger *changer);
    ~GameScene() {}
    void Initialize() override;    //�������������I�[�o�[���C�h�B
    //void Finalize() override;        //�I���������I�[�o�[���C�h�B
    void Update() override;        //�X�V�������I�[�o�[���C�h�B
    void Draw() override;            //�`�揈�����I�[�o�[���C�h�B

    //�V�[���Ŏg���C���X�^���X
    XMFLOAT3 eye = { 0,0,-150 };
    XMFLOAT3 target = { 0,0,0 };
    XMFLOAT3 up = { 0,1,0 };

    // �Q�[�����[�v�Ŏg���ϐ��̐錾
    Player* player = Player::Get();
    Stage* stage = Stage::Get();

    //�X�e�[�W�I�����Q�[������
    enum NowGameState
    {
        is_Select,
        is_Game,
    };
    NowGameState nowState = is_Select;

    StageSelecter selecter;
    GameMainManager gamemain;




};

