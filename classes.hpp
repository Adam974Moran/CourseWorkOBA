#include "raylib.h"
#include "iostream"
#include "fstream"
#include <random>
#include <string>
#include <time.h>
#include <cmath>
#include <thread>

using namespace std;


/*
File structure:
12 34 23 5 2023
1				||| LINE FOR HERO TYPE
234
{				||| '{' SYMBOL THAT MEANS BEGINNING OF ITEM LIST
1.2.10.23
3.3.56			||| [ITEM CLASS].[ITEM TYPE].[AMMOUNT OF ITEMS]
2.5 45
}				||| '}' SYMBOL THAT MEANS ENDING OF ITEM LIST
*/

struct DataToSave {
	int* timeAndDate = new int[5],
		characterType,			// '1' - knight, '2' - elf, '3' - dworf
		ammountOfSteps = 0,
		ammOfFood,
		maxAmmIncHP,
		ammOfExtraDamage,
		incMaxHP;
};


int randomNum(int min, int max) {
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> dist(min, max);
	return dist(gen);
}


// ||||||||||||||||||||||||||||||||||||||||||
//		HERE IS THE ZONE OF GAME ITEMS
// ||||||||||||||||||||||||||||||||||||||||||


class Food {
private:
	Texture2D foodTexture = LoadTexture("./GameImages/MAINGAMEPROC/Inventory/Food.png");
	Vector2 position = { 45, 94 };
public:
	int ammOfFood, maxAmmIncHP;
	Food(int exAmmOfFood = 0, int exMaxAmmIncHp = 0) {
		this->ammOfFood = exAmmOfFood;
		this->maxAmmIncHP = exMaxAmmIncHp;
	}
	void show() {
		DrawTextureEx(foodTexture, position, 0.0, 2.0, WHITE);
		DrawText((to_string(this->maxAmmIncHP).c_str()), position.x, position.y, 30.0, WHITE);
		DrawText((to_string(this->ammOfFood).c_str()), position.x, position.y+122, 30.0, WHITE);
	}

	void chestCheck(int h_x, int h_y) {
		int random = randomNum(1, 4);
		this->maxAmmIncHP += random * 5;
		random = randomNum(0, 20);
		this->ammOfFood += random;
		BeginDrawing();
		if (random != 0) {
			DrawText(("+picked food(" + to_string(random) + ")").c_str(), h_x, h_y - 50, 20, WHITE);
		}
	}

	int takeFood() {
		if (this->ammOfFood > 0) {
			this->ammOfFood--;
			return this->maxAmmIncHP;
		}
		else {
			return 0;
		}
	}

	~Food() {
		UnloadTexture(foodTexture);
	}
};


class Weapons {
private:
	Texture2D weaponsTexture = LoadTexture("./GameImages/MAINGAMEPROC/Inventory/Weapons.png");
	Vector2 position = { 45, 276 };
public:
	int ammOfExtraDamage;
	Weapons(int exAmmOfExtraDamage = 0) {
		this->ammOfExtraDamage = exAmmOfExtraDamage;
	}

	void show() {
		DrawTextureEx(weaponsTexture, position, 0.0, 2.0, WHITE);
		DrawText((to_string(this->ammOfExtraDamage).c_str()), position.x, position.y, 30.0, WHITE);
	}

	int chestCheck(int h_x, int h_y) {
		int random = randomNum(1, 2);
		this->ammOfExtraDamage += random * 10;
		DrawText("+weapons upgrade", h_x, h_y - 10, 20, WHITE);
		EndDrawing();
		this_thread::sleep_for(chrono::milliseconds(2000));
		return this->ammOfExtraDamage;
	}

	~Weapons() {
		UnloadTexture(weaponsTexture);
	}
	
};


class Armory {
private:
	Texture2D armoryTexture = LoadTexture("./GameImages/MAINGAMEPROC/Inventory/Armory.png");
	Vector2 position = { 45, 458 };
public:
	int incMaxHP;
	Armory(int exIncMaxHp = 0) {
		this->incMaxHP = exIncMaxHp;
	}
	
	void show() {
		DrawTextureEx(armoryTexture, position, 0.0, 2.0, WHITE);
		DrawText((to_string(this->incMaxHP).c_str()), position.x, position.y, 30.0, WHITE);
	}
	
	int chestCheck(int h_x, int h_y) {
		int random = randomNum(1, 2);
		this->incMaxHP += random * 10;
		DrawText("+armory upgrade", h_x, h_y - 30, 20, WHITE);
		return this->incMaxHP;
	}

	~Armory() {
		UnloadTexture(armoryTexture);
	}
};


// |||||||||||||||||||||||||||||||||||||||||||||
//		HERE IS THE ZONE OF GAME CHARACTERS
// |||||||||||||||||||||||||||||||||||||||||||||

class Boss {
private:
	Texture2D texture[4];
	Texture2D krackenMainTexture;
	Texture2D emblemTexture;
	int ammOfHP, textureNum, step;
	float scale, emblemScale;
	Vector2 krackenPos;
	Vector2 emblemPos;
public:
	int ammOfDamage;
	Boss() {
		this->texture[0] = LoadTexture("./GameImages/MAINGAMEPROC/BossFight/BOSS1.png");
		this->texture[1] = LoadTexture("./GameImages/MAINGAMEPROC/BossFight/BOSS2.png");
		this->texture[2] = LoadTexture("./GameImages/MAINGAMEPROC/BossFight/BOSS3.png");
		this->texture[3] = LoadTexture("./GameImages/MAINGAMEPROC/BossFight/BOSS2.png");
		this->krackenMainTexture = texture[0];
		this->emblemTexture = LoadTexture("./GameImages/MAINGAMEPROC/BossFight/BossHPEmblem.png");
		this->step = 0;
		this->textureNum = 0;
		this->ammOfHP = 10000;
		this->ammOfDamage = 100;
		this->scale = 5;
		this->emblemScale = 1;
		this->krackenPos = { 300, -40 };
		this->emblemPos = { 992, 263 };
	}

	void show() {
		if (this->textureNum != 4 && step == 5) {
			this->textureNum++;
			this->step = 0;
		}
		else if(this->textureNum == 4 && step == 5) {
			this->textureNum = 0;
			this->step = 0;
		}
		else {
			this->step++;
		}
		DrawTextureEx(this->texture[this->textureNum], this->krackenPos, 0.0, this->scale, WHITE);
		DrawTextureEx(this->emblemTexture, this->emblemPos, 0.0, this->emblemScale, WHITE);
		DrawText(to_string(this->ammOfHP).c_str(), this->emblemPos.x + 90, this->emblemPos.y + 42, 30, WHITE);
	}

	bool gettingDamage(int ammOfDamage) {
		this->ammOfHP -= ammOfDamage;
		if (this->ammOfHP <= 0) {
			return true;
		}
		return false;
	}

	~Boss(){
		for (int i = 0; i < 3; i++) {
			UnloadTexture(texture[i]);
		}
		UnloadTexture(krackenMainTexture);
	}
};

class Villain {
private:
	Texture2D mainVillainTexture;
	Texture2D villainTextures[3] = { LoadTexture("./GameImages/Characters/Bogeyman.png") ,LoadTexture("./GameImages/Characters/Spider.png") ,LoadTexture("./GameImages/Characters/Tripper.png") };
	int ammountOfHealthPoints;
	Vector2 vPos;
public:
	int ammountOfDamagePoints, v_x, v_y;
	bool visible = false;
	bool attack = false;

	void generatingVillain(int villainType, int steps) {
		if (villainType == 0) {
			this->mainVillainTexture = villainTextures[villainType];
			this->ammountOfHealthPoints = 60 + steps / 10;
			this->ammountOfDamagePoints = 20 + steps / 10;
		}
		else if (villainType == 1) {
			this->mainVillainTexture = villainTextures[villainType];
			this->ammountOfHealthPoints = 40 + steps / 10;
			this->ammountOfDamagePoints = 30 + steps / 10;
		}
		else if (villainType == 2) {
			this->mainVillainTexture = villainTextures[villainType];
			this->ammountOfHealthPoints = 20 + steps / 10;
			this->ammountOfDamagePoints = 70 + steps / 10;
		}
	}

	void checkHeroPosition(int h_x, int h_y){
		cout << h_x << " " << h_y << " " << this->v_x << " " << this->v_y << endl;
		if ((abs(h_x - this->v_x) == 1 && abs(h_y - this->v_y) == 0) || (abs(h_x - this->v_x) == 0 && abs(h_y - this->v_y) == 1)) {
			this->attack = true;
		}
		else {
			this->attack = false;
		}
	}

	void startPosition(int i) {
		this->v_x = i;
		this->v_y = 0;
		this->vPos = { float(334 + i * 68), float(14) };
		this->visible = true;
	}

	void show() {
		DrawTextureEx(mainVillainTexture, vPos, 0.0, 1.0, WHITE);
	}
	
	void gettingDamage(int gainedDamage) {
		this->ammountOfHealthPoints -= gainedDamage;
		cout << this->ammountOfHealthPoints << endl;
		DrawTextureEx(mainVillainTexture, vPos, 0.0, 1.0, RED);
		if (this->ammountOfHealthPoints <= 0) {
			this->visible = false;
			this->attack = false;
			this->startPosition(100);
		}
	}

	void movingDown() {
		if (v_y < 8) {
			this->v_y++;
			this->vPos = { vPos.x, vPos.y + 68 };
		}
		else {
			this->visible = false;
		}
	}
};


class Hero {
protected:
	Texture2D mainHeroTexture;
	Texture2D heroTextures[3] = { LoadTexture("./GameImages/Characters/Knight2.png") ,LoadTexture("./GameImages/Characters/Elf2.png") ,LoadTexture("./GameImages/Characters/Dworf2.png") };
	Texture2D heroDamageTextures[3] = { LoadTexture("./GameImages/Characters/KnightDamaged.png") ,LoadTexture("./GameImages/Characters/ElfDamaged.png") ,LoadTexture("./GameImages/Characters/DworfDamaged.png") };
	int maxHealthPoints;
public:
	int	ammountOfDamagePoints;
	int ammountOfHealthPoints;
	Vector2 heroPosition = { float(334 + 4 * 68), float(14 + 6 * 68) };
	Hero(int heroType) {
		if (heroType == 1) {
			this->mainHeroTexture = heroTextures[heroType - 1];
			this->ammountOfDamagePoints = 50;
			this->ammountOfHealthPoints = 100;
			this->maxHealthPoints = 100;
		}
		else if (heroType == 2) {
			this->mainHeroTexture = heroTextures[heroType - 1];
			this->ammountOfDamagePoints = 30;
			this->ammountOfHealthPoints = 130;
			this->maxHealthPoints = 130;
		}
		else {
			this->mainHeroTexture = heroTextures[heroType - 1];
			this->ammountOfDamagePoints = 70;
			this->ammountOfHealthPoints = 70;
			this->maxHealthPoints = 70;
		}
	}
	int x = 4, y = 6;
	void movingUp() {
		y--;
		heroPosition = { this->heroPosition.x, this->heroPosition.y - 68 };
	}
	void movingDown() {
		y++;
		heroPosition = { this->heroPosition.x, this->heroPosition.y + 68 };
	}
	void movingRight() {
		x++;
		heroPosition = { this->heroPosition.x + 68, this->heroPosition.y };
	}
	void movingLeft() {
		x--;
		heroPosition = { this->heroPosition.x - 68, this->heroPosition.y };
	}
	void show() {
		DrawTextureEx(mainHeroTexture, heroPosition, 0.0, 1.0, WHITE);
	}
	void gettingDressed(int extra) {
		this->maxHealthPoints += extra;
	}
	void useWeapon(int extra) {
		this->ammountOfDamagePoints += extra;
	}
	void eatSomething(int extra) {
		this->ammountOfHealthPoints += extra;
		if (this->ammountOfHealthPoints > this->maxHealthPoints) {
			this->ammountOfHealthPoints = this->maxHealthPoints;
		}
	}
	bool gettingDammage(int ammOfDamage) {
		this->ammountOfHealthPoints -= ammOfDamage;
		DrawTextureEx(mainHeroTexture, heroPosition, 0.0, 1.0, RED);
		if (this->ammountOfHealthPoints <= 0) {
			return true;
		}
		return false;
	}
};


// ||||||||||||||||||||||||||||||||||||||||
//		HERE IS THE ZONE OF GAME MAP
// ||||||||||||||||||||||||||||||||||||||||


class Chunk {
private:
	Texture2D mainChunkTexture{};
	float x, y;
	Texture2D textures[5] = { LoadTexture("./GameImages/MAINGAMEPROC/Chunks/Chunk0.png"), LoadTexture("./GameImages/MAINGAMEPROC/Chunks/Chunk1.png"), LoadTexture("./GameImages/MAINGAMEPROC/Chunks/Chunk2.png"), LoadTexture("./GameImages/MAINGAMEPROC/Chunks/Chunk4.png"), LoadTexture("./GameImages/MAINGAMEPROC/Chunks/Chunk3.png") };
public:
	int textureNum;
	void setCoordinates(int i, int j) {
		this->x = float(334 + i * 68);
		this->y = float(14 + j * 68);
	}
	void changeChunkTexture(int chunkNum) {
		this->textureNum = chunkNum;
		this->mainChunkTexture = textures[chunkNum];
	}
	void changeChunkTexture(Texture2D texture) {
		this->mainChunkTexture = texture;
	}
	void show() {
		DrawTextureEx(this->mainChunkTexture, { this->x, this->y }, 0.0, 1.0, WHITE);
	}
	~Chunk() {
		UnloadTexture(mainChunkTexture);
		for (int i = 0; i < 3; i++) {
			UnloadTexture(textures[i]);
		}
	}
};


// |||||||||||||||||||||||||||||||||||||||||||||
//		HERE IS THE ZONE OF SPECIAL CLASSES
// |||||||||||||||||||||||||||||||||||||||||||||


class button {
protected:
	Texture2D buttonTexture;
	float button_x,
		button_y,
		button_scale;
public:
	button(const char* textureAdress, float x, float y, float scale) {
		this->buttonTexture = LoadTexture(textureAdress);
		this->button_x = x;
		this->button_y = y;
		this->button_scale = scale;
	}
	void show() {
		DrawTextureEx(this->buttonTexture, { this->button_x, this->button_y }, 0.0f, this->button_scale, WHITE);
	}
	Rectangle rectangleButton() {
		Rectangle buttonBounds = { this->button_x, this->button_y, this->buttonTexture.width * this->button_scale, this->buttonTexture.height * this->button_scale };
		return buttonBounds;
	}
	~button() {
		UnloadTexture(buttonTexture);
	}
};

class TickButton : public button {
public:
	int tickButtonStatus; // 0 - TickOff, 1 - TickOn
	TickButton(const char* textureAdress, float x, float y, float scale) : button(textureAdress, x, y, scale) {
		this->buttonTexture = LoadTexture(textureAdress);
		this->button_x = x;
		this->button_y = y;
		this->button_scale = scale;
		this->tickButtonStatus = 0;
	}
	void changeTickStatus(int tickButtonStatus) {
		if (tickButtonStatus == 0) {
			this->tickButtonStatus = 0;
			this->buttonTexture = LoadTexture("./GameImages/CreatingMenu/TickOff.png");
		}
		else {
			this->tickButtonStatus = 1;
			this->buttonTexture = LoadTexture("./GameImages/CreatingMenu/TickOn.png");
		}
	}
};

int* currentTime() {
	struct tm timeinfo;
	time_t rawtime;
	time(&rawtime);
	localtime_s(&timeinfo, &rawtime);
	int* datetime_arr = new int[5];
	datetime_arr[0] = timeinfo.tm_hour;
	datetime_arr[1] = timeinfo.tm_min;
	datetime_arr[2] = timeinfo.tm_mday;
	datetime_arr[3] = timeinfo.tm_mon + 1;
	datetime_arr[4] = timeinfo.tm_year + 1900;
	return datetime_arr;
}

class SavingSlot {
private:
	Texture2D slotTexture;
	int* slotTimeAndDate = new int[5];
	float slot_x,
		slot_y,
		slot_scale;
	string slotText;
public:
	string filename;
	DataToSave dataToSave;
	int slotStatus;	//0 - empty slot, 1 - this game exists
	SavingSlot(const char* textureAdress, float x, float y, float scale, string filename, int slotNum) {
		this->slotTexture = LoadTexture(textureAdress);
		this->slot_x = x;
		this->slot_y = y;
		this->slot_scale = scale;

		this->filename = filename;
		ifstream file(filename);
		if (file.peek() == ifstream::traits_type::eof()) {
			this->slotStatus = 0;
			for (int i = 0; i < 5; i++) {
				slotTimeAndDate[i] = 0;
			}
		}
		else {
			this->slotStatus = 1;
			file.seekg(0, ios_base::beg);
			for (int i = 0; i < 5; i++) {
				file >> slotTimeAndDate[i];
			}
		}
		this->slotText = this->slotText + "SLOT " + to_string(slotNum) + ' ' + to_string(this->slotTimeAndDate[0]) + ':' + to_string(this->slotTimeAndDate[1]) + ' ' + to_string(this->slotTimeAndDate[2]) + '.' + to_string(this->slotTimeAndDate[3]) + '.' + to_string(this->slotTimeAndDate[4]);

		file.close();
	}

	void clearFile() {
		ofstream file;
		file.open(filename, ios::out | ios::trunc);
		file.close();
	}

	void show() {
		DrawTextureEx(this->slotTexture, { this->slot_x, this->slot_y }, 0.0f, this->slot_scale, WHITE);
		DrawText(this->slotText.c_str(), int(slot_x + 15.0f), int(slot_y + 15.0f), 25, WHITE);
		if (slotStatus == 0) {
			DrawText("empty slot", int(slot_x + 15.0f), int(slot_y + 50.0f), 25, WHITE);
		}
	}

	Rectangle rectangleSavingSlot() {
		Rectangle savingSlotBounds = { this->slot_x, this->slot_y, this->slotTexture.width * this->slot_scale, this->slotTexture.height * this->slot_scale };
		return savingSlotBounds;
	}

	void loadingGame() {
		ifstream file(filename);
		for (int i = 0; i < 5; i++) {
			file >> this->dataToSave.timeAndDate[i];
		}
		file >> this->dataToSave.characterType;
		file >> this->dataToSave.ammountOfSteps;
		file >> this->dataToSave.ammOfFood;
		file >> this->dataToSave.maxAmmIncHP;
		file >> this->dataToSave.ammOfExtraDamage;
		file >> this->dataToSave.incMaxHP;
	}

	void savingGame() {
		ofstream file;
		file.open(filename);

		file.seekp(0, ios_base::beg);
		for (int i = 0; i < 5; i++) {
			file << dataToSave.timeAndDate[i] << ' ';
		}
		file << "\n";
		file << this->dataToSave.characterType << "\n";
		file << this->dataToSave.ammountOfSteps << "\n";
		file << this->dataToSave.ammOfFood << "\n";
		file << this->dataToSave.maxAmmIncHP << "\n";
		file << this->dataToSave.ammOfExtraDamage << "\n";
		file << this->dataToSave.incMaxHP << "\n";

		file.close();
	}

	void prepairingSavingFile(int characterType) {
		this->dataToSave.ammountOfSteps = 0;
		this->dataToSave.characterType = characterType;
		this->dataToSave.timeAndDate = currentTime();

		ofstream file;
		file.open(filename);

		file.seekp(0, ios_base::beg);
		for (int i = 0; i < 5; i++) {
			file << dataToSave.timeAndDate[i] << ' ';
		}
		file << "\n";
		file << dataToSave.characterType << "\n";
		file << dataToSave.ammountOfSteps << "\n";
		file << 0 << "\n";
		file << 0 << "\n";
		file << 0 << "\n";
		file << 0 << "\n";
		

		file.close();
	}


	~SavingSlot() {
		UnloadTexture(slotTexture);
	}
};