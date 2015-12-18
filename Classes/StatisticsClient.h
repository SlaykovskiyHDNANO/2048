#pragma once
#include "network/SocketIO.h"
#include <thread>
#include <string>
#include "json/rapidjson.h"
#include "json/document.h"
#include "threading/MessageQueue.hpp"

enum ConnectionStatus {
	CS_CONNECTED,
	CS_IN_PROGRESS,
	CS_FAILED

};


class StatisticsStruct {
	int64_t userid;
	std::string usernick;
	size_t score;



};

class StatisticsClient {
public:
	
	std::thread thr;
	cocos2d::network::SIOClient client;
	
	static const std::string ServerAddress;


	ConnectionStatus GetStatus();

private:
	ConnectionStatus status_;
	//threading::ThreadMessageQueue queue_;

	void _Utils_Connect() {

	}

};