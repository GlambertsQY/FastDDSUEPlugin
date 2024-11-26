// Fill out your copyright notice in the Description page of Project Settings.


#include "JsonStrSubscriber.h"

#include <fastdds/dds/domain/DomainParticipantFactory.hpp>
#include <fastdds/dds/subscriber/DataReader.hpp>
#include <fastdds/dds/subscriber/SampleInfo.hpp>
#include <fastdds/dds/subscriber/Subscriber.hpp>

#include "SubListener.h"

using namespace eprosima::fastdds::dds;

bool JsonStrSubscriber::init()
{
	//CREATE THE PARTICIPANT
	pqos.name({TCHAR_TO_UTF8(*ParticipantName)});
	participant_ = DomainParticipantFactory::get_instance()->create_participant(DomainId, pqos);
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
	reader_ = subscriber_->create_datareader(topic_, rqos, _listener);
	if (reader_ == nullptr)
	{
		return false;
	}

	return true;
}

JsonStrSubscriber::JsonStrSubscriber()
	: participant_(nullptr)
	  , subscriber_(nullptr)
	  , topic_(nullptr)
	  , reader_(nullptr)
	  , type_(new JsonStrBeanPubSubType())
{
	_listener = nullptr;
	ParticipantName = TEXT("Participant_Pub");
	TopicName = TEXT("myTopic");
}

JsonStrSubscriber::~JsonStrSubscriber()
{
	if (reader_ != nullptr)
	{
		_listener->isAvailable = false;
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

void JsonStrSubscriber::setParams(int32 DId, FString PName, FString TName, SubListener* SubListener)
{
	DomainId = DId;
	ParticipantName = PName;
	TopicName = TName;
	_listener = SubListener;
}
