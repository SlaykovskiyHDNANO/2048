#pragma once
#include <string>
#include "cocos2d.h"


namespace utils {

	class DynamicTextFieldDelegate: cocos2d::TextFieldDelegate {
	public:
		bool onTextFieldAttachWithIME(cocos2d::TextFieldTTF* sender) override;
		bool onTextFieldDetachWithIME(cocos2d::TextFieldTTF* sender) override;
		bool onTextFieldInsertText(cocos2d::TextFieldTTF* sender, const char* text, size_t nLen) override;
		bool onTextFieldDeleteBackward(cocos2d::TextFieldTTF* sender, const char* delText, size_t nLen) override;
		bool onVisit(cocos2d::TextFieldTTF* sender, cocos2d::Renderer* renderer, const cocos2d::Mat4& transform, uint32_t flags) override;
		~DynamicTextFieldDelegate() override;
	};


	cocos2d::Label* CreateLabel(
		const std::string &text,
		const cocos2d::Vec2 &position,
		cocos2d::Scene* scene,
		size_t font_size = 100,
		const cocos2d::Color3B &color = cocos2d::Color3B::BLACK,
		const std::string &font_name = "Arial"
		) {
		cocos2d::Label *label;
		label = cocos2d::Label::create(text, font_name, font_size);

		label->setPosition(position.x, position.y);
		label->setColor(color);

		if (scene)
			scene->addChild(label,1);
		return label;
	}


	cocos2d::TextFieldDelegate* CreateDelegate(

		) {

	}

	std::pair<cocos2d::Layer*,cocos2d::TextFieldTTF*> CreateTextInput(
		const std::string &placeholder,
		const cocos2d::Vec2 &position,
		cocos2d::Layer* parent,
		size_t font_size = 100,
		const cocos2d::Color3B &text_color = cocos2d::Color3B::BLACK,
		const std::string &font_name = "Arial",
		const cocos2d::Color4B &field_color = cocos2d::Color4B(0,0,0,0),
		const cocos2d::Vec2 &size = {200,200}
		) {
		auto layer = cocos2d::LayerRGBA::create();
		layer->setColor(cocos2d::Color3B(field_color));
		layer->setOpacity(field_color.a);
		auto ttf =  cocos2d::TextFieldTTF::create(placeholder, font_name, font_size, cocos2d::Size(size));
		layer->setPosition(position);
		

		if (parent)
			parent->addChild(layer);

		return std::make_pair(layer, ttf);
	}

}