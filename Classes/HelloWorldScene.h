#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "CardSprite.h"

#define SIZE_FIELD_X  4
#define SIZE_FIELD_Y  4



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

    void autoCreateCardNumber();
    void createCardSprite(cocos2d::Size size, cocos2d::LabelTTF *labelTTFCardNumberName);
    void doCheckGameOver();

    //Game scores
	int score = { 0 };

    //Defines the display control scores счетчик
    cocos2d::LabelTTF* labelTTFCardNumber;

private:
	int first_x,
		first_y,
		delta_x,
		delta_y;
		
    CardSprite *cards[4][4];
};

#endif // __HELLOWORLD_SCENE_H__
