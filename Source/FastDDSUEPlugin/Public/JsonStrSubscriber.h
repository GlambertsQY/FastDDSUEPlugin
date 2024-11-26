// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#pragma warning(disable : 4668)
#pragma warning(disable : 4582)
#pragma warning(disable : 4265)
#pragma warning(disable : 4530)

#include <fastdds/dds/domain/DomainParticipant.hpp>
#include <fastdds/dds/subscriber/DataReader.hpp>
#include <fastdds/dds/subscriber/DataReaderListener.hpp>
#include <fastdds/dds/subscriber/Subscriber.hpp>
#include "JsonStrPubSubTypes.h"

#include "SubListener.h"


/**
 * 
 */

class FASTDDSUEPLUGIN_API JsonStrSubscriber
{
public:
	bool init();
	JsonStrSubscriber();
	virtual ~JsonStrSubscriber();
	
	std::string* Message = nullptr;

	void setParams(int32 DId, FString PName, FString TName, SubListener* SubListener);

private:

	eprosima::fastdds::dds::DomainParticipant* participant_;
	eprosima::fastdds::dds::Subscriber* subscriber_;
	eprosima::fastdds::dds::Topic* topic_;
	eprosima::fastdds::dds::DataReader* reader_;
	eprosima::fastdds::dds::TypeSupport type_;

	// 放在init()中作为局部变量，则当init()执行完毕时，会导致heap corruption异常
	eprosima::fastdds::dds::DataReaderQos rqos;
	eprosima::fastdds::dds::DomainParticipantQos pqos;
	
	SubListener* _listener;

	UPROPERTY()
	FString TopicName;

	UPROPERTY()
	FString ParticipantName;

	UPROPERTY()
	int32 DomainId = 0;
	
};
