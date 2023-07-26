// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#pragma warning(disable : 4668)
#pragma warning(disable : 4582)
#pragma warning(disable : 4265)

#include <fastdds/dds/domain/DomainParticipant.hpp>
#include <fastdds/dds/publisher/DataWriter.hpp>
#include <fastdds/dds/publisher/DataWriterListener.hpp>
#include <fastdds/dds/publisher/Publisher.hpp>
#include <fastdds/dds/topic/TypeSupport.hpp>

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "JsonStrPublisher.generated.h"

/**
 * 
 */
UCLASS()
class FASTDDSUEPLUGIN_API UJsonStrPublisher : public UObject
{
	GENERATED_BODY()

public:
	UJsonStrPublisher();
	virtual ~UJsonStrPublisher() override;
	bool init();
	void setParams(FString PName, FString TName);
	void SendMessage(FString Message);
	

public:
	eprosima::fastdds::dds::DomainParticipant* participant_;
	eprosima::fastdds::dds::Publisher* publisher_;
	eprosima::fastdds::dds::Topic* topic_;
	eprosima::fastdds::dds::DataWriter* writer_;
	eprosima::fastdds::dds::TypeSupport type_;

	UPROPERTY()
	FString TopicName;

	UPROPERTY()
	FString ParticipantName;
	
	class PubListener : public eprosima::fastdds::dds::DataWriterListener
	{
	public:
		PubListener() = default;

		~PubListener() override = default;

		virtual void on_publication_matched(
			eprosima::fastdds::dds::DataWriter* writer,
			const eprosima::fastdds::dds::PublicationMatchedStatus& info) override;

		int matched = 0;
	} listener_;
};
