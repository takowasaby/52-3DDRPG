#include "menu.h"

Menu_c::Menu_c()
{
}

Menu_c::~Menu_c()
{
}

<<<<<<< HEAD
=======
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

>>>>>>> data
void Menu_c::MenuAll()
{
	DrawLeft();
	DrawRight();
	DrawCursor();
	CheckKey();
}

void Menu_c::DrawBack()
{
}

void Menu_c::DrawLeft()
{
	DrawFormatString();
}

void Menu_c::DrawRight()
{
<<<<<<< HEAD

=======
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
					yUp =  MENU_MAP_UP + 1 + i * 16;

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
						printfDx("%s, " ,GData.GetItemText(i, 0));
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
>>>>>>> data
}

void Menu_c::DrawCursor()
{
}

void Menu_c::CheckKey()
{
<<<<<<< HEAD
=======
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
				if (chooseChara != drawCount) {
					chooseChara++;
				}
				break;
			case soubi:
				if (chooseChara != drawCount) {
					chooseChara++;
				}
				break;
			}
			break;
		case 2:
			switch (mode) {
			case status:
				if (chooseSkill != drawCount) {
					chooseSkill++;
				}
				break;
			case soubi:
				if (chooseSoubi != drawCount) {
					chooseSoubi++;
				}
				break;
			case item:
				if (chooseItem != drawCount) {
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
			if (targetChara != drawCount) {
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
				if (chooseChara != 0) {
					chooseChara--;
				}
				break;
			case soubi:
				if (chooseChara != 0) {
					chooseChara--;
				}
				break;
			}
			break;
		case 2:
			switch (mode) {
			case status:
				if (chooseSkill != 0) {
					chooseSkill--;
				}
				break;
			case soubi:
				if (chooseSoubi != 0) {
					chooseSoubi--;
				}
				break;
			case item:
				if (chooseItem != 0) {
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
			if (targetChara != 0) {
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
				if (soubiType != 0) {
					soubiType--;
				}
				break;
			case item:
				if (itemType != 0) {
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
				if (soubiType != 1) {
					soubiType++;
				}
				break;
			case item:
				if (itemType != 1) {
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
			case 1: 
			case 2: depth++; break;
			case 3: 
				if (YN == 0) {
					if (GData.GetSkillPoint(skillNum[chooseSkill], 6) == 0) {
						depth++;
					}
					else {
						UseSkill(skillNum[chooseSkill], -1);
					}
				}
				else {
					depth--;
				}
				break;
			case 4:
				UseSkill(itemNum[chooseSkill], targetChara);
				break;
			}
			break;
		case soubi:
			switch (depth) {
			case 0:
			case 1:
			case 2: depth++; break;
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
			case 1:
			case 2: depth++; break;
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
			*mMode = 1;
			*mTitle_scene = 3;
			break;
		case option:
			*mMode = 1;
			*mTitle_scene = 4;
			break;
		}
	}
	else if (mKey[KEY_INPUT_X] == 1) {
		if (depth != 0) {
			depth--;
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
	} else {
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
}

void Menu_c::WearSoubi(int num, int target, int part)
{
	GData.SetCharacterPoint(target, part + 9, num);
}

void Menu_c::UseSkill(int num, int target)
{
	int x = 0;
	int effect = GData.GetSkillPoint(num, 2);

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
>>>>>>> data
}
