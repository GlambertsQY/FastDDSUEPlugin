// Fill out your copyright notice in the Description page of Project Settings.


#include "JsonStrPublisher.h"
#include "JsonStrPubSubTypes.h"

#include <fastdds/dds/domain/DomainParticipantFactory.hpp>
#include <fastdds/dds/publisher/Publisher.hpp>
#include <fastdds/dds/publisher/qos/PublisherQos.hpp>
#include <fastdds/dds/publisher/DataWriter.hpp>
#include <fastdds/dds/publisher/qos/DataWriterQos.hpp>

using namespace eprosima::fastdds::dds;

UJsonStrPublisher::UJsonStrPublisher()
	: participant_(nullptr)
	  , publisher_(nullptr)
	  , topic_(nullptr)
	  , writer_(nullptr)
	  , type_(new JsonStrBeanPubSubType())
{
	ParticipantName = TEXT("Participant_Pub");
	TopicName = TEXT("myTopic");
}

UJsonStrPublisher::~UJsonStrPublisher()
{
	if (writer_ != nullptr)
	{
		publisher_->delete_datawriter(writer_);
	}
	if (publisher_ != nullptr)
	{
		participant_->delete_publisher(publisher_);
	}
	if (topic_ != nullptr)
	{
		participant_->delete_topic(topic_);
	}
	DomainParticipantFactory::get_instance()->delete_participant(participant_);
}

bool UJsonStrPublisher::init()
{
	/* Initialize data_ here */

	//CREATE THE PARTICIPANT
	DomainParticipantQos pqos;
	pqos.name({TCHAR_TO_UTF8(*ParticipantName)});
	participant_ = DomainParticipantFactory::get_instance()->create_participant(0, pqos);
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

	// CREATE THE WRITER
	writer_ = publisher_->create_datawriter(topic_, DATAWRITER_QOS_DEFAULT, &listener_);
	if (writer_ == nullptr)
	{
		return false;
	}
	
	return true;
}

void UJsonStrPublisher::setParams(FString PName, FString TName)
{
	ParticipantName = PName;
	TopicName = TName;
}

void UJsonStrPublisher::SendMessage(FString Message)
{
	if (listener_.matched != 0)
	{
		JsonStrBean sendStr;
		sendStr.LRJsonString({TCHAR_TO_UTF8(*Message)});
		writer_->write(&sendStr);
	}
}

void UJsonStrPublisher::PubListener::on_publication_matched(eprosima::fastdds::dds::DataWriter* writer,
                                                            const eprosima::fastdds::dds::PublicationMatchedStatus&
                                                            info)
{
	if (info.current_count_change == 1)
	{
		matched = info.total_count;
		std::cout << "DataWriter matched." << std::endl;
	}
	else if (info.current_count_change == -1)
	{
		matched = info.total_count;
		std::cout << "DataWriter unmatched." << std::endl;
	}
	else
	{
		std::cout << info.current_count_change
			<< " is not a valid value for PublicationMatchedStatus current count change" << std::endl;
	}
}
