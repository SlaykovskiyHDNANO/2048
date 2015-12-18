#include "StatisticsClient.h"

ConnectionStatus StatisticsClient::GetStatus()
{
	return this->status_;
}

std::vector<StatisticsStruct> StatisticsClient::GetTop(size_t max_count)
{
	return std::vector<StatisticsStruct>();
}

StatisticsMessage StatisticsClient::GetTopAsync(size_t max_count)
{
	return StatisticsMessage();
}

bool StatisticsClient::SendStatistics(const StatisticsStruct & stat)
{
	return false;
}

StatisticsMessage StatisticsClient::SendStatisticsAsync(const StatisticsStruct & stat)
{
	return StatisticsMessage();
}

inline StatisticsClient & StatisticsClient::Current() {
	if (!this->instance_)
		this->instance_ = new StatisticsClient();
	return *this->instance_;
}




const std::string StatisticsClient::ServerAddress = "192.168.1.54:8080";
