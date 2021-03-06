#pragma once
class Data_c; //仮

class TextBox
{
private:
	WindowMode windowMode;
	int key[256];

	Data_c* originalData;		// データクラスから一覧を読み込む用

	vector<string> message;	//メッセージ格納配列
	int x, y, w, h, raw;	//座標、大きさ、行数
	int position; //選択位置
	int topOfPage;	//ページの先頭の位置

	bool isActivated;	//アクティブ状態か
	bool isVisible;	//可視状態か
	bool isSelected;	//選択状態か

	bool isReverse;

	int windowEdge[9];
	int windowBack;

	//キー入力用変数
	//int key[256]; // 0:入力されていない 1:入力された瞬間 2:入力されている
public:
	TextBox();
	~TextBox();

	void Update();	//更新
	void Draw();		//描画
	void Activate();
	void InActivate();

	void LoadData(Data_c*);

	//ウィンドウ編集用関数
	void SetWindowMode(WindowMode);
	void SetPositon(int,int);
	void SetSize(int,int);

	int GetHeight();
	int GetWidth();

	//メッセージ編集用関数
	void AddMessage(string);
	void SetMessage(string,int);
	void ClearMessage();
	void Reset();
	void DrawMessage(int x, int y, int w, int h, string str);

	//ページめくり関数
	void ScrollUp();
	void ScrollDown();
	void PageUp();
	void PageDown();

	void LoadWindow();
	void DrawWindow(int x, int y, int w, int h);

	string Enter();

	string GetText(int);
};

