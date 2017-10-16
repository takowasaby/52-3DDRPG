#include "define.h"

Menu_c::Menu_c() :
	depth(0), 
	mode(0), mscenario(0),
	mdir(0), mx(0), my(0),
	drawCount(0),
	itemType(0), soubiType(0),
	chooseChara(0), chooseItem(0), chooseSoubi(0), chooseSkill(0),
	YN(0), targetChara(0),
	windowH(0), windowW(0), menuScreen(0),
	row(0), stringX(0), stringY(0),
	xLeft(0), yUp(0)
{
	colorW = GetColor(255, 255, 255);
	LoadWindow();
}
Menu_c::~Menu_c()
{
}

void Menu_c::KeyUpdata(int Key[256])
{
	for (int i = 0; i < 256; i++) {
		mKey[i] = Key[i];
	}
}

void Menu_c::DrawGoal()
{
	int drawCount;

	for (int i = 0; i < EVENT_SIZE; i++) {
		drawCount += GData.GetEventFlag(mscenario, i);
	}

	printfDx("%s");
}

void Menu_c::MenuAll()
{
	clsDx();

	DrawLeft();
	DrawRight();
	DrawCursor();
	CheckKey();

	printfDx("\nMode:%d, ", mode);
	printfDx("ItemType:%d, ", itemType);
	printfDx("SoubiType:%d, ", soubiType);
	printfDx("CChara:%d, ", chooseChara);
	printfDx("CItem:%d, ", chooseItem);
	printfDx("CSoubi:%d, ", chooseSoubi);
	printfDx("CSkill:%d, ", chooseSoubi);
	printfDx("YN:%d, ", YN);
	printfDx("targetChara:%d, ", targetChara);
	printfDx("drawCount:%d, ", drawCount);
	printfDx("depth:%d, ", depth);
}

void Menu_c::DrawBack()
{
}
void Menu_c::DrawLeft()
{
	DrawExtendGraph(60, 40, 161, 321, windowH, TRUE);
	DrawExtendGraph(60, 320, 161, 441, windowH, TRUE);

	row = 40;
	stringX = 65;
	stringY = 45;

	DrawFormatString(stringX, stringY + row * 0, colorW, "マップ");
	DrawFormatString(stringX, stringY + row * 1, colorW, "ステータス");
	DrawFormatString(stringX, stringY + row * 2, colorW, "装備");
	DrawFormatString(stringX, stringY + row * 3, colorW, "アイテム");
	DrawFormatString(stringX, stringY + row * 4, colorW, "ライブラリ");
	DrawFormatString(stringX, stringY + row * 5, colorW, "セーブ");
	DrawFormatString(stringX, stringY + row * 6, colorW, "オプション");

	row = 50;
	stringX = 65;
	stringY = 325;

	DrawFormatString(stringX, stringY + row * 0, colorW, "プレイ時間");
	DrawFormatString(stringX, stringY + row * 1, colorW, "シナリオ");
}
void Menu_c::DrawRight()
{
	drawCount = 0;

	switch (depth) {
	case 0:
	case 1:
		switch (mode) {
		case map:
//			DrawGoal	
			DrawExtendGraph(160, 40, 581, 441, windowW, TRUE);

			mscenario = GData.GetScenario();
			mdir = GData.GetDir();
			mx = GData.GetDungeonX();
			my = GData.GetDungeonY();
			for (int i = 0; i < MAP_SIZE_X; i++) {
				for (int j = 0; j < MAP_SIZE_Y; j++) {
					mwallType[i][j] = GData.GetWallType(i, j);
				}
			}

			DrawBox(MENU_MAP_LEFT, MENU_MAP_UP, MENU_MAP_LEFT + (MENU_MAP_SIZE + 2) * MAP_SIZE_X + 2, MENU_MAP_UP + (MENU_MAP_SIZE + 2) * MAP_SIZE_Y + 2, 0, TRUE);

			for (int i = 0; i < 25; i++) {
				for (int j = 0; j < 25; j++) {
					xLeft = MENU_MAP_LEFT + 2 + j * (MENU_MAP_SIZE + 2);
					yUp = MENU_MAP_UP + 2 + i * (MENU_MAP_SIZE + 2);

					switch (mwallType[j][i]) {
					case 1: DrawBox(xLeft, yUp, xLeft + MENU_MAP_SIZE, yUp + MENU_MAP_SIZE, GetColor(255, 255, 255), TRUE);	break;
					case 2: DrawBox(xLeft, yUp, xLeft + MENU_MAP_SIZE, yUp + MENU_MAP_SIZE, GetColor(255, 0, 0), TRUE);		break;
					case 3: DrawBox(xLeft, yUp, xLeft + MENU_MAP_SIZE, yUp + MENU_MAP_SIZE, GetColor(0, 255, 0), TRUE);		break;
					case 4: DrawBox(xLeft, yUp, xLeft + MENU_MAP_SIZE, yUp + MENU_MAP_SIZE, GetColor(0, 0, 255), TRUE);		break;
					}
				}
			}

			xLeft = MENU_MAP_LEFT + 2 + mx * (MENU_MAP_SIZE + 2);
			yUp = MENU_MAP_UP + 2 + my * (MENU_MAP_SIZE + 2);
			switch (mdir) {
			case 0:	DrawTriangle(xLeft, yUp + MENU_MAP_SIZE, xLeft + MENU_MAP_SIZE / 2, yUp, xLeft + MENU_MAP_SIZE, yUp + MENU_MAP_SIZE, GetColor(255, 255, 0), TRUE); break;
			case 1: DrawTriangle(xLeft, yUp, xLeft + MENU_MAP_SIZE, yUp + MENU_MAP_SIZE / 2, xLeft, yUp + MENU_MAP_SIZE, GetColor(255, 255, 0), TRUE); break;
			case 2: DrawTriangle(xLeft, yUp, xLeft + MENU_MAP_SIZE, yUp, xLeft + MENU_MAP_SIZE / 2, yUp + MENU_MAP_SIZE, GetColor(255, 255, 0), TRUE); break;
			case 3: DrawTriangle(xLeft + MENU_MAP_SIZE, yUp, xLeft, yUp + MENU_MAP_SIZE / 2, xLeft + MENU_MAP_SIZE, yUp + MENU_MAP_SIZE, GetColor(255, 255, 0), TRUE); break;
			}
			break;
		case status:

			DrawExtendGraph(160, 40, 581, 441, windowW, TRUE);

			row = 100;
			stringX = 190;
			stringY = 80;

			for (int i = 0; i < CHARACTER_SIZE; i++) {
				if (GData.GetCharacterFlag(i)) {
					DrawFormatString(stringX, stringY + row * i, colorW, "%s HP:%d/%d MP:%d/%d \nSTR:%d VIT:%d AGI:%d INT:%d", 
						GData.GetCharacterName(i).c_str(), GData.GetCharacterPoint(i, 0), GData.GetCharacterPoint(i, 2), 
						GData.GetCharacterPoint(i, 1), GData.GetCharacterPoint(i, 3), GData.GetCharacterPoint(i, 4), 
						GData.GetCharacterPoint(i, 5), GData.GetCharacterPoint(i, 6), GData.GetCharacterPoint(i, 7));

					drawCount++;
					charaNum[drawCount - 1] = i;
				}
			}
			break;
		case soubi:
			DrawExtendGraph(160, 40, 581, 441, windowW, TRUE);
			for (int i = 0; i < CHARACTER_SIZE; i++) {
				if (GData.GetCharacterFlag(i)) {
					printfDx("\n%s ", GData.GetCharacterName(i).c_str());
					printfDx("武器:%s, ", GData.GetSoubiText(GData.GetCharacterPoint(i, 9), 0).c_str());
					printfDx("アクセ:%s, ", GData.GetSoubiText(GData.GetCharacterPoint(i, 10), 0).c_str());

					charaNum[drawCount] = i;
					drawCount++;
				}
			}
			break;
		case item:
			DrawExtendGraph(160, 40, 581, 81, windowW, TRUE);
			DrawExtendGraph(160, 80, 581, 441, windowW, TRUE);
			printfDx("消耗品");
			printfDx("だいじなもの");
			break;
		case library:
			DrawExtendGraph(160, 40, 581, 441, windowW, TRUE);
			break;
		default: 
			DrawExtendGraph(160, 40, 581, 441, windowW, TRUE);
			break;
		}
		break;
	case 2:
		switch (mode) {
		case map:
			break;
		case status:
			DrawExtendGraph(160, 40, 581, 241, windowW, TRUE);
			DrawExtendGraph(160, 240, 581, 401, windowW, TRUE);
			DrawExtendGraph(160, 400, 581, 441, windowW, TRUE);

			printfDx("\n%s ", GData.GetCharacterName(chooseChara).c_str());
			printfDx("\nHP:%d/%d ", GData.GetCharacterPoint(chooseChara, 0), GData.GetCharacterPoint(chooseChara, 2));
			printfDx("MP:%d/%d ", GData.GetCharacterPoint(chooseChara, 1), GData.GetCharacterPoint(chooseChara, 3));
			printfDx("STR:%d ", GData.GetCharacterPoint(chooseChara, 4));
			printfDx("VIT:%d ", GData.GetCharacterPoint(chooseChara, 5));
			printfDx("AGI:%d ", GData.GetCharacterPoint(chooseChara, 6));
			printfDx("INT:%d ", GData.GetCharacterPoint(chooseChara, 7));
			DrawGraph(480, 240, GData.GetCharacterPoint(chooseChara, 8), TRUE);

			for (int i = 0; i < SKILL_SIZE; i++) {
				skillNum[i] = 0;
				if (GData.GetCharacterSkillCode(chooseChara, i) == 1) {
					printfDx("\n%s, ", GData.GetSkillText(i, 0).c_str());
					skillNum[drawCount] = i;
					drawCount++;
				}
			}

			printfDx("\n%s", GData.GetSkillText(skillNum[chooseSkill], 1).c_str());
			break;

		case soubi:
			DrawExtendGraph(160, 40, 581, 81, windowW, TRUE);
			DrawExtendGraph(160, 80, 581, 401, windowW, TRUE);
			DrawExtendGraph(160, 400, 581, 441, windowW, TRUE);

			printfDx("%s", GData.GetCharacterName(chooseChara).c_str());

			for (int i = 0; i < SOUBI_SIZE; i++) {
				soubiNum[i] = 0;
				if (GData.GetSoubiFlag(i) >= 1) {
					if (soubiType == GData.GetSoubiPoint(i, 1)) {
						if (i == GData.GetCharacterPoint(chooseChara, soubiType + 9)) printfDx("E.");
						printfDx("%s, ", GData.GetSoubiText(i, 0).c_str());
						soubiNum[drawCount] = i;
						drawCount++;
					}
				}
			}

			printfDx("\n%s", GData.GetSoubiText(soubiNum[chooseSoubi], 1).c_str());
			break;

		case item:
			DrawExtendGraph(160, 40, 581, 81, windowW, TRUE);
			DrawExtendGraph(160, 80, 581, 401, windowW, TRUE);
			DrawExtendGraph(160, 400, 581, 441, windowW, TRUE);

			printfDx("消耗品");
			printfDx("だいじなもの");

			for (int i = 0; i < ITEM_SIZE; i++) {
				itemNum[i] = 0;
				if (GData.GetItemFlag(i) >= 1) {
					if (itemType == GData.GetItemPoint(i, 1)) {
						printfDx("%s, ", GData.GetItemText(i, 0).c_str());
						itemNum[drawCount] = i;
						drawCount++;
					}
				}
			}

			printfDx("\n%s", GData.GetItemText(itemNum[chooseItem], 1).c_str());
			break;

		case library:
			break;
		}
		break;
	case 3:
		DrawGraph(0, 0, menuScreen, TRUE);
		switch (mode) {
		case status:
			DrawExtendGraph(220, 140, 541, 221, windowW, TRUE);
			DrawExtendGraph(480, 220, 541, 261, windowW, TRUE);

			printfDx("\nこのスキルを使用しますか？");
			printfDx("はい　");
			printfDx("いいえ");
			break;
		case soubi:
			DrawExtendGraph(220, 140, 541, 221, windowW, TRUE);
			DrawExtendGraph(480, 220, 541, 261, windowW, TRUE);

			printfDx("\n%sを装備しますか？", GData.GetSoubiText(soubiNum[chooseSoubi], 0).c_str());
			printfDx("はい　");
			printfDx("いいえ");
			break;
		case item:
			DrawExtendGraph(220, 140, 541, 221, windowW, TRUE);
			DrawExtendGraph(480, 220, 541, 261, windowW, TRUE);

			printfDx("\nこのアイテムを使用しますか？");
			printfDx("はい　");
			printfDx("いいえ");
			break;
		}
		break;
	case 4:
		DrawGraph(0, 0, menuScreen, TRUE);
		switch (mode) {
		case status:
			DrawExtendGraph(220, 140, 541, 221, windowW, TRUE);
			DrawExtendGraph(480, 220, 541, 281, windowW, TRUE);

			printfDx("\nこのスキルを誰に使用しますか？");
			for (int i = 0; i < CHARACTER_SIZE; i++) {
				if (GData.GetCharacterFlag(i)) {
					printfDx("\n%s ", GData.GetCharacterName(i).c_str());
					drawCount++;
				}
			}
			break;
		case item:
			DrawExtendGraph(220, 140, 541, 221, windowW, TRUE);
			DrawExtendGraph(480, 220, 541, 281, windowW, TRUE);

			printfDx("\nこのアイテムを誰に使用しますか？");
			for (int i = 0; i < CHARACTER_SIZE; i++) {
				if (GData.GetCharacterFlag(i)) {
					printfDx("\n%s ", GData.GetCharacterName(i).c_str());
					drawCount++;
				}
			}
			break;
		}
		break;
	case 5:
		printfDx("MPが足りません！");
		break;
	}
}

void Menu_c::DrawCursor()
{
	DrawTriangle(cursorX - 5, cursorY - 3, cursorX + 5, cursorY, cursorX - 5, cursorY + 3, GetColor(255, 255, 255), TRUE);
}

void Menu_c::CheckKey()
{
	if (mKey[KEY_INPUT_DOWN] == 1) {
		switch (depth) {
		case 0:
			if (cursorY != limitDOWN) {
				cursorY += 20;
				mode++;
			}
			break;
		case 1:
			switch (mode) {
			case status:
				if (chooseChara < drawCount - 1) {
					chooseChara++;
				}
				break;
			case soubi:
				if (chooseChara < drawCount - 1) {
					chooseChara++;
				}
				break;
			}
			break;
		case 2:
			switch (mode) {
			case status:
				if (chooseSkill < drawCount - 1) {
					chooseSkill++;
				}
				break;
			case soubi:
				if (chooseSoubi < drawCount - 1) {
					chooseSoubi++;
				}
				break;
			case item:
				if (chooseItem < drawCount - 1) {
					chooseItem++;
				}
				break;
			}
			break;
		case 3:
			if (YN != 1) {
				YN++;
			}
			break;
		case 4:
			if (targetChara < drawCount - 1) {
				targetChara++;
			}
			break;
		}
	}
	else if (mKey[KEY_INPUT_UP] == 1) {
		switch (depth) {
		case 0:
			if (cursorY != limitUP) {
				cursorY -= 20;
				mode--;
			}
			break;
		case 1:
			switch (mode) {
			case status:
				if (chooseChara > 0) {
					chooseChara--;
				}
				break;
			case soubi:
				if (chooseChara > 0) {
					chooseChara--;
				}
				break;
			}
			break;
		case 2:
			switch (mode) {
			case status:
				if (chooseSkill > 0) {
					chooseSkill--;
				}
				break;
			case soubi:
				if (chooseSoubi > 0) {
					chooseSoubi--;
				}
				break;
			case item:
				if (chooseItem > 0) {
					chooseItem--;
				}
				break;
			}
			break;
		case 3:
			if (YN != 0) {
				YN--;
			}
			break;
		case 4:
			if (targetChara > 0) {
				targetChara--;
			}
			break;
		}
	}
	else if (mKey[KEY_INPUT_LEFT] == 1) {
		switch (depth) {
		case 0: break;
		case 1:
			switch (mode) {
			case soubi:
				if (soubiType > 0) {
					soubiType--;
				}
				break;
			case item:
				if (itemType > 0) {
					itemType--;
				}
				break;
			}
			break;
		case 2:
		case 3:
		case 4: break;
		}
	}
	else if (mKey[KEY_INPUT_RIGHT] == 1) {
		switch (depth) {
		case 0: break;
		case 1:
			switch (mode) {
			case soubi:
				if (soubiType < 1) {
					soubiType++;
				}
				break;
			case item:
				if (itemType < 1) {
					itemType++;
				}
				break;
			}
			break;
		case 2:
		case 3:
		case 4: break;
		}
	}
	else if (mKey[KEY_INPUT_Z] == 1) {
		switch (mode) {
		case status:
			switch (depth) {
			case 0:
				depth++;
				break;
			case 1:
				depth++;
				break;
			case 2: 
				DeleteGraph(menuScreen);
				SaveDrawScreen(0, 0, 640, 480, "resource/MenuScreen.bmp");
				menuScreen = LoadGraph("resource/MenuScreen.bmp");
				depth++; 
				break;
			case 3:
				if (YN == 0) {
					if (GData.GetSkillPoint(skillNum[chooseSkill], 6) == 0) {
						depth++;
					}
					else {
						if (UseSkill(skillNum[chooseSkill], -1, chooseChara) == FALSE) {
							depth = 5;
						}
					}
				}
				else {
					depth--;
				}
				break;
			case 4:
				if (UseSkill(skillNum[chooseSkill], targetChara, chooseChara) == FALSE) {
					depth = 5;
				}
				break;
			case 5:
				depth = 2;
				break;
			}
			break;
		case soubi:
			switch (depth) {
			case 0:
				depth++;
				break;
			case 1:
				depth++;
				break;
			case 2:
				DeleteGraph(menuScreen);
				SaveDrawScreen(0, 0, 640, 480, "resource/MenuScreen.bmp");
				menuScreen = LoadGraph("resource/MenuScreen.bmp");
				depth++;
				break;
			case 3:
				if (YN == 0) {
					GData.SetCharacterPoint(charaNum[chooseChara], 9, soubiNum[chooseSoubi]);
				}
				else {
					depth--;
				}
				break;
			}
			break;
		case item:
			switch (depth) {
			case 0:
				depth++;
				break;
			case 1:
				depth++;
				break;
			case 2:
				DeleteGraph(menuScreen);
				SaveDrawScreen(0, 0, 640, 480, "resource/MenuScreen.bmp");
				menuScreen = LoadGraph("resource/MenuScreen.bmp");
				depth++;
				break;
			case 3:
				if (YN == 0) {
					if (GData.GetItemPoint(itemNum[chooseItem], 6) == 0) {
						depth++;
					}
					else {
						UseItem(itemNum[chooseItem], -1);
					}
				}
				else {
					depth--;
				}
				break;
			case 4:
				UseItem(itemNum[chooseItem], targetChara);
				break;
			}
			break;
			//		case library:
		case save:
			GData.SceneRequest(1, 3);
			break;
		case option:
			GData.SceneRequest(1, 5);
			break;
		}
	}
	else if (mKey[KEY_INPUT_X] == 1) {
		switch (depth) {
		case 0: break;
		case 1:
			itemType = 0;
			soubiType = 0;
			chooseChara = 0;
			depth--;
			break;
		case 2:
			chooseItem = 0;
			chooseSoubi = 0;
			chooseSkill = 0;
			depth--;
			break;
		case 3:
			YN = 0;
			depth--;
			break;
		case 4:
			targetChara = 0;
			depth--;
			break;
		case 5:
			YN = 0;
			targetChara = 0;
			depth = 2;
			break;
		}
	}
}

void Menu_c::UseItem(int num, int target)
{
	int x = 0;
	int y = 0;
	int effect1 = GData.GetItemPoint(num, 2);
	int effect2 = GData.GetItemPoint(num, 3);

	if (GData.GetItemPoint(num, 6) == 1) {
		for (int i = 0; i < CHARACTER_SIZE; i++) {
			if (GData.GetCharacterFlag(i) == 1) {
				x = GData.GetCharacterPoint(i, effect1 + 2);
				if (GData.GetItemPoint(num, 3) != -1) {
					y = GData.GetCharacterPoint(i, effect2 + 2);
				}

				x += GData.GetItemPoint(num, 4);
				if (effect1 <= 1 && x > GData.GetCharacterPoint(i, effect1)) {
					x = GData.GetCharacterPoint(i, effect1);
				}
				y += GData.GetItemPoint(num, 5);
				if (effect2 <= 1 && y > GData.GetCharacterPoint(i, effect2)) {
					y = GData.GetCharacterPoint(i, effect2);
				}

				GData.SetCharacterPoint(i, effect1 + 2, x);
				if (GData.GetItemPoint(num, 3) != -1) {
					GData.SetCharacterPoint(i, effect2 + 2, y);
				}
			}
		}
	}
	else {
		x = GData.GetCharacterPoint(target, effect1 + 2);
		if (GData.GetItemPoint(num, 3) != -1) {
			y = GData.GetCharacterPoint(target, effect2 + 2);
		}

		x += GData.GetItemPoint(num, 4);
		if (effect1 <= 1 && x > GData.GetCharacterPoint(target, effect1)) {
			x = GData.GetCharacterPoint(target, effect1);
		}
		y += GData.GetItemPoint(num, 5);
		if (effect2 <= 1 && y > GData.GetCharacterPoint(target, effect2)) {
			y = GData.GetCharacterPoint(target, effect2);
		}

		GData.SetCharacterPoint(target, effect1 + 2, x);
		if (GData.GetItemPoint(num, 3) != -1) {
			GData.SetCharacterPoint(target, effect2 + 2, y);
		}
	}

	GData.CalcItemFlag(num, -1);
}
void Menu_c::WearSoubi(int num, int target, int part)
{
	GData.SetCharacterPoint(target, part + 9, num);
}
bool Menu_c::UseSkill(int num, int target, int user)
{
	int x = 0;
	int mp = GData.GetCharacterPoint(user, 3);
	int effect = GData.GetSkillPoint(num, 2);
	if (mp < GData.GetSkillPoint(num, 1)) {
		return FALSE;
	}

	if (GData.GetSkillPoint(num, 6) == 1) {
		for (int i = 0; i < CHARACTER_SIZE; i++) {
			if (GData.GetCharacterFlag(i) == 1) {
				x = GData.GetCharacterPoint(i, effect + 2);

				x += GData.GetSkillPoint(num, 4);
				if (effect <= 1 && x > GData.GetCharacterPoint(i, effect)) {
					x = GData.GetCharacterPoint(i, effect);
				}

				GData.SetCharacterPoint(i, effect + 2, x);
			}
		}
	}
	else {
		x = GData.GetCharacterPoint(target, effect + 2);

		x += GData.GetSkillPoint(num, 4);
		if (effect <= 1 && x > GData.GetCharacterPoint(target, effect)) {
			x = GData.GetCharacterPoint(target, effect);
		}

		GData.SetCharacterPoint(target, effect + 2, x);
	}
	mp -= GData.GetSkillPoint(num, 1);
	GData.SetCharacterPoint(user, 3, mp);

	return TRUE;
}

void Menu_c::LoadWindow()
{
	windowH = LoadGraph("resource/window/window_H.png");
	windowW = LoadGraph("resource/window/window_W.png");
}
