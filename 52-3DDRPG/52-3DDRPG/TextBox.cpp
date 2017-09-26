#include "define.h"

TextBox::TextBox()
	: windowMode(readMode),
	x(0), y(0), w(100), h(100), raw(5),
	isActivated(false), isVisible(true), isSelected(false),
	position(0), topOfPage(0)
{
}

TextBox::~TextBox()
{
}

void TextBox::Update()
{
	if (!isActivated) return;		//��A�N�e�B�u��ԂȂ�X�V�͂��Ȃ�

	//�L�[���͂̌��m
	static char buf[256];
	GetHitKeyStateAll(buf);
	for (int i = 0; i < 256; i++) {
		if (buf[i]) key[i]++;
		else        key[i] = 0;
	}

	//2017/9/19 ���b�Z�[�W���[�h�̎����J�n
	if (windowMode == readMode) {
		//����L�[���������Ƃ��̓���
		if (key[KEY_INPUT_Z] == 1) {
			if (topOfPage < message.size()) topOfPage++;
		}
	}

	//2017/9/17 �X�N���[�����[�h�̂ݎ����J�n
	if (windowMode == scrollMode) {
		//�L�[���͂ɂ��y�[�W�ړ�
		if (key[KEY_INPUT_W] == 1) {
			if (topOfPage < position) position--;
			else if (topOfPage + raw < message.size() - 1) position += raw-1;
			else position = message.size() - 1;
		}
		if (key[KEY_INPUT_A] == 1) {
			if (topOfPage > 0) {
				topOfPage -= raw;
				position -= raw;
			}
			else {
				topOfPage += (message.size() - (message.size() % raw));
				if (topOfPage + position < message.size() - 1) position += topOfPage;
				else position = message.size() - 1;
			}
		}
		if (key[KEY_INPUT_S] == 1) {
			if ((topOfPage+raw-1) > position && position < message.size() - 1) position++;
			else position = topOfPage;
		}
		if (key[KEY_INPUT_D] == 1) {
			if (topOfPage + raw < message.size() - 1) {
				topOfPage += raw;
				if (position + raw < message.size() - 1) position += raw;
				else position = message.size() - 1;
			}
			else {
				position = position - topOfPage;
				topOfPage = 0;
			}
		}

		//����L�[���������Ƃ��̓���
		if (key[KEY_INPUT_Z] == 1) isSelected = true;
		else isSelected = false;
	}
}

void TextBox::Draw()
{
	if (!isVisible) return;		//��\����ԂȂ�`��͂��Ȃ�

	//���W�ƃT�C�Y�����ɃE�B���h�E��`�悷��
	DrawBox(x, y, x + w, y + h, GetColor(255, 255, 255), false);

	//�E�B���h�E�Ƀ��b�Z�[�W��`�悷��
	for (int i = topOfPage; i < topOfPage + raw; i++) {
		if (i > message.size() - 1) break;
		int color = GetColor(255, 255, 255);
		if (i == position && windowMode != readMode) color = GetColor(255, 191, 0);
		DrawFormatString(x + 5, y + 5 + ((i-topOfPage) * 17), color, message[i].c_str());
	}
}

void TextBox::Activate()
{
	isActivated = true;
}

void TextBox::InActivate()
{
	isActivated = false;
}

void TextBox::LoadData(Data_c* data)
{
	originalData = data;
}

void TextBox::SetWindowMode(WindowMode pWinodwMode)
{
	windowMode = pWinodwMode;
}

void TextBox::SetPositon(int px, int py)
{
	x = px;	//x���W�̐ݒ�
	y = py;	//y���W�̐ݒ�
}

void TextBox::SetSize(int pw, int ph, int praw)
{
	w = pw;	//���̐ݒ�
	raw = praw;	//�s���̐ݒ�
	h = 5 + praw*17 + 5;	//�����̐ݒ�
}

void TextBox::AddMessage(string text)
{
	message.push_back(text);
}

void TextBox::SetMessage(string text, int index)
{
	if (message.size() > index) message[index] = text;
	else message.push_back(text);
}

string TextBox::GetText(int index)
{
	return message[index];
}