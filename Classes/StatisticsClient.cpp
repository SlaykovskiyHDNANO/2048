#include "StatisticsClient.h"

ConnectionStatus StatisticsClient::GetStatus()
{
	return this->status_;
}


const std::string StatisticsClient::ServerAddress = "192.168.1.54:8080";
