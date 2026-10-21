// Fill out your copyright notice in the Description page of Project Settings.


#include "JsonStrPublisher.h"
#include "JsonStrPubSubTypes.h"

#include <fastdds/dds/domain/DomainParticipantFactory.hpp>
#include <fastdds/dds/publisher/Publisher.hpp>
#include <fastdds/dds/publisher/qos/PublisherQos.hpp>
#include <fastdds/dds/publisher/DataWriter.hpp>
#include <fastdds/dds/publisher/qos/DataWriterQos.hpp>

#include "FastDDSUEPlugin.h"

using namespace eprosima::fastdds::dds;

JsonStrPublisher::JsonStrPublisher()
	: participant_(nullptr)
	  , publisher_(nullptr)
	  , topic_(nullptr)
	  , writer_(nullptr)
	  , type_(new JsonStrBeanPubSubType())
{
	ParticipantName = TEXT("Participant_Pub");
	TopicName = TEXT("myTopic");
}

JsonStrPublisher::~JsonStrPublisher()
{
	Reset();
}

void JsonStrPublisher::Reset()
{
	if (participant_ != nullptr)
	{
		if (publisher_ != nullptr)
		{
			if (writer_ != nullptr)
			{
				publisher_->delete_datawriter(writer_);
				writer_ = nullptr;
			}
			participant_->delete_publisher(publisher_);
			publisher_ = nullptr;
		}
		if (topic_ != nullptr)
		{
			participant_->delete_topic(topic_);
			topic_ = nullptr;
		}
		DomainParticipantFactory::get_instance()->delete_participant(participant_);
		participant_ = nullptr;
	}
}

bool JsonStrPublisher::init()
{
	//CREATE THE PARTICIPANT
	DomainParticipantQos pqos;
	pqos.name({TCHAR_TO_UTF8(*ParticipantName)});
	participant_ = DomainParticipantFactory::get_instance()->create_participant(DomainId, pqos);
	if (participant_ == nullptr)
	{
		return false;
	}

	//REGISTER THE TYPE
	type_.register_type(participant_);

	//CREATE THE PUBLISHER
	publisher_ = participant_->create_publisher(PUBLISHER_QOS_DEFAULT, nullptr);
	if (publisher_ == nullptr)
	{
		Reset();
		return false;
	}

	//CREATE THE TOPIC
	topic_ = participant_->create_topic(
		{TCHAR_TO_UTF8(*TopicName)},
		type_.get_type_name(),
		TOPIC_QOS_DEFAULT);
	if (topic_ == nullptr)
	{
		Reset();
		return false;
	}

	// CREATE THE WRITER
	// RELIABLE to match the subscriber-side QoS; DDS default is BEST_EFFORT,
	// which would silently downgrade communication with a RELIABLE reader.
	DataWriterQos wqos = DATAWRITER_QOS_DEFAULT;
	wqos.reliability().kind = RELIABLE_RELIABILITY_QOS;
	writer_ = publisher_->create_datawriter(topic_, wqos, &listener_);
	if (writer_ == nullptr)
	{
		Reset();
		return false;
	}

	return true;
}

void JsonStrPublisher::setParams(int32 DId, FString PName, FString TName)
{
	DomainId = DId;
	ParticipantName = PName;
	TopicName = TName;
}

void JsonStrPublisher::SendMessage(const FString& Message)
{
	if (writer_ == nullptr)
	{
		UE_LOG(LogFastDDS, Warning, TEXT("SendMessage called before init(), message dropped."));
		return;
	}
	SendBean.JsonString({TCHAR_TO_UTF8(*Message)});
	writer_->write(&SendBean);
}

bool JsonStrPublisher::IsMatched() const
{
	return listener_.matched.load() > 0;
}

int32 JsonStrPublisher::GetMatchedCount() const
{
	return listener_.matched.load();
}

void JsonStrPublisher::PubListener::on_publication_matched(eprosima::fastdds::dds::DataWriter* writer,
                                                            const eprosima::fastdds::dds::PublicationMatchedStatus&
                                                            info)
{
	if (info.current_count_change == 1)
	{
		matched = info.total_count;
		UE_LOG(LogFastDDS, Log, TEXT("DataWriter matched."));
	}
	else if (info.current_count_change == -1)
	{
		matched = info.total_count;
		UE_LOG(LogFastDDS, Log, TEXT("DataWriter unmatched."));
	}
	else
	{
		UE_LOG(LogFastDDS, Warning,
			TEXT("%d is not a valid value for PublicationMatchedStatus current count change"),
			info.current_count_change);
	}
}
