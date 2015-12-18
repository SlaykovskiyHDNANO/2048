#include "GameOverScene.h"
#include "HelloWorldScene.h"


USING_NS_CC;

Scene* GameOver::createScene()
{
    auto scene = Scene::create();
    auto layer = GameOver::create();
    scene->addChild(layer);
    return scene;
}

bool GameOver::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
	director = Director::getInstance();  
    visibleSize = director->getVisibleSize();
	Vec2 origin = director->getVisibleOrigin();
    auto pauseItem = MenuItemImage::create(
                                           "play.png",
                                           "play_pressed.png",
                                           CC_CALLBACK_1(GameOver::exitPause, this));
	pauseItem->setPosition(Vec2(origin.x + visibleSize.width - pauseItem->getContentSize().width / 2,
							origin.y + pauseItem->getContentSize().height / 2));
	auto menu = Menu::create(pauseItem, nullptr);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
	auto layerColorBG = cocos2d::LayerColor::create(cocos2d::Color4B(180,170,160,255));
	this->addChild(layerColorBG);
	auto label = Label::createWithTTF("Game Over", "fonts/Marker Felt.ttf", 96);
	//label->enableOutline(Color4B(255, 0, 0, 100),6);
	label->enableGlow(Color4B(255, 0, 0, 255));
	label->enableShadow();
    label->setPosition(origin.x + visibleSize.width/2, origin.y + visibleSize.height - visibleSize.height / 8);
	this->addChild(label, 1);
	auto label2 = Label::createWithSystemFont("Your score is", "Arial", 48);
    label2->setPosition(origin.x + visibleSize.width/2, label->getPosition().y - label->getLineHeight() / 1.5);
	this->addChild(label2, 1);
	char scoreText[32];
	int score = UserDefault::getInstance()->getIntegerForKey("score",0);
	sprintf(scoreText, "%d", score);
	auto label3 = Label::createWithSystemFont(scoreText, "Arial", 48);
	label3->setPosition(origin.x + visibleSize.width / 2, label2->getPosition().y - label->getLineHeight() / 1.5);
	this->addChild(label3, 1);
	auto label4 = Label::createWithSystemFont("Enter your name", "Arial", 48);
	label4->setPosition(origin.x + visibleSize.width / 2, label3->getPosition().y - label->getLineHeight() / 1.5);
	this->addChild(label4, 1);

	createTF(origin.x + visibleSize.width / 2, label4->getPosition().y - label->getLineHeight() / 1.5);

    return true;
}

void GameOver::exitPause(cocos2d::Ref* pSender){
	Director::getInstance()->replaceScene(TransitionFlipX::create(1.0, HelloWorld::createScene()));
}


CCScene* GameOver::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	HelloWorld *layer = HelloWorld::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
/*bool GameOver::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	this->setTouchEnabled(true);

	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	createTF();

	CCLabelTTF* pLabel = CCLabelTTF::create("Hello World", "Arial", 24);

	// position the label on the center of the screen
	pLabel->setPosition(ccp(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - pLabel->getContentSize().height));

	this->addChild(pLabel, 1);

	return true;
}*/

void GameOver::createTF(size_t x, size_t y)
{
	tf = CCTextFieldTTF::textFieldWithPlaceHolder("Your name", CCSizeMake(100, 100), kCCTextAlignmentCenter, "helvetica", 20);
	tf->setColorSpaceHolder(Color3B(0xDD, 0xDD, 0xDD));
	tf->setPosition(ccp(x,y));
	tf->setHorizontalAlignment(kCCTextAlignmentCenter);
	tf->setVerticalAlignment(kCCVerticalTextAlignmentCenter);
	tf->setDelegate(this);
	addChild(tf);
}



bool GameOver::onTouchBegan(Touch *pTouch, Event *pEvent)
{
	log("inside touchbegan");

	return true;
}

void GameOver::onTouchEnded(Touch *pTouch, Event *pEvent)
{
	log("inside touchend");

	tf->attachWithIME();

}


bool GameOver::onTextFieldAttachWithIME(TextFieldTTF * pSender)
{

	return false;

}

bool GameOver::onTextFieldDetachWithIME(TextFieldTTF * pSender)
{
	return false;
}

bool GameOver::onTextFieldInsertText(TextFieldTTF * pSender, const char * text, size_t nLen)
{
	return false;
}

bool GameOver::onTextFieldDeleteBackward(TextFieldTTF * pSender, const char * delText, size_t nLen)
{
	return false;
} 