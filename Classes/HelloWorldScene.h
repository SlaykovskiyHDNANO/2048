#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__
#pragma once
#include "cocos2d.h"
#include "CardSprite.h"


static const int SIZE_FIELD_X = 4;
static const int SIZE_FIELD_Y = 4;

enum SceneStatus {
	SS_WAITING_YOU_DIED_CHANGE,
	SS_PLAYING,


};



class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

	//управление с клавиатуры
	virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode code, cocos2d::Event *unused_event) override;



    virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event) override;

    virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event) override;

    bool doUp();
    bool doDown();
    bool doLeft();
    bool doRight();

	bool doCheckGameOver();

    void autoCreateCardNumber();
    void createCardSprite(cocos2d::Size size, cocos2d::LabelTTF *labelTTFCardNumberName);
    

    //Game scores
	int score = { 0 };

    //Defines the display control scores счетчик
    cocos2d::LabelTTF* labelTTFCardNumber;

	//void pauseCallback(cocos2d::Ref* pSender);
	void Close(Ref* pSender);
	void Again(Ref* pSender);

private:
	int first_x,
		first_y,
		delta_x,
		delta_y;
		
	SceneStatus status_;

    CardSprite *cards[4][4];

	cocos2d::Director *_director;
	cocos2d::Size _visibleSize;
};

#endif // __HELLOWORLD_SCENE_H__
