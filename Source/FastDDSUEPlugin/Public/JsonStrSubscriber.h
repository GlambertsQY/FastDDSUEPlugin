// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#pragma warning(disable : 4668)
#pragma warning(disable : 4582)
#pragma warning(disable : 4265)

#include <fastdds/dds/domain/DomainParticipant.hpp>
#include <fastdds/dds/subscriber/DataReader.hpp>
#include <fastdds/dds/subscriber/DataReaderListener.hpp>
#include <fastdds/dds/subscriber/Subscriber.hpp>

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "JsonStrSubscriber.generated.h"

/**
 * 
 */
UCLASS()
class FASTDDSUEPLUGIN_API UJsonStrSubscriber : public UObject
{
	GENERATED_BODY()
public:
	bool init();
	UJsonStrSubscriber();
	virtual ~UJsonStrSubscriber() override;
	
	std::string* Message = nullptr;

	void setParams(FString PName, FString TName);

private:

	eprosima::fastdds::dds::DomainParticipant* participant_;
	eprosima::fastdds::dds::Subscriber* subscriber_;
	eprosima::fastdds::dds::Topic* topic_;
	eprosima::fastdds::dds::DataReader* reader_;
	eprosima::fastdds::dds::TypeSupport type_;

	// 放在init()中作为局部变量，则当init()执行完毕时，会导致heap corruption异常
	eprosima::fastdds::dds::DataReaderQos rqos;
	eprosima::fastdds::dds::DomainParticipantQos pqos;

	UPROPERTY()
	FString TopicName;

	UPROPERTY()
	FString ParticipantName;
	
	class SubListener : public eprosima::fastdds::dds::DataReaderListener
	{
	public:

		SubListener() = default;

		~SubListener() override = default;

		void on_data_available(
				eprosima::fastdds::dds::DataReader* reader) override;

		void on_subscription_matched(
				eprosima::fastdds::dds::DataReader* reader,
				const eprosima::fastdds::dds::SubscriptionMatchedStatus& info) override;

		int matched = 0;
		uint32_t samples = 0;
		std::string getStr;
	}
	listener_;
};
