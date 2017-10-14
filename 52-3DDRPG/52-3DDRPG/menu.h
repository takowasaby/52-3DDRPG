#pragma once

class Menu_c {
private:
	int depth;
	int mode = 0;
	int mscenario, mdir, mx, my;
	int mwallType[MAP_SIZE_X][MAP_SIZE_Y];
	int meventFlag[SCENARIO_SIZE][EVENT_SIZE];
	int drawCount;

	int itemType;
	int soubiType;

	int charaNum[CHARACTER_SIZE];
	int itemNum[ITEM_SIZE];
	int soubiNum[SOUBI_SIZE];
	int skillNum[SKILL_SIZE];

	int chooseChara;
	int chooseItem;
	int chooseSoubi;
	int chooseSkill;

	int YN;

	int targetChara;

	int mKey[256];
	int* mMode;
	int* mEvent_scene;
	int* mTitle_scene;
	int* mGame_scene;

	int cursorY = 20;
	const int cursorX = 10;
	const int limitUP = 20;
	const int limitDOWN = 140;

	typedef enum {
		map,
		status,
		soubi,
		item,
		library,
		save,
		option,
	}Mode;

public:
	Menu_c();
	~Menu_c();

	void MenuAll();
	void DrawBack();
	void DrawLeft();
	void DrawRight()
	{
		drawCount = 0;

		printfDx("/nMode:%d, ", mode);
		printfDx("ItemType:%d, ", itemType);
		printfDx("SoubiType:%d, ", soubiType);
		printfDx("CChara:%d, ", chooseChara);
		printfDx("CItem:%d, ", chooseItem);
		printfDx("CSoubi:%d, ", chooseSoubi);
		printfDx("CSkill:%d, ", chooseSoubi);
		printfDx("YN:%d, ", YN);

		switch (depth) {
		case 0:
		case 1:
			switch (mode) {
			case map:
				DrawGoal();

				mscenario = GData.GetScenario();
				mdir = GData.GetDir();
				mx = GData.GetDungeonX();
				my = GData.GetDungeonY();
				for (int i = 0; i < MAP_SIZE_X; i++) {
					for (int j = 0; j < MAP_SIZE_Y; j++) {
						mwallType[i][j] = GData.GetWallType(i, j);
					}
				}

				int xLeft, yUp, size;
				size = 14;
				DrawBox(MENU_MAP_LEFT, MENU_MAP_UP, MENU_MAP_LEFT + 402, MENU_MAP_UP + 402, 0, TRUE);

				for (int i = 0; i < 25; i++) {
					for (int j = 0; j < 25; j++) {
						xLeft = MENU_MAP_LEFT + 1 + j * 16;
						yUp = MENU_MAP_UP + 1 + i * 16;

						switch (mwallType[mx - 4 + j][my - 4 + i]) {
						case 1: DrawBox(xLeft, yUp, xLeft + size, yUp + size, GetColor(255, 255, 255), TRUE);	break;
						case 2: DrawBox(xLeft, yUp, xLeft + size, yUp + size, GetColor(255, 0, 0), TRUE);		break;
						case 3: DrawBox(xLeft, yUp, xLeft + size, yUp + size, GetColor(0, 255, 0), TRUE);		break;
						case 4: DrawBox(xLeft, yUp, xLeft + size, yUp + size, GetColor(0, 0, 255), TRUE);		break;
						}
					}
				}

				xLeft = MENU_MAP_LEFT + 1 + mx * 16;
				yUp = MENU_MAP_UP + 1 + my * 16;
				switch (mdir) {
				case 0:	DrawTriangle(xLeft, yUp + size, xLeft + size / 2, yUp, xLeft + size, yUp + size, GetColor(255, 255, 0), TRUE); break;
				case 1: DrawTriangle(xLeft, yUp, xLeft + size, yUp + size / 2, xLeft, yUp + size, GetColor(255, 255, 0), TRUE); break;
				case 2: DrawTriangle(xLeft, yUp, xLeft + size, yUp, xLeft + size / 2, yUp + size, GetColor(255, 255, 0), TRUE); break;
				case 3: DrawTriangle(xLeft + size, yUp, xLeft, yUp + size / 2, xLeft + size, yUp + size, GetColor(255, 255, 0), TRUE); break;
				}
				break;
			case status:
				for (int i = 0; i < CHARACTER_SIZE; i++) {
					if (GData.GetCharacterFlag(i)) {
						printfDx("/n%s ", GData.GetCharacterName(i));
						printfDx("HP:%d/%d ", GData.GetCharacterPoint(i, 0), GData.GetCharacterPoint(i, 2));
						printfDx("MP:%d/%d ", GData.GetCharacterPoint(i, 1), GData.GetCharacterPoint(i, 3));
						printfDx("STR:%d ", GData.GetCharacterPoint(i, 4));
						printfDx("VIT:%d ", GData.GetCharacterPoint(i, 5));
						printfDx("AGI:%d ", GData.GetCharacterPoint(i, 6));
						printfDx("INT:%d ", GData.GetCharacterPoint(i, 7));

						charaNum[drawCount] = i;
						drawCount++;
					}
				}
				break;
			case soubi:
				for (int i = 0; i < CHARACTER_SIZE; i++) {
					if (GData.GetCharacterFlag(i)) {
						printfDx("/n%s ", GData.GetCharacterName(i));
						printfDx("武器:%s, ", GData.GetSoubiText(GData.GetCharacterPoint(i, 9), 0));
						printfDx("アクセ:%s, ", GData.GetSoubiText(GData.GetCharacterPoint(i, 10), 0));

						charaNum[drawCount] = i;
						drawCount++;
					}
				}
				break;
			case item:
				printfDx("消耗品");
				printfDx("だいじなもの");
				break;
			case library:
				break;
			}
			break;
		case 2:
			switch (mode) {
			case map:
				break;
			case status:
				printfDx("/n%s ", GData.GetCharacterName(chooseChara));
				printfDx("HP:%d/%d ", GData.GetCharacterPoint(chooseChara, 0), GData.GetCharacterPoint(chooseChara, 2));
				printfDx("MP:%d/%d ", GData.GetCharacterPoint(chooseChara, 1), GData.GetCharacterPoint(chooseChara, 3));
				printfDx("STR:%d ", GData.GetCharacterPoint(chooseChara, 4));
				printfDx("VIT:%d ", GData.GetCharacterPoint(chooseChara, 5));
				printfDx("AGI:%d ", GData.GetCharacterPoint(chooseChara, 6));
				printfDx("INT:%d ", GData.GetCharacterPoint(chooseChara, 7));
				DrawGraph(480, 240, GData.GetCharacterPoint(chooseChara, 8), TRUE);

				for (int i = 0; i < SKILL_CODE_SIZE; i++) {
					if (GData.GetCharacterSkillCode(chooseChara, i) == -1) {
						printfDx("/n%s, ", GData.GetSkillText(GData.GetCharacterSkillCode(chooseChara, i), 0));
						skillNum[drawCount] = GData.GetCharacterSkillCode(chooseChara, i);
						drawCount++;
					}
				}

				printfDx("/n%s", GData.GetSkillText(skillNum[chooseSkill], 1));
				break;

			case soubi:
				printfDx("%s", GData.GetCharacterName(chooseChara));

				for (int i = 0; i < SOUBI_SIZE; i++) {
					if (GData.GetSoubiFlag(i) >= 1) {
						if (soubiType == GData.GetSoubiPoint(i, 1)) {
							if (i == GData.GetCharacterPoint(chooseChara, soubiType + 9)) printfDx("E.");
							printfDx("%s, ", GData.GetSoubiText(i, 0));
							soubiNum[drawCount] = i;
							drawCount++;
						}
					}
				}

				printfDx("/n%s", GData.GetSoubiText(soubiNum[chooseSoubi], 1));
				break;

			case item:
				printfDx("消耗品");
				printfDx("だいじなもの");

				for (int i = 0; i < ITEM_SIZE; i++) {
					if (GData.GetItemFlag(i) >= 1) {
						if (itemType == GData.GetItemPoint(i, 1)) {
							printfDx("%s, ", GData.GetItemText(i, 0));
							itemNum[drawCount] = i;
							drawCount++;
						}
					}
				}

				printfDx("/n%s", GData.GetItemText(itemNum[chooseItem], 1));
				break;

			case library:
				break;
			}
		case 3:
			switch (mode) {
			case status:
				printfDx("/nこのスキルを使用しますか？");
				printfDx("はい　");
				printfDx("いいえ");
				break;
			case soubi:
				printfDx("/n%sを装備しますか？", GData.GetSoubiText(soubiNum[chooseSoubi], 0));
				printfDx("はい　");
				printfDx("いいえ");
				break;
			case item:
				printfDx("/nこのアイテムを使用しますか？");
				printfDx("はい　");
				printfDx("いいえ");
				break;
			}
		case 4:
			switch (mode) {
			case status:
				printfDx("/nこのスキルを誰に使用しますか？");
				for (int i = 0; i < CHARACTER_SIZE; i++) {
					if (GData.GetCharacterFlag(i)) {
						printfDx("/n%s ", GData.GetCharacterName(i));
					}
				}
				break;
			case item:
				printfDx("/nこのアイテムを誰に使用しますか？");
				for (int i = 0; i < CHARACTER_SIZE; i++) {
					if (GData.GetCharacterFlag(i)) {
						printfDx("/n%s ", GData.GetCharacterName(i));
					}
				}
				break;
			}
			break;
		}
	}
	void DrawCursor();
	void CheckKey();

	void KeyUpdata(int Key[256]);
	void DrawGoal();

	void UseItem(int num, int target);
	void WearSoubi(int num, int target, int part);
	void UseSkill(int num, int target);
};
