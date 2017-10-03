#pragma once
class Data_c; //仮

class TextBox
{
private:
	//ウィンドウモードに関する列挙体
	enum WindowMode {
		readMode,	//選択できないメッセージ用
		pageMode,	//上下で選択、左右でページ移動
		scrollMode	//スクロールで移動
	};
	WindowMode windowMode;

	Data_c* originalData;		// データクラスから一覧を読み込む用

	vector<string> message;	//メッセージ格納配列
	int x, y, w, h, raw;	//座標、大きさ、行数
	int position; //選択位置
	int topOfPage;	//ページの先頭の位置

	bool isActivated;	//アクティブ状態か
	bool isVisible;	//可視状態か
	bool isSelected;	//選択状態か

	//キー入力用変数
	int key[256]; // 0:入力されていない 1:入力された瞬間 2:入力されている
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
	void SetSize(int,int,int);

	//メッセージ編集用関数
	void AddMessage(string);
	void SetMessage(string,int);

	string GetText(int);
};

