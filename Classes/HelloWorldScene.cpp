#include "HelloWorldScene.h"
#include "CardSprite.h"
//#include "PauseScene.h"
#include "GameOverScene.h"



USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init() {
    //////////////////////////////
    // 1. super init first
    if (!Layer::init()) {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
//    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto touchListener = EventListenerTouchOneByOne::create();
	auto keyboardListener = EventListenerKeyboard::create();


	keyboardListener->onKeyReleased = CC_CALLBACK_2(HelloWorld::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);

    touchListener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this); 
    touchListener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener,this);

	
    //Join the game's background color
    auto layerColorBG = cocos2d::LayerColor::create(cocos2d::Color4B(180,170,160,255));
    this->addChild(layerColorBG);

    

    //Join the game score at the top

    //Adding "scores" label
    auto labelTTFCardNumberName = LabelTTF::create("SCORE","Helvetica",60); // HiraKakuProN-W6
    labelTTFCardNumberName->setPosition(Point(visibleSize.width / 3, visibleSize.height - 40));
    addChild(labelTTFCardNumberName);

	createCardSprite(visibleSize, labelTTFCardNumberName); // необходимо написать норм код а не говны // исправлено вроде

	//Create Zhang automatically generated card
	autoCreateCardNumber();
	autoCreateCardNumber();

    //Join specific scores
    labelTTFCardNumber = LabelTTF::create("0","Helvetica",60);
	labelTTFCardNumber->setPosition(Point(labelTTFCardNumberName->getPosition().x + labelTTFCardNumberName->getFontSize() * (labelTTFCardNumberName->getString().length() % 2 + labelTTFCardNumberName->getString().length() / 2 + 1), visibleSize.height - 40));
    addChild(labelTTFCardNumber);
	_director = Director::getInstance();
	_visibleSize = _director->getVisibleSize();
	auto origin = _director->getVisibleOrigin();
	auto closeItem = MenuItemImage::create(
		"quit.png",
		"quit.png",
		CC_CALLBACK_1(HelloWorld::Close, this));

	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
		origin.y + closeItem->getContentSize().height / 2));

	auto menu = Menu::create(closeItem, nullptr);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	auto againItem = MenuItemImage::create(
		"again.png",
		"again.png",
		CC_CALLBACK_1(HelloWorld::Again, this));

	againItem->setPosition(Vec2(origin.x + visibleSize.width - againItem->getContentSize().width / 2,
		origin.y + visibleSize.height - againItem->getContentSize().height / 2));

	auto menu2 = Menu::create(againItem, nullptr);
	menu2->setPosition(Vec2::ZERO);
	this->addChild(menu2, 1);

    return true;

}

// это уже конечная версия, норм функция
//Event listener callbacks: Touch Start
bool HelloWorld::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event) {
    Vec2 touchPoint = touch->getLocation(); //Get OpenGL coordinates (ie cocos2d-x coordinate origin in the lower left corner)
    touch->getLocationInView(); 
    first_x = (int) touchPoint.x;
    first_y = (int) touchPoint.y;
    return true;
}

// это уже конечная версия, норм функция
//Event listener callback: Touch End
void HelloWorld::onTouchEnded(Touch *touch, Event *unused_event) {
    Vec2 touchPoint = touch->getLocation();
    delta_x = first_x - touchPoint.x;
    delta_y = first_y - touchPoint.y;

    if (abs(delta_x) > abs(delta_y)) 
	{
		if (delta_x + 20 > 0)
		{
			if (!doLeft())
				return;
        }
        else
        {
            doRight();
        }
    } 
	else 
	{
		if (delta_y + 20 > 0)
		{
            doDown();
        }    
		else 
		{
            doUp();
        }
    }

	if(doCheckGameOver())
		autoCreateCardNumber();

}


bool HelloWorld::doUp() {
    log("doUp");
    bool isdo = false;
    for (int x = 0; x < 4; x++) {
        for (int y = 3; y >= 0; y--) {

            for (int y1 = y - 1; y1 >= 0; y1--) {
                if (cards[x][y1]->getNumber() > 0) {
                    if (cards[x][y]->getNumber() <= 0) {
                        cards[x][y]->setNumber(cards[x][y1]->getNumber());
                        cards[x][y1]->setNumber(0);

                        y++;
                        isdo = true;
                    }else if(cards[x][y]->getNumber() == cards[x][y1]->getNumber()){
                        cards[x][y]->setNumber(cards[x][y]->getNumber()*2);
                        cards[x][y1]->setNumber(0);

                        //Изменить оценки
                        score += cards[x][y]->getNumber();
                        labelTTFCardNumber->setString(String::createWithFormat("%i",score)->getCString());
                        isdo = true;
                    }
                    break;
                }
            }

        }
    }
    return isdo;
}

bool HelloWorld::doDown() {
    log("doDown");
    bool isdo = false;
    for (int x = 0; x < 4; x++) {
        for (int y = 0; y < 4; y++) {

            for (int y1 = y + 1; y1 < 4; y1++) {
                if (cards[x][y1]->getNumber() > 0) {
                    if (cards[x][y]->getNumber() <= 0) {
                        cards[x][y]->setNumber(cards[x][y1]->getNumber());
                        cards[x][y1]->setNumber(0);

                        y--;
                        isdo = true;
                    }else if(cards[x][y]->getNumber() == cards[x][y1]->getNumber()){
                        cards[x][y]->setNumber(cards[x][y]->getNumber()*2);
                        cards[x][y1]->setNumber(0);

                        //Изменить оценки
                        score += cards[x][y]->getNumber();
                        labelTTFCardNumber->setString(String::createWithFormat("%i",score)->getCString());
                        isdo = true;
                    }
                    break;
                }
            }

        }
    }
    return isdo;
}

bool HelloWorld::doLeft() {
    log("doLeft");

    bool isDo = false;
    for (int y = 0; y < SIZE_FIELD_Y; y++) {
        for (int x = 0; x < SIZE_FIELD_X; x++) {
            // If the number equal to the number on the left to the right, then to the left of the number multiplied by 2, 
			//and then the number on the right is set to 0, it becomes empty.
            for (int x1 = x + 1; x1 < 4; x1++) {
                if (cards[x1][y]->getNumber() > 0) {
                    if (cards[x][y]->getNumber() <= 0) {
                        cards[x][y]->setNumber(cards[x1][y]->getNumber());
                        cards[x1][y]->setNumber(0);

                        x--;
                        isDo = true;
                    }else if(cards[x][y]->getNumber() == cards[x1][y]->getNumber()){
                        cards[x][y]->setNumber(cards[x][y]->getNumber()*2);
                        cards[x1][y]->setNumber(0);

                        //Change marks
                        score += cards[x][y]->getNumber();
                        labelTTFCardNumber->setString(String::createWithFormat("%i",score)->getCString());
                        isDo = true;
                    }
                    break;
                }
            }
        }
    }
    return isDo;
}

bool HelloWorld::doRight() {
    log("doRight");
    bool isdo = false;
    for (int y = 0; y < 4; y++) {
        for (int x = 3; x >= 0; x--) {

            for (int x1 = x - 1; x1 >= 0; x1--) {
                if (cards[x1][y]->getNumber() > 0) {
                    if (cards[x][y]->getNumber() <= 0) {
                        cards[x][y]->setNumber(cards[x1][y]->getNumber());
                        cards[x1][y]->setNumber(0);

                        x++;
                        isdo = true;
                    }else if(cards[x][y]->getNumber() == cards[x1][y]->getNumber()){
                        cards[x][y]->setNumber(cards[x][y]->getNumber()*2);
                        cards[x1][y]->setNumber(0);

                        //change marks
                        score += cards[x][y]->getNumber();
                        labelTTFCardNumber->setString(String::createWithFormat("%i",score)->getCString());
                        isdo = true;
                    }
                    break;
                }
            }

        }
    }
    return isdo;
}

//Creating card
void HelloWorld::createCardSprite(cocos2d::Size size, cocos2d::LabelTTF *labelTTFCardNumberName)
{
	//const CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    //Obtaining cell width and height
	int unitSize;
	if (size.height < size.width)
		unitSize = (size.height - size.height / (SIZE_FIELD_Y + 1)) / SIZE_FIELD_Y;
	else unitSize = (size.width - size.width / (SIZE_FIELD_X + 1)) / SIZE_FIELD_X;

    //4*4Cell
    for(int i = 0; i < SIZE_FIELD_X; i++)
    {
        for(int j = 0; j < SIZE_FIELD_Y; j++)
        {
			CardSprite *card = CardSprite::createCardSprite(0, unitSize, unitSize, unitSize*i + labelTTFCardNumberName->getPosition().x
				- labelTTFCardNumberName->getFontSize() * (labelTTFCardNumberName->getString().length() % 2 + labelTTFCardNumberName->getString().length() / 2),
				unitSize*j + 20);
            cards[i][j] = card;
            addChild(card);
        }
    }
}

//
void HelloWorld::autoCreateCardNumber()
{
	//Быдлоалгоритм, раньше вообще ... была
	//Находим все свободные клетки, выбираем рандом из них.
	std::vector<std::pair<int, int>> vacant_places;
	for (int i = 0; i < SIZE_FIELD_X; ++i)
		for (int j = 0; j < SIZE_FIELD_Y; ++j)
			if (!cards[i][j]->getNumber())
				vacant_places.push_back(std::make_pair(i, j));

	if (vacant_places.size() == 0)
		return;
	int index_random_place = CCRANDOM_0_1()*(vacant_places.size() - 1);
	auto pair = vacant_places[index_random_place]; //чтобы меньше писать

    cards[pair.first][pair.second]->setNumber(CCRANDOM_0_1()*10 < 1 ? 2: 4);
    log("(%d,%d): %d", pair.first, pair.second, cards[pair.first][pair.second]->getNumber());

}

//Determine whether the game can continue
bool HelloWorld::doCheckGameOver(){
	bool gameContinue = false;

    for (int y = 0; y < SIZE_FIELD_X; y++) {
        for (int x = 0; x < SIZE_FIELD_Y; x++) {
			//if (cards[x][y]->getNumber() == 0 || )
			if (cards[x][y]->getNumber() == 0 ||
				(x>0 && (cards[x][y]->getNumber() == cards[x - 1][y]->getNumber())) ||
				(x<3 && (cards[x][y]->getNumber() == cards[x + 1][y]->getNumber())) ||
				(y>0 && (cards[x][y]->getNumber() == cards[x][y - 1]->getNumber())) ||
				(y<3 && (cards[x][y]->getNumber() == cards[x][y + 1]->getNumber()))) {
				gameContinue = true;
				break;
			}
        }
    }
	UserDefault::getInstance()->setIntegerForKey("score", score);

	if (!gameContinue) {

		auto label = Label::createWithTTF("YOU DIED", "fonts/Marker Felt.ttf", 96);
		label->setColor(cocos2d::Color3B::RED);
		auto visibleSize = _director->getVisibleSize();
		label->setPosition(visibleSize.width / 2, visibleSize.height / 2);
		this->addChild(label, 1);
		//Эта строчка убирает все слушатели событий (тач, нажатия на клаву)
		//после нее игра не реагирует на касания
		_eventDispatcher->removeEventListenersForTarget(this);
		//Создаем слушатель события - нажата любая кнопка
		auto keyboardListener = EventListenerKeyboard::create();
		auto touchListener = EventListenerTouchOneByOne::create();

		/////////////////
		touchListener->onTouchBegan = [this](Touch *touch, Event *unused_event){
		Director::getInstance()->replaceScene(TransitionFade::create(1, HelloWorld::createScene()));
		return true;
		};
		_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
		/////////////////


		keyboardListener->onKeyReleased = [this](EventKeyboard::KeyCode keyCode, Event* event){
			
			Director::getInstance()->replaceScene(TransitionFade::create(1, GameOver::createScene()));

		};
		_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);
		//_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
		

        log("you die");
    } else {
		return true;
		//autoCreateCardNumber();
    }
}





void HelloWorld::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event){
	bool didMove = true;
	switch (keyCode){
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
	case EventKeyboard::KeyCode::KEY_A:
		didMove = doLeft();
		break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
	case EventKeyboard::KeyCode::KEY_D:
		didMove = doRight();
		break;
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
	case EventKeyboard::KeyCode::KEY_W:
		didMove = doUp();
		break;
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
	case EventKeyboard::KeyCode::KEY_S:
		didMove = doDown();
		break;
	}

	if (didMove) 
		autoCreateCardNumber();

	doCheckGameOver();
};

void HelloWorld::Close(Ref* pSender)
{
	Director::getInstance()->end();
}

void HelloWorld::Again(Ref* pSender)
{
	Director::getInstance()->replaceScene(TransitionFade::create(1, HelloWorld::createScene()));
}
