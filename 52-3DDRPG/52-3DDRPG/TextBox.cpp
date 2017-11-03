#include "define.h"

TextBox::TextBox()
	: windowMode(readMode),
	x(0), y(0), w(100), h(100), raw(5),
	isActivated(false), isVisible(true), isSelected(false),
	position(0), topOfPage(0)
{
	LoadWindow();
}

TextBox::~TextBox()
{
}

void TextBox::Update()
{
	//if (!isActivated) return;		//非アクティブ状態なら更新はしない

	//キー入力の検知
	
	static char buf[256];
	GetHitKeyStateAll(buf);
	for (int i = 0; i < 256; i++) {
		if (buf[i]) key[i]++;
		else        key[i] = 0;
	}

	//2017/9/19 メッセージモードの実装開始
	if (windowMode == readMode) {
		//決定キーを押したときの動作
		/*
		if (key[KEY_INPUT_Z] == 1) {
			if (topOfPage < message.size()) topOfPage++;
		}*/
	}

	//2017/9/17 スクロールモードのみ実装開始
	//2017/10/11 すべてのキー入力をクラス外操作に移行
	if (windowMode == pageMode) {
		
		//キー入力によるページ移動
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
				if (topOfPage > message.size() - 1) topOfPage = 0;
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

		//決定キーを押したときの動作
		//if (key[KEY_INPUT_Z] == 1) isSelected = true;
		//else isSelected = false;
	}
}

void TextBox::Draw()
{
	if (!isVisible) return;		//非表示状態なら描画はしない

	//座標とサイズを元にウィンドウを描画する
	//DrawBox(x, y, x + w, y + h, GetColor(255, 255, 255), false);
//	DrawWindow(x, y, w, h);

	//ウィンドウにメッセージを描画する
	if (message.size() > 0) {
		switch (windowMode) {
		case readMode:
			break;
		case pageMode:
			for (int i = topOfPage; i < topOfPage + raw; i++) {
				if (i >(message.size() - 1)) break;
				int color = GetColor(255, 255, 255);
				if (i == position) color = GetColor(255, 191, 0);
				DrawFormatString(x + 5, y + 5 + ((i - topOfPage) * 17), color, message[i].c_str());
			}
			break;
		case scrollMode:
			break;
		case logMode:
			for (int i = 0; i < raw; i++) {
				if (message.size() - i < 1) break;
				DrawFormatString(x + 5, y + 5 + (i * 17), GetColor(255, 255, 255), message[message.size() - i - 1].c_str());
			}
			break;
		}
	}
}
void TextBox::DrawMessage(int px, int py, int width, int height, string str)
{
	int line = 0;
	int start = 0;
	double ww = 8.5;
	for (int i = 0; i < str.size(); i++)
	{
		if (str[i] == 'B' && str.size()-1 != i)
		{
			if (str[i + 1] != 'B')
			{
				continue;
			}
			DrawFormatString(px, py + line * 17, GetColor(255, 191, 0), str.substr(start, i - start).c_str());
			i+=2;
			start = i;
			line++;
		}
		else if (ww*(i - start) > width)
		{
			DrawFormatString(px, py + line * 17, GetColor(255, 191, 0), str.substr(start, i - start).c_str());
			start = i-1;
			line++;
		}
	}
	if(str[str.size()-1] == 'B')
		DrawFormatString(px, py + line * 17, GetColor(255, 191, 0), str.substr(start, str.size() - start-1).c_str());
	else
		DrawFormatString(px, py + line * 17, GetColor(255, 191, 0), str.substr(start, str.size() - start).c_str());
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
	x = px;	//x座標の設定
	y = py;	//y座標の設定
}

void TextBox::SetSize(int pw, int praw)
{
	w = pw;	//幅の設定
	raw = praw;	//行数の設定
	h = 5 + praw*17 + 5;	//高さの設定
}

int TextBox::GetHeight()
{
	return h;
}

int TextBox::GetWidth()
{
	return w;
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

void TextBox::ClearMessage()
{
	message.clear();
	position = 0;
}


void TextBox::ScrollUp()
{
	if (topOfPage < position) position--;
	else if (topOfPage + raw < message.size() - 1) position += raw - 1;
	else position = message.size() - 1;
}

void TextBox::ScrollDown()
{
	if ((topOfPage + raw - 1) > position && position < message.size() - 1) position++;
	else position = topOfPage;
}

void TextBox::PageUp()
{
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

void TextBox::PageDown()
{
	if (topOfPage > 0) {
		topOfPage -= raw;
		position -= raw;
	}
	else {
		topOfPage += (message.size() - (message.size() % raw));
		if (topOfPage > message.size() - 1) topOfPage = 0;
		if (topOfPage + position < message.size() - 1) position += topOfPage;
		else position = message.size() - 1;
	}
}

void TextBox::LoadWindow()
{
	LoadDivGraph("resource/window/枠.png", 9, 3, 3, 8, 8, windowEdge);
	windowBack = LoadGraph("resource/window/背景.png");
}
void TextBox::DrawWindow(int x, int y, int w, int h)
{
//	DrawBox(x, y, x + w, y + h, GetColor(255, 255, 255), false);
	DrawExtendGraph(x + 3, y + 3, x + w - 2, y + h - 2, windowBack, TRUE);

	int edgeType = 0;
	for (int i = 0; i < w / 8; i++) {
		for (int j = 0; j < h / 8; j++) {
			if (i == 0 && j == 0) edgeType = 0;
			else if (i == 0 && j == h / 8 - 1) edgeType = 6;
			else if (i == w / 8 - 1 && j == 0) edgeType = 2;
			else if (i == w / 8 - 1 && j == h / 8 - 1) edgeType = 8;
			else if (i == 0) edgeType = 3;
			else if (j == 0) edgeType = 1;
			else if (i == w / 8 - 1) edgeType = 5;
			else if (j == h / 8 - 1) edgeType = 7;
			else edgeType = 4;
			DrawGraph(x + 8 * i, y + 8 * j, windowEdge[edgeType], TRUE);
		}
	}
}

string TextBox::Enter()
{
	return message[position];
}

int TextBox::EnterInt()
{
	return position;
}

string TextBox::GetText(int index)
{
	return message[index];
}
