#include "define.h"

Menu_c::Menu_c()
{
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
}

void Menu_c::DrawBack()
{
}

void Menu_c::DrawLeft()
{
	printfDx("マップ");
	printfDx("ステータス");
	printfDx("装備");
	printfDx("アイテム");
	printfDx("ライブラリ");
	printfDx("セーブ");
	printfDx("オプション");
	printfDx("プレイ時間");
	printfDx("現在のシナリオ");
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
}
