#pragma once
#include "JsonStr.h"
#include "fastdds/dds/subscriber/DataReaderListener.hpp"

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "SubListener.generated.h"

UCLASS()
class FASTDDSUEPLUGIN_API USubListener : public UObject, public eprosima::fastdds::dds::DataReaderListener
{
	GENERATED_BODY()

public:
	USubListener() = default;

	~USubListener() override = default;

	void on_data_available(
		eprosima::fastdds::dds::DataReader* reader) override;

	void on_subscription_matched(
		eprosima::fastdds::dds::DataReader* reader,
		const eprosima::fastdds::dds::SubscriptionMatchedStatus& info) override;

	// 不能是局部变量，会引发free异常
	JsonStrBean st;
	int matched = 0;
	uint32_t samples = 0;
	std::string getStr;
};
