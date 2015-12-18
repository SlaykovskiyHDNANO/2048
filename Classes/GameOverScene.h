#ifndef __GameOver_SCENE_H__
#define __GameOver_SCENE_H__
#pragma once
#include "cocos2d.h"


class GameOver : public cocos2d::Layer, public cocos2d::TextFieldDelegate
{
public:
	virtual bool onTextFieldAttachWithIME(cocos2d::TextFieldTTF * pSender) override;
	bool onTextFieldDetachWithIME(cocos2d::TextFieldTTF * pSender) override;
	
	bool onTextFieldInsertText(cocos2d::TextFieldTTF * pSender, const char * text, size_t nLen) override;
	bool onTextFieldDeleteBackward(cocos2d::TextFieldTTF * pSender, const char * delText, size_t nLen) override;


	static cocos2d::CCScene* scene();

	void createTF(size_t x, size_t y);
	cocos2d::CCTextFieldTTF* tf;

	
	virtual bool onTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent) override;
	virtual void onTouchEnded(cocos2d::Touch *pTouch, cocos2d::Event *pEvent) override;

	//CCtextFieldttf delegate begin
	
	//CCtextFieldttf delegate end


    static cocos2d::Scene* createScene();
    virtual bool init();    
	void exitPause(cocos2d::Ref* pSender);
    CREATE_FUNC(GameOver);
private:
	cocos2d::Sprite* sprLogo;
	cocos2d::Director *director;
	cocos2d::Size visibleSize;	
};

#endif // __Pause_SCENE_H__
