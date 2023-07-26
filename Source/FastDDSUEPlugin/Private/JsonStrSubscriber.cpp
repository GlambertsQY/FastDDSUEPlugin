// Fill out your copyright notice in the Description page of Project Settings.


#include "JsonStrSubscriber.h"
#include "JsonStrPubSubTypes.h"

#include <fastdds/dds/domain/DomainParticipantFactory.hpp>
#include <fastdds/dds/subscriber/DataReader.hpp>
#include <fastdds/dds/subscriber/SampleInfo.hpp>
#include <fastdds/dds/subscriber/Subscriber.hpp>

using namespace eprosima::fastdds::dds;

bool UJsonStrSubscriber::init()
{
	//CREATE THE PARTICIPANT

	pqos.name({TCHAR_TO_UTF8(*ParticipantName)});
	participant_ = DomainParticipantFactory::get_instance()->create_participant(0, pqos);
	if (participant_ == nullptr)
	{
		return false;
	}

	//REGISTER THE TYPE
	type_.register_type(participant_);

	//CREATE THE SUBSCRIBER
	subscriber_ = participant_->create_subscriber(SUBSCRIBER_QOS_DEFAULT, nullptr);
	if (subscriber_ == nullptr)
	{
		return false;
	}

	//CREATE THE TOPIC
	topic_ = participant_->create_topic(
		{TCHAR_TO_UTF8(*TopicName)},
		type_.get_type_name(),
		TOPIC_QOS_DEFAULT);
	if (topic_ == nullptr)
	{
		return false;
	}

	//CREATE THE READER
	rqos = DATAREADER_QOS_DEFAULT;
	rqos.reliability().kind = RELIABLE_RELIABILITY_QOS;
	reader_ = subscriber_->create_datareader(topic_, rqos, &listener_);
	if (reader_ == nullptr)
	{
		return false;
	}

	return true;
}

UJsonStrSubscriber::UJsonStrSubscriber()
	: participant_(nullptr)
	  , subscriber_(nullptr)
	  , topic_(nullptr)
	  , reader_(nullptr)
	  , type_(new JsonStrBeanPubSubType())
{
	Message = &listener_.getStr;
	ParticipantName = TEXT("Participant_Pub");
	TopicName = TEXT("myTopic");
}

UJsonStrSubscriber::~UJsonStrSubscriber()
{
	if (reader_ != nullptr)
	{
		subscriber_->delete_datareader(reader_);
	}
	if (topic_ != nullptr)
	{
		participant_->delete_topic(topic_);
	}
	if (subscriber_ != nullptr)
	{
		participant_->delete_subscriber(subscriber_);
	}
	DomainParticipantFactory::get_instance()->delete_participant(participant_);
}

void UJsonStrSubscriber::setParams(FString PName, FString TName)
{
	ParticipantName = PName;
	TopicName = TName;
}

void UJsonStrSubscriber::SubListener::on_data_available(eprosima::fastdds::dds::DataReader* reader)
{
	// Take data
	JsonStrBean st;
	SampleInfo info;

	if (reader->take_next_sample(&st, &info) == ReturnCode_t::RETCODE_OK)
	{
		if (info.valid_data)
		{
			// Print your structure data here.
			// ++samples;
			// std::cout << "Sample received, count=" << samples << std::endl;
			getStr = st.LRJsonString();
			// GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, s);
		}
	}
}

void UJsonStrSubscriber::SubListener::on_subscription_matched(eprosima::fastdds::dds::DataReader* reader,
                                                            const eprosima::fastdds::dds::SubscriptionMatchedStatus&
                                                            info)
{
	if (info.current_count_change == 1)
	{
		matched = info.total_count;
		std::cout << "Subscriber matched." << std::endl;
	}
	else if (info.current_count_change == -1)
	{
		matched = info.total_count;
		std::cout << "Subscriber unmatched." << std::endl;
	}
	else
	{
		std::cout << info.current_count_change
			<< " is not a valid value for SubscriptionMatchedStatus current count change" << std::endl;
	}
}
