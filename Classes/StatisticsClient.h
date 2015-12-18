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
	CS_FAILED,
	CS_NOT_CONNECTED,

	CS_RECEIVING_TOP_RESPONSE,
	CS_RECEIVING_SET_RESULT_RESPONSE

};

struct StatisticsMessage {
	struct StatisticsMessageData{
		std::mutex lock;
		void* data;
		bool done;
		bool succes;
	};

	std::shared_ptr<StatisticsMessageData> Data = { std::shared_ptr<StatisticsMessageData>(new StatisticsMessageData()) };
};


struct StatisticsStruct {
	int64_t userid;
	std::string usernick;
	size_t score;



};



class StatisticsClient:protected cocos2d::network::SocketIO::SIODelegate {
public:
	
	
	static const std::string ServerAddress;

	ConnectionStatus GetStatus();

	//Получает список игроков с макисмальным счетом.
	std::vector<StatisticsStruct> GetTop(size_t max_count);

	//Получает топ асинхронно.
	StatisticsMessage GetTopAsync(size_t max_count);

	bool SendStatistics(const StatisticsStruct& stat);

	StatisticsMessage SendStatisticsAsync(const StatisticsStruct& stat);


	StatisticsClient& Current();
	

protected:

	void onConnect(cocos2d::network::SIOClient* cli) override {

	}

	void onMessage(cocos2d::network::SIOClient* cli, const std::string& data) override {


	}


	void onClose(cocos2d::network::SIOClient* cli) override {

	}

	void onError(cocos2d::network::SIOClient* cli, const std::string& data) override {
		cocos2d::log(("[ERROR] StatisticsClient::"+data).c_str());
		status_ = ConnectionStatus::CS_FAILED;


	}

private:
	
	


	StatisticsClient* instance_ = { nullptr };

	std::thread thr;
	std::shared_ptr<cocos2d::network::SIOClient> client;
	cocos2d::network::SocketIO::SIODelegate* delegate_;
	ConnectionStatus status_ = { ConnectionStatus::CS_NOT_CONNECTED };
	threading::ThreadMessageQueue<StatisticsMessage> queue_;

	void _Utils_Connect() {
		client = std::shared_ptr<cocos2d::network::SIOClient>(cocos2d::network::SocketIO::connect( ServerAddress , *delegate_ ));
	}


	StatisticsClient() {

	}
};