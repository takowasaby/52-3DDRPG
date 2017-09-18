#pragma once

const int SCENARIO_SIZE = 5;
const int STAGE_SIZE = 5;
const int ITEM_TYPE_SIZE = 3;
const int ITEM_SIZE = 32;
const int NAME_SIZE = 32;
const int SKILL_CODE_SIZE = 16;

class Data_c {
private:
	int scenario;
	int dungeonX, dungeonY;
	int mapFlag[SCENARIO_SIZE][STAGE_SIZE][MAP_SIZE_X][MAP_SIZE_Y];
	int eventFlag[SCENARIO_SIZE][64];
	int playCount;
//	int itemFlag[SCENARIO_SIZE][ITEM_TYPE_SIZE][ITEM_SIZE];

	struct Skill_t {
		int num;				//�X�L���ŗL�̐���
		char name[64];			//�X�L���̖��O
		int MP;					//�X�L���̏���MP
		int effect;				//�X�L���̌���(0:HP�񕜁A1:MP�񕜁A2:STR�㏸�A3:VIT�㏸�A4:AGI�㏸�A5:INT�㏸�A6:�_���[�W)
		int status;				//�X�L���̌��ʂɈˑ������X�e�[�^�X
		int magnification;		//�X�L�����ʂ̃X�e�[�^�X�ˑ��̔{��
		int area;				//�X�L�����ʂ͈̔�(0:�P�́A1:�S��)
		char explain[64];		//�X�L���̐�����
	};

	struct Item_t {
		int flag;				//�A�C�e�����������Ă����
		int num;				//�A�C�e���ŗL�̐���
		char name[64];			//�A�C�e���̖��O
		int type;				//�A�C�e���̎��(0:���Օi�A1:�������Ȃ���)
		int effect1, effect2;	//�A�C�e���̌���(0:HP�񕜁A1:MP�񕜁A2:STR�㏸�A3:VIT�㏸�A4:AGI�㏸�A5:INT�㏸�A6:�_���[�W)
		int point1, point2;		//�A�C�e�����ʂ̌Œ�l
		int area1, area2;		//�A�C�e�����ʂ͈̔�(0:�P�́A1:�S��)
		char explain[64];		//�A�C�e���̐�����
	};

	struct Soubi_t {
		int flag;				//�������������Ă����
		int num;				//�����ŗL�̐���
		char name[64];			//�����̖��O
		int type;				//�����̎��(0:����A1:�A�N�Z�T���[)
		int effect;				//�����̌���(0:HP�㏸�A1:MP�㏸�A2:STR�㏸�A3:VIT�㏸�A4:AGI�㏸�A5:INT�㏸)
		int point;				//�������ʂ̌Œ�l
		int area;				//����̍U���͈�(0:�P�́A1:�S��)
		char explain[64];		//�����̐�����
	};
	
	struct Character_t {
		int flag;
		const int HPMAX, MPMAX, STR, VIT, AGI, INT;
		int HP, MP;
		char name[NAME_SIZE];
		int skillCode[SKILL_CODE_SIZE];
		int Image;
	};

public:
	Data_c();		//�R���X�g���N�^
	~Data_c();		//�f�X�g���N�^

	void LoadAll(int scenario);
	void ItemLoad(int scenario);
	void SoubiLoad(int scenario);
	void SkillLoad(int scenario);
	void CharacterLoad(int scenario);

	int GetScenario();
	int GetDungeonX();
	int GetDungeonY();

	void SetScenario(int i);
	void SetDungeonX(int i);
	void SetDungeonY(int i);
};