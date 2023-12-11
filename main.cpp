#include "classes.hpp"


Chunk** generatingMap(Chunk** chunks) {
    int randomNum;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(0, 100);
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            randomNum = dist(gen);
            if ((randomNum < 40 || (i == 1 || i == 4)) || (i == 4 && j == 4)) {
                chunks[i][j].changeChunkTexture(0);
            }
            else if ((randomNum > 39 && randomNum < 80 || (i == 1 || i == 4)) || (i == 4 && j == 4)) {
                chunks[i][j].changeChunkTexture(1);
            }
            else if (randomNum > 79 && randomNum < 90 && (i != 1 && i != 4)){
                chunks[i][j].changeChunkTexture(2);
            }
            else if (randomNum > 89 && (i != 1 && i != 4)) {
                chunks[i][j].changeChunkTexture(3);
            }
            if (i == 0 || i == 8) {
                chunks[i][j].changeChunkTexture(2);
            }

        }
    }
    return chunks;
}


Chunk** chunksReload(Chunk** chunk, int & chestLines, int steps, bool & chestOpened, int & villainLines, Villain * villain, SavingSlot * slot) {
    int random;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(0, 110);
    for (int j = 8; j > 0; j--) {
        for (int i = 0; i < 9; i++) {
            chunk[i][j].changeChunkTexture(chunk[i][j - 1].textureNum);
        }
    }
    for (int i = 1; i < 8; i++) {
        random = dist(gen);
        if (random < 40) {
            chunk[i][0].changeChunkTexture(0);
            if (villainLines > 15) {
                int random2 = randomNum(0, 5);
                if (random2 < 3) {
                    villain[random2].startPosition(i);
                    villain[random2].generatingVillain(random2, slot->dataToSave.ammountOfSteps);
                    villainLines = 0;
                }
            }
        }
        else if (random > 39 && random < 80) {
            chunk[i][0].changeChunkTexture(1);
            if (villainLines > 15) {
                int random2 = randomNum(0, 5);
                if (random2 < 3) {
                    villain[random2].startPosition(i);
                    villain[random2].generatingVillain(random2, slot->dataToSave.ammountOfSteps);
                    villainLines = 0;
                }
            }
        }
        else if ((random > 79 && random< 90) && (i != 1 && i != 4)) {
            chunk[i][0].changeChunkTexture(2);
        }
        else if ((random> 89 && random< 101) && (i != 1 && i != 4)) {
            chunk[i][0].changeChunkTexture(3);
        }
        else if ((random> 100 && random < 111) && chestLines > 45) {
            if (chunk[i][1].textureNum != 4) {
                chunk[i][0].changeChunkTexture(4);
                chestLines = 0;
                chestOpened = false;
            }
        }
    }
    chestLines++;
    villainLines = villainLines + 1;
    return chunk;
}


Chunk** bossFightChunkGeneration(Chunk** chunk, Texture2D*& texture, int num, int& stage, int hero_x, int hero_y) {
    if (num == 1 && stage == 0) { //small horizontal lines
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                chunk[i][j].changeChunkTexture(texture[0]);
                chunk[i][j].textureNum = 7;
            }
        }
        if (hero_y % 2 == 0) {
            for (int i = 0; i < 9; i++) {
                for (int j = 1; j < 9; j += 2) {
                    chunk[i][j].changeChunkTexture(texture[stage]);
                    chunk[i][j].textureNum = 8;
                }
            }
        }
    }
    else if (num == 1 && stage != 0) {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (chunk[i][j].textureNum == 8) {
                    chunk[i][j].changeChunkTexture(texture[stage]);
                    if (stage == 4) {
                        chunk[i][j].textureNum = 9;
                    }
                }
            }
        }
    }
    else if (num == 2 && stage == 0) { //big horizontal lines
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                chunk[i][j].changeChunkTexture(texture[0]);
                chunk[i][j].textureNum = 7;
            }
        }
        int y[4] = { hero_y + 2, hero_y + 1, hero_y - 1, hero_y - 2 };
        for (int k = 0; k < 4; k++) {
            if (y[k] > 8 || y[k] < 0) {
                y[k] = hero_y;
            }
        }
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (j == y[0] || j == y[1] || j == y[2] || j == y[3] || j == hero_y) {
                    chunk[i][j].changeChunkTexture(texture[stage]);
                    chunk[i][j].textureNum = 8;
                }
            }
        }
    }
    else if (num == 2 && stage != 0) {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (chunk[i][j].textureNum == 8) {
                    chunk[i][j].changeChunkTexture(texture[stage]);
                    if (stage == 4) {
                        chunk[i][j].textureNum = 9;
                    }
                }
            }
        }
    }
    else if (num == 3 && stage == 0) { //big vertical lines
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                chunk[i][j].changeChunkTexture(texture[0]);
                chunk[i][j].textureNum = 7;
            }
        }
        int x[4] = { hero_x + 2, hero_x + 1, hero_x - 1, hero_x - 2 };
        for (int k = 0; k < 4; k++) {
            if (x[k] > 8 || x[k] < 0) {
                x[k] = hero_x;
            }
        }
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (j == x[0] || j == x[1] || j == x[2] || j == x[3] || j == hero_x) {
                    chunk[i][j].changeChunkTexture(texture[stage]);
                    chunk[i][j].textureNum = 8; 
                }
            }
        }
    }
    else if (num == 3 && stage != 0) {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (chunk[i][j].textureNum == 8) {
                    chunk[i][j].changeChunkTexture(texture[stage]);
                    if (stage == 4) {
                        chunk[i][j].textureNum = 9;
                    }
                }
            }
        }
    }
    stage = stage + 1;
    return chunk;
}

void saveingEverything(SavingSlot* slot, Food* food, Weapons* weapons, Armory* armory) {
    slot->dataToSave.ammOfFood = food->ammOfFood;
    slot->dataToSave.maxAmmIncHP = food->maxAmmIncHP;
    slot->dataToSave.ammOfExtraDamage = weapons->ammOfExtraDamage;
    slot->dataToSave.incMaxHP = armory->incMaxHP;
    slot->savingGame();
}

bool YouLose(int WindowWidth, SavingSlot * slot) {
    //PREPAIRING BACKGROUND
    Texture2D youLose = LoadTexture("./GameImages/MAINGAMEPROC/YouLose.png");
    float youLoseScale = (float)WindowWidth / youLose.width;
    Vector2 youLosePos = { 0, 0 };


    int cycle = 0;
    while (!WindowShouldClose()) {
        BeginDrawing();
        DrawTextureEx(youLose, youLosePos, 0.0, 10.0, WHITE);
        if (cycle > 300) {
            break;
        }
        EndDrawing();
        cycle++;
    }

    UnloadTexture(youLose);

    slot->clearFile();
    return false;
}

bool YouWin(int WindowWidth, SavingSlot* slot) {
    //PREPAIRING BACKGROUND
    Texture2D youWin = LoadTexture("./GameImages/MAINGAMEPROC/YouWin.png");
    float youWinScale = (float)WindowWidth / youWin.width;
    Vector2 youWinPos = { 0, 0 };


    int cycle = 0;
    while (!WindowShouldClose()) {
        BeginDrawing();
        DrawTextureEx(youWin, youWinPos, 0.0, 10.0, WHITE);
        if (cycle > 300) {
            break;
        }
        EndDrawing();
        cycle++;
    }

    UnloadTexture(youWin);

    slot->clearFile();
    return false;
}

bool GameOverWindow(int WindowWidth, SavingSlot* slot) {
    //PREPAIRING BACKGROUND
    Texture2D gameOver = LoadTexture("./GameImages/MAINGAMEPROC/GameOver2.png");
    float gameOverScale = (float)WindowWidth / gameOver.width;
    Vector2 gameOverPos = { 0, 0 };


    int cycle = 0;
    while (!WindowShouldClose()) {
        BeginDrawing();
        DrawTextureEx(gameOver, gameOverPos, 0.0, gameOverScale, WHITE);
        if (cycle > 300) {
            break;
        }
        EndDrawing();
        cycle++;
    }

    UnloadTexture(gameOver);
    return false;
}

bool checkBossAttack(Chunk** chunk, int hero_x, int hero_y) {
    bool exit = false;
    if (chunk[hero_x][hero_y].textureNum == 9) {
        return true;
    }
    return false;
}

bool BOSSFIGHT(int WindowWidth, SavingSlot* slot, Food* food, Weapons* weapons, Armory* armory, Texture2D heart, Vector2 hPos, Hero* hero) {
    //PREAPIRING OBJECTS
    //1.Creating background:
    Texture2D backgroundImage = LoadTexture("./GameImages/MAINGAMEPROC/mainGameProc_Background.png");
    float bckgndImageScale = (float)WindowWidth / backgroundImage.width;
    Vector2 bckgndImagePos = { 0, 0 };
    //2.Creating chunks textures:
    Texture2D * chunkTexture = new Texture2D[5];
    chunkTexture[0] = LoadTexture("./GameImages/MAINGAMEPROC/BossFight/Chunk.png");
    chunkTexture[1] = LoadTexture("./GameImages/MAINGAMEPROC/BossFight/ChunkDanger1.png");
    chunkTexture[2] = LoadTexture("./GameImages/MAINGAMEPROC/BossFight/ChunkDanger2.png");
    chunkTexture[3] = LoadTexture("./GameImages/MAINGAMEPROC/BossFight/ChunkDanger3.png");
    chunkTexture[4] = LoadTexture("./GameImages/MAINGAMEPROC/BossFight/DamagedChunk.png");
    //3.Creating main scene chunks:
    int stage;
    Chunk** mainScene;
    mainScene = new Chunk * [9];
    for (int i = 0; i < 9; i++) {
        mainScene[i] = new Chunk[9];
    }
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            mainScene[i][j].changeChunkTexture(chunkTexture[0]);
            mainScene[i][j].setCoordinates(i, j);
        }
    }
    //4.Creating boss texture:
    Boss* boss = new Boss();


    stage = 0;
    int num;
    bool GameOver = false;
    bool YouWinV = false;
    while (!WindowShouldClose()) {
        BeginDrawing();
        if (YouWinV == true) {
            return YouWin(WindowWidth, slot);
        }
        else if (GameOver == true) {
            return YouLose(WindowWidth, slot);
        }
        DrawTextureEx(backgroundImage, bckgndImagePos, 0.0, bckgndImageScale, WHITE);
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                mainScene[i][j].show();
            }
        }
        DrawTextureEx(heart, hPos, 0.0, 1.0, WHITE);
        DrawText((to_string(hero->ammountOfHealthPoints) + "%").c_str(), 1105, 510, 30, WHITE);
        hero->show();
        boss->show();
        food->show();
        weapons->show();
        armory->show();



        if (IsKeyPressed(KEY_W)) { // check for damage
            if (hero->y != 3) {
                hero->movingUp();
            }
            if (stage == 5) {
                num = randomNum(1, 3);
                stage = 0;
            }
            mainScene = bossFightChunkGeneration(mainScene, chunkTexture, num, stage, hero->x, hero->y);
            if (checkBossAttack(mainScene, hero->x, hero->y)) {
                GameOver = hero->gettingDammage(boss->ammOfDamage);
            }
        }
        else if (IsKeyPressed(KEY_S)) { // check for damage
            if (hero->y != 8) {
                hero->movingDown();
            }
            if (stage == 5) {
                num = randomNum(1, 3);
                stage = 0;
            }
            mainScene = bossFightChunkGeneration(mainScene, chunkTexture, num, stage, hero->x, hero->y);
            if (checkBossAttack(mainScene, hero->x, hero->y)) {
                GameOver = hero->gettingDammage(boss->ammOfDamage);
            }
        }
        else if (IsKeyPressed(KEY_A)) { // check for damage
            if (hero->x != 0) {
                hero->movingLeft();
            }
            if (stage == 5) {
                num = randomNum(1, 3);
                stage = 0;
            }
            mainScene = bossFightChunkGeneration(mainScene, chunkTexture, num, stage, hero->x, hero->y);
            if (checkBossAttack(mainScene, hero->x, hero->y)) {
                GameOver = hero->gettingDammage(boss->ammOfDamage);
            }
        }
        else if (IsKeyPressed(KEY_D)) { // check for damage
            if (hero->x != 8) {
                hero->movingRight();
            }
            if (stage == 5) {
                num = randomNum(1, 3);
                stage = 0;
            }
            mainScene = bossFightChunkGeneration(mainScene, chunkTexture, num, stage, hero->x, hero->y);
            if (checkBossAttack(mainScene, hero->x, hero->y)) {
                GameOver = hero->gettingDammage(boss->ammOfDamage);
            }
        }
        else if (IsKeyPressed(KEY_UP)) { //add dammage to boss
            if (hero->y < 5) {
                YouWinV = boss->gettingDamage(hero->ammountOfDamagePoints);
            }
            if (stage == 5) {
                num = randomNum(1, 3);
                stage = 0;
            }
            mainScene = bossFightChunkGeneration(mainScene, chunkTexture, num, stage, hero->x, hero->y);
            if (checkBossAttack(mainScene, hero->x, hero->y)) {
                GameOver = hero->gettingDammage(boss->ammOfDamage);
            }
        }
        if (IsKeyPressed(KEY_E)) {
            hero->eatSomething(food->takeFood());

        }
        EndDrawing();
    }

    UnloadTexture(backgroundImage);

    return true;
}


bool MAIN_GAME_PROCESS(int WindowWidth, SavingSlot* slot, int startType = 0) {
    //PREPAIRING OBJECTS
    slot->loadingGame();
    //1.Creating background:
    Texture2D backgroundImage = LoadTexture("./GameImages/MAINGAMEPROC/mainGameProc_Background.png");
    Texture2D gameOver = LoadTexture("./GameImages/MAINGAMEPROC/GameOver2.png");
    float bckgndImageScale = (float)WindowWidth / backgroundImage.width;
    Vector2 bckgndImagePos = { 0, 0 };
    //2.Creating chunk matrix:
    Chunk** chunks;
    chunks = new Chunk * [9]();
    for (int i = 0; i < 9; i++) {
        chunks[i] = new Chunk[9]();
    }
    //3.Setting chunk coordinates:
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            chunks[i][j].setCoordinates(i, j);
        }
    }
    //4.Generating random chunk textures:
    chunks = generatingMap(chunks);
    //5.Creating hero:
    Hero* hero = new Hero(slot->dataToSave.characterType);
    //6.Creating inventory:
    Food* food = new Food(slot->dataToSave.ammOfFood, slot->dataToSave.maxAmmIncHP);
    Weapons* weapons = new Weapons(slot->dataToSave.ammOfExtraDamage);
    Armory* armory = new Armory(slot->dataToSave.incMaxHP);
    if (startType == 1) {
        hero->gettingDressed(armory->incMaxHP);
        hero->useWeapon(weapons->ammOfExtraDamage);
    }
    //7.Creating villains:
    Villain* villain = new Villain[3];
    //8.Creating health system:
    Texture2D heart = LoadTexture("./GameImages/MAINGAMEPROC/Inventory/Heart.png");
    Vector2 heartPosition = { 1068 , 458 };
    //9.Creating saving button:
    Texture2D savingButton = LoadTexture("./GameImages/MAINGAMEPROC/Inventory/SavingButton.png");
    Vector2 savingButtonPos = {1072, 50};
    Rectangle savingButtonRect = { savingButtonPos.x, savingButtonPos.y, savingButton.width, savingButton.height};

    int chestLines = 0;
    int villainLines = 0;
    bool chestOpened = false;
    bool GameOver = false;
    while (!WindowShouldClose()) {
        if (slot->dataToSave.ammountOfSteps == 100) {    //CHANGE BOSS FIGHT STEP TO START
            ClearBackground(RAYWHITE);
            return GameOver = BOSSFIGHT(WindowWidth, slot, food, weapons, armory, heart, heartPosition, hero);
        }
        BeginDrawing();
        //SHOWING ALL MAIN MENU ELEMENTS
        ClearBackground(RAYWHITE);
        if (GameOver == false) {
            DrawTextureEx(backgroundImage, bckgndImagePos, 0.0f, bckgndImageScale, WHITE);
        }
        else {
            return GameOverWindow(WindowWidth, slot);
        }
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                chunks[i][j].show();
            }
        }
        hero->show();
        DrawText(to_string(slot->dataToSave.ammountOfSteps).c_str(), (1280-(to_string(slot->dataToSave.ammountOfSteps).length() * 22))/2, 30, 24, WHITE);
        food->show();
        weapons->show();
        armory->show();
        for (int i = 0; i < 3; i++) {
            if (villain[i].visible == true) {
                villain[i].show();
            }
        }
        DrawTextureEx(heart, heartPosition, 0.0, 1.0, WHITE);
        DrawText((to_string(hero->ammountOfHealthPoints) + "%").c_str(), 1105, 510, 30, WHITE);
        for (int i = 0; i < 3; i++) {
            if(villain[0].visible == true || villain[1].visible == true || villain[2].visible == true)
            villain[i].checkHeroPosition(hero->x, hero->y);
        }
        DrawTextureEx(savingButton, savingButtonPos, 0.0, 1.0, WHITE);

        //MAIN ACTIONS
        if (IsKeyPressed(KEY_W)) {
            if (chunks[hero->x][hero->y - 1].textureNum != 2 && chunks[hero->x][hero->y - 1].textureNum != 3 && chunks[hero->x][hero->y - 1].textureNum != 4 && villain[0].attack == false && villain[1].attack == false && villain[2].attack == false && hero->y != 4) {
                hero->movingUp();
            }
            else if (chunks[hero->x][hero->y - 1].textureNum != 2 && chunks[hero->x][hero->y - 1].textureNum != 3 && chunks[hero->x][hero->y - 1].textureNum != 4 && villain[0].attack == false && villain[1].attack == false && villain[2].attack == false && hero->y == 4) {
                chunks = chunksReload(chunks, chestLines, slot->dataToSave.ammountOfSteps, chestOpened, villainLines, villain, slot);
                for (int i = 0; i < 3; i++) {
                    if (villain[i].visible == true) {
                        villain[i].movingDown();
                    }
                }
                slot->dataToSave.ammountOfSteps++;
            }
            else if (chunks[hero->x][hero->y - 1].textureNum == 4 && chestOpened == false) {
                food->chestCheck(hero->heroPosition.x, hero->heroPosition.y);
                hero->gettingDressed(armory->chestCheck(hero->heroPosition.x, hero->heroPosition.y));
                hero->useWeapon(weapons->chestCheck(hero->heroPosition.x, hero->heroPosition.y));
                chestOpened = true;
            }
            if (villain[0].attack == true || villain[1].attack == true || villain[2].attack == true) {
                for (int i = 0; i < 3; i++) {
                    if (villain[i].attack == true) {
                        GameOver = hero->gettingDammage(villain[i].ammountOfDamagePoints);
                    }
                }
            }
        }
        if (IsKeyPressed(KEY_S)) {
            if (chunks[hero->x][hero->y + 1].textureNum != 2 && chunks[hero->x][hero->y + 1].textureNum != 3 && chunks[hero->x][hero->y + 1].textureNum != 4 && villain[0].attack == false && villain[1].attack == false && villain[2].attack == false && hero->y != 8) {
                hero->movingDown();
            }
            else if (chunks[hero->x][hero->y + 1].textureNum == 4 && chestOpened == false) {
                food->chestCheck(hero->heroPosition.x, hero->heroPosition.y);
                hero->gettingDressed(armory->chestCheck(hero->heroPosition.x, hero->heroPosition.y));
                hero->useWeapon(weapons->chestCheck(hero->heroPosition.x, hero->heroPosition.y));
                chestOpened = true;
            }
            if (villain[0].attack == true || villain[1].attack == true || villain[2].attack == true) {
                for (int i = 0; i < 3; i++) {
                    if (villain[i].attack == true) {
                        GameOver = hero->gettingDammage(villain[i].ammountOfDamagePoints);
                    }
                }
            }
        }
        if (IsKeyPressed(KEY_D)) {
            if (chunks[hero->x + 1][hero->y].textureNum != 2 && chunks[hero->x + 1][hero->y].textureNum != 3 && chunks[hero->x + 1][hero->y].textureNum != 4 && villain[0].attack == false && villain[1].attack == false && villain[2].attack == false) {
                hero->movingRight();
            }
            else if (chunks[hero->x + 1][hero->y].textureNum == 4 && chestOpened == false) {
                food->chestCheck(hero->heroPosition.x, hero->heroPosition.y);
                hero->gettingDressed(armory->chestCheck(hero->heroPosition.x, hero->heroPosition.y));
                hero->useWeapon(weapons->chestCheck(hero->heroPosition.x, hero->heroPosition.y));
                chestOpened = true;
            }
            if (villain[0].attack == true || villain[1].attack == true || villain[2].attack == true) {
                for (int i = 0; i < 3; i++) {
                    if (villain[i].attack == true) {
                        GameOver = hero->gettingDammage(villain[i].ammountOfDamagePoints);

                    }
                }
            }
        }
        if (IsKeyPressed(KEY_A)) {
            if (chunks[hero->x - 1][hero->y].textureNum != 2 && chunks[hero->x - 1][hero->y].textureNum != 3 && chunks[hero->x - 1][hero->y].textureNum != 4 && villain[0].attack == false && villain[1].attack == false && villain[2].attack == false) {
                hero->movingLeft();
            }
            else if (chunks[hero->x - 1][hero->y].textureNum == 4 && chestOpened == false) {
                food->chestCheck(hero->heroPosition.x, hero->heroPosition.y);
                hero->gettingDressed(armory->chestCheck(hero->heroPosition.x, hero->heroPosition.y));
                hero->useWeapon(weapons->chestCheck(hero->heroPosition.x, hero->heroPosition.y));
                chestOpened = true;
            }
            if (villain[0].attack == true || villain[1].attack == true || villain[2].attack == true) {
                for (int i = 0; i < 3; i++) {
                    if (villain[i].attack == true) {
                        GameOver = hero->gettingDammage(villain[i].ammountOfDamagePoints);

                    }
                }
            }
        }
        if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_LEFT)) {
            if(villain[0].attack == true || villain[1].attack == true || villain[2].attack == true){
                for (int i = 0; i < 3; i++) {
                    if (villain[i].attack == true) {
                        villain[i].gettingDamage(hero->ammountOfDamagePoints);
                        GameOver = hero->gettingDammage(villain[i].ammountOfDamagePoints);
                    }
                }
            }
        }
        if (IsKeyPressed(KEY_E)) {
             hero->eatSomething(food->takeFood());

        }
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            Vector2 mousePostion = GetMousePosition();
            if (CheckCollisionPointRec(mousePostion, savingButtonRect)) {
                saveingEverything(slot, food, weapons, armory);
            }
        }
        EndDrawing();
    }


    UnloadTexture(backgroundImage);
    UnloadTexture(gameOver);
    UnloadTexture(heart);

    return true;
}

bool CreatingGame(int WindowWidth, SavingSlot * slot) {
    //PREPAIRING OBJECTS
    //1.Creating background:
    Texture2D loadAndSaveMenuBackgroundImage = LoadTexture("./GameImages/LoadCreate/LoadCreateGameMenu01.png");
    float bckgndImageScale = (float)WindowWidth / loadAndSaveMenuBackgroundImage.width;
    Vector2 bckgndLasmImagePos = { 0, 0 };
    Texture2D fakeButton2Image = LoadTexture("./GameImages/CreatingMenu/fakeButton1.png");
    Vector2 fakeButton2Pos = { 820,  70 };
    //2.Creating display:
    Texture2D loadAndSaveMenuDisplayImage = LoadTexture("./GameImages/LoadCreate/LoadAndCreateDisplay01.png");
    Vector2 lasmDisplayPos = { 237,  32 };
    //3.Creating play button:
    button playButton("./GameImages/CreatingMenu/PlayButton.png", 820, 225, 0.8f);
    //4.Creating characters:
    Texture2D charactersImage = LoadTexture("./GameImages/CreatingMenu/Characters.png");
    Vector2 charactersPos = { 270, 75 };
    //5.Creating ticks
    TickButton knightTick("./GameImages/CreatingMenu/TickOff.png", 325, 450, 0.8f);
    TickButton elfTick("./GameImages/CreatingMenu/TickOff.png", 520, 450, 0.8f);
    TickButton dworfTick("./GameImages/CreatingMenu/TickOff.png", 715, 450, 0.8f);
    //6.Load error texture of display
    Texture2D errorTexture = LoadTexture("./GameImages/LoadCreate/LoadAndCreateDisplay02.png");

    int error = 0;
    while (!WindowShouldClose()) {
        BeginDrawing();
        //SHOWING ALL MAIN MENU ELEMENTS
        ClearBackground(RAYWHITE);
        DrawTextureEx(loadAndSaveMenuBackgroundImage, bckgndLasmImagePos, 0.0f, bckgndImageScale, WHITE);
        if (error > 0) {
            DrawTextureEx(errorTexture, lasmDisplayPos, 0.0f, 0.8f, WHITE);
            error--;
        }
        else {
            DrawTextureEx(loadAndSaveMenuDisplayImage, lasmDisplayPos, 0.0f, 0.8f, WHITE);
        }
        DrawTextureEx(fakeButton2Image, fakeButton2Pos, 0.0f, 0.8f, WHITE);
        DrawTextureEx(charactersImage, charactersPos, 0.0f, 0.8f, WHITE);
        playButton.show();
        knightTick.show();
        elfTick.show();
        dworfTick.show();
        

        //CREATING RECTANGLES FOR BUTTONS
        Rectangle playButtonRect = playButton.rectangleButton();
        Rectangle knightTickRect = knightTick.rectangleButton();
        Rectangle elfTickRect = elfTick.rectangleButton();
        Rectangle dworfTickRect = dworfTick.rectangleButton();

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            Vector2 mousePosition = GetMousePosition();
            if (CheckCollisionPointRec(mousePosition, knightTickRect)) {
                knightTick.changeTickStatus(1);
                elfTick.changeTickStatus(0);
                dworfTick.changeTickStatus(0);
            }
            else if (CheckCollisionPointRec(mousePosition, elfTickRect)) {
                elfTick.changeTickStatus(1);
                knightTick.changeTickStatus(0);
                dworfTick.changeTickStatus(0);
            }
            else if (CheckCollisionPointRec(mousePosition, dworfTickRect)) {
                dworfTick.changeTickStatus(1);
                knightTick.changeTickStatus(0);
                elfTick.changeTickStatus(0);
            }
            else if (CheckCollisionPointRec(mousePosition, playButtonRect)) {
                if (knightTick.tickButtonStatus == 1) {
                    slot->prepairingSavingFile(1);
                    UnloadTexture(loadAndSaveMenuBackgroundImage);
                    UnloadTexture(loadAndSaveMenuDisplayImage);
                    UnloadTexture(fakeButton2Image);
                    UnloadTexture(charactersImage);
                    UnloadTexture(errorTexture);
                    EndDrawing();
                    return MAIN_GAME_PROCESS(WindowWidth, slot);
                }
                else if (elfTick.tickButtonStatus == 1) {
                    slot->prepairingSavingFile(2);
                    UnloadTexture(loadAndSaveMenuBackgroundImage);
                    UnloadTexture(loadAndSaveMenuDisplayImage);
                    UnloadTexture(fakeButton2Image);
                    UnloadTexture(charactersImage);
                    UnloadTexture(errorTexture);
                    EndDrawing();
                    return MAIN_GAME_PROCESS(WindowWidth, slot);
                }
                else if (dworfTick.tickButtonStatus == 1) {
                    slot->prepairingSavingFile(3);
                    UnloadTexture(loadAndSaveMenuBackgroundImage);
                    UnloadTexture(loadAndSaveMenuDisplayImage);
                    UnloadTexture(fakeButton2Image);
                    UnloadTexture(charactersImage);
                    UnloadTexture(errorTexture);
                    EndDrawing();
                    return MAIN_GAME_PROCESS(WindowWidth, slot);
                }
                else {
                    error = 100;
                }
            }
            
        }
        EndDrawing();
    }
    return true;
}


bool LoadAndCreateGameMenu(int WindowWidth) {
    bool exitStatus;
    //PREPAIRING ELEMENTS
    //1.Creating background:
    Texture2D loadAndSaveMenuBackgroundImage = LoadTexture("./GameImages/LoadCreate/LoadCreateGameMenu01.png");
    float bckgndImageScale = (float)WindowWidth / loadAndSaveMenuBackgroundImage.width;
    Vector2 bckgndLasmImagePos = { 0, 0 };
    //2.Creating display:
    Texture2D loadAndSaveMenuDisplayImage = LoadTexture("./GameImages/LoadCreate/LoadAndCreateDisplay01.png");
    Vector2 lasmDisplayPos = { 237,  32 };
    //3.Creating load button:
    button creatingGameButton("./GameImages/LoadCreate/CreatingGameButton.png", 820, 70, 0.8f);
    //4.Creating exit button:
    button exitToMainMenuButton("./GameImages/LoadCreate/ExitToMainMenu.png", 820, 225, 0.8f);
    //5.Creating saving slots
    SavingSlot slot1("./GameImages/LoadCreate/SavingSlot.png", 263, 65, 0.8f, "./GameFiles/SavingSlot1.txt", 1);
    SavingSlot slot2("./GameImages/LoadCreate/SavingSlot.png", 263, 161, 0.8f, "./GameFiles/SavingSlot2.txt", 2);
    SavingSlot slot3("./GameImages/LoadCreate/SavingSlot.png", 263, 257, 0.8f, "./GameFiles/SavingSlot3.txt", 3);
    SavingSlot slot4("./GameImages/LoadCreate/SavingSlot.png", 263, 353, 0.8f, "./GameFiles/SavingSlot4.txt", 4);
    SavingSlot slot5("./GameImages/LoadCreate/SavingSlot.png", 263, 449, 0.8f, "./GameFiles/SavingSlot5.txt", 5);
    //6.Load error texture of display
    Texture2D errorTexture = LoadTexture("./GameImages/LoadCreate/LoadAndCreateDisplay03.png");
    
    
    int error = 0;
    while (!WindowShouldClose()) {
        BeginDrawing();
        //SHOWING ALL MAIN MENU ELEMENTS
        ClearBackground(RAYWHITE);
        DrawTextureEx(loadAndSaveMenuBackgroundImage, bckgndLasmImagePos, 0.0f, bckgndImageScale, WHITE);
        if (error > 0) {
            DrawTextureEx(errorTexture, lasmDisplayPos, 0.0f, 0.8f, WHITE);
            error--;
        }
        else {
            DrawTextureEx(loadAndSaveMenuDisplayImage, lasmDisplayPos, 0.0f, 0.8f, WHITE);
        }
        creatingGameButton.show();
        exitToMainMenuButton.show();
        slot1.show();
        slot2.show();
        slot3.show();
        slot4.show();
        slot5.show();

        //CREATING RECTANGLES FOR BUTTONS
        Rectangle creatingGameRect = creatingGameButton.rectangleButton();
        Rectangle exitToMainMenuRect = exitToMainMenuButton.rectangleButton();
        Rectangle firstSlotRect = slot1.rectangleSavingSlot();
        Rectangle secondSlotRect = slot2.rectangleSavingSlot();
        Rectangle thirdSlotRect = slot3.rectangleSavingSlot();
        Rectangle fourthSlotRect = slot4.rectangleSavingSlot();
        Rectangle fifthSlotRect = slot5.rectangleSavingSlot();
        if(IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)){}
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            Vector2 mousePosition = GetMousePosition();
            if (CheckCollisionPointRec(mousePosition, exitToMainMenuRect)) {
                UnloadTexture(loadAndSaveMenuBackgroundImage);
                UnloadTexture(loadAndSaveMenuDisplayImage);
                return false;
            }
            else if (CheckCollisionPointRec(mousePosition, creatingGameRect)) {
                if (slot1.slotStatus == 0) {
                    exitStatus = CreatingGame(WindowWidth, &slot1);
                    return exitStatus;
                }
                else if (slot2.slotStatus == 0) {
                    exitStatus = CreatingGame(WindowWidth, &slot2);
                    return exitStatus;
                }
                else if (slot3.slotStatus == 0) {
                    exitStatus = CreatingGame(WindowWidth, &slot3);
                    return exitStatus;
                }
                else if (slot4.slotStatus == 0) {
                    exitStatus = CreatingGame(WindowWidth, &slot4);
                    return exitStatus;
                }
                else if (slot5.slotStatus == 0) {
                    exitStatus = CreatingGame(WindowWidth, &slot5);
                    return exitStatus;
                }
                else {
                    error = 100;
                }
            }

            if (CheckCollisionPointRec(mousePosition, firstSlotRect) && slot1.slotStatus != 0) {
                return exitStatus = MAIN_GAME_PROCESS(WindowWidth, &slot1, 1);
            }
            else if (CheckCollisionPointRec(mousePosition, secondSlotRect) && slot2.slotStatus != 0) {
                return exitStatus = MAIN_GAME_PROCESS(WindowWidth, &slot2, 1);
            }
            else if (CheckCollisionPointRec(mousePosition, thirdSlotRect) && slot3.slotStatus != 0) {
                return exitStatus = MAIN_GAME_PROCESS(WindowWidth, &slot3, 1);
            }
            else if (CheckCollisionPointRec(mousePosition, fourthSlotRect) && slot4.slotStatus != 0) {
                return exitStatus = MAIN_GAME_PROCESS(WindowWidth, &slot4, 1);
            }
            else if (CheckCollisionPointRec(mousePosition, fifthSlotRect) && slot5.slotStatus != 0) {
                return exitStatus = MAIN_GAME_PROCESS(WindowWidth, &slot5, 1);
            }
        }

        EndDrawing();
    }

    //UNLOADING TEXTURES
    UnloadTexture(loadAndSaveMenuBackgroundImage);
    UnloadTexture(loadAndSaveMenuDisplayImage);

    return true;
}


int main() {
    bool exitStatusCheck;

    const int WindowWidth = 1280;
    const int WindowHeight = 640;

    InitWindow(WindowWidth, WindowHeight, "OneBitAdventure");

    SetTargetFPS(60);


    //PREPAIRING ELEMENTS
    //1.Creating background:
    Texture2D backgroundImage = LoadTexture("./GameImages/MainMenu/MainMenuBkgnd.png");
    float bckgndImageScale = (float)WindowWidth / backgroundImage.width;
    Vector2 bckgndImagePos = { 0, 0 };
    //2.Creating main title:
    Texture2D mainTitleImage = LoadTexture("./GameImages/MainMenu/Title.png");
    //3.Creating start button:
    button startGameButton("./GameImages/MainMenu/StartGameButton.png", 512, 300, 0.2f);
    //5.Creating exit button:
    button exitButton("./GameImages/MainMenu/ExitButton.png", 512, 370, 0.2f);


    //MAIN CYCLE
    while (!WindowShouldClose()) {
        BeginDrawing();

        //SHOWING ELEMENTS
        ClearBackground(RAYWHITE);
        DrawTextureEx(backgroundImage, bckgndImagePos, 0.0f, bckgndImageScale, WHITE);
        DrawTextureEx(mainTitleImage, {200, 50}, 0.0f, 1.0, WHITE);
        startGameButton.show();
        exitButton.show();


        //CREATING RECTANGLES
        Rectangle startGameRect = startGameButton.rectangleButton();
        Rectangle exitRect = exitButton.rectangleButton();
        

        //CHECKING MAIN EVENTS
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            Vector2 mousePosition = GetMousePosition();
            if (CheckCollisionPointRec(mousePosition, exitRect)) {
                break;
            }
            else if (CheckCollisionPointRec(mousePosition, startGameRect)) {
                exitStatusCheck = LoadAndCreateGameMenu(WindowWidth);
                if (exitStatusCheck == true) {
                    break;
                }
            }
        }

        EndDrawing();
        
    }
    //UNLOADING TEXTURES
    UnloadTexture(backgroundImage);
    UnloadTexture(mainTitleImage);
    return 0;
}