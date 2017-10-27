#pragma once
class Data_c; //��

class TextBox
{
private:
	WindowMode windowMode;
	int key[256];

	Data_c* originalData;		// �f�[�^�N���X����ꗗ��ǂݍ��ޗp

	vector<string> message;	//���b�Z�[�W�i�[�z��
	int x, y, w, h, raw;	//���W�A�傫���A�s��
	int position; //�I���ʒu
	int topOfPage;	//�y�[�W�̐擪�̈ʒu

	bool isActivated;	//�A�N�e�B�u��Ԃ�
	bool isVisible;	//����Ԃ�
	bool isSelected;	//�I����Ԃ�

	int windowEdge[9];
	int windowBack;

	//�L�[���͗p�ϐ�
	//int key[256]; // 0:���͂���Ă��Ȃ� 1:���͂��ꂽ�u�� 2:���͂���Ă���
public:
	TextBox();
	~TextBox();

	void Update();	//�X�V
	void Draw();		//�`��
	void Activate();
	void InActivate();

	void LoadData(Data_c*);

	//�E�B���h�E�ҏW�p�֐�
	void SetWindowMode(WindowMode);
	void SetPositon(int,int);
	void SetSize(int,int);

	int GetHeight();
	int GetWidth();

	//���b�Z�[�W�ҏW�p�֐�
	void AddMessage(string);
	void SetMessage(string,int);
	void ClearMessage();

	//�y�[�W�߂���֐�
	void ScrollUp();
	void ScrollDown();
	void PageUp();
	void PageDown();

<<<<<<< HEAD
	void LoadWindow();
	void DrawWindow(int x, int y, int w, int h);
=======
	string Enter();
>>>>>>> BattleScene

	string GetText(int);
};

