// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#pragma warning(push)
#pragma warning(disable : 4668)
#pragma warning(disable : 4582)
#pragma warning(disable : 4265)
#pragma warning(disable : 4530)

#include "CoreMinimal.h"

#include <atomic>

#include <fastdds/dds/domain/DomainParticipant.hpp>
#include <fastdds/dds/publisher/DataWriter.hpp>
#include <fastdds/dds/publisher/DataWriterListener.hpp>
#include <fastdds/dds/publisher/Publisher.hpp>
#include <fastdds/dds/topic/TypeSupport.hpp>

#include "JsonStr.h"

/**
 * Fast DDS publisher for the JsonStrBean topic type.
 * Call setParams() before init(). Not thread-safe; use from the game thread.
 */
class FASTDDSUEPLUGIN_API JsonStrPublisher
{

public:
	JsonStrPublisher();
	virtual ~JsonStrPublisher();
	bool init();
	void setParams(int32 DId, FString PName, FString TName);
	void SendMessage(const FString& Message);

	bool IsMatched() const;
	int32 GetMatchedCount() const;

private:
	// Destroys all created DDS entities. Safe to call multiple times.
	void Reset();

	eprosima::fastdds::dds::DomainParticipant* participant_;
	eprosima::fastdds::dds::Publisher* publisher_;
	eprosima::fastdds::dds::Topic* topic_;
	eprosima::fastdds::dds::DataWriter* writer_;
	eprosima::fastdds::dds::TypeSupport type_;

	// Reused sample to avoid per-call construction in SendMessage().
	JsonStrBean SendBean;

	FString TopicName;
	FString ParticipantName;
	int32 DomainId = 0;

	class PubListener : public eprosima::fastdds::dds::DataWriterListener
	{
	public:
		PubListener() = default;

		~PubListener() override = default;

		virtual void on_publication_matched(
			eprosima::fastdds::dds::DataWriter* writer,
			const eprosima::fastdds::dds::PublicationMatchedStatus& info) override;

		// Written on the DDS listener thread, read on the game thread.
		std::atomic<int> matched{0};
	} listener_;
};

#pragma warning(pop)
