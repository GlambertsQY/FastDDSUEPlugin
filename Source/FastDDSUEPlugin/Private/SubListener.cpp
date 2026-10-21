#include "SubListener.h"

#include "fastdds/dds/subscriber/SampleInfo.hpp"
#include <fastdds/dds/subscriber/DataReader.hpp>

#include "FastDDSUEPlugin.h"

using namespace eprosima::fastdds::dds;

void SubListener::on_subscription_matched(eprosima::fastdds::dds::DataReader* reader,
	const eprosima::fastdds::dds::SubscriptionMatchedStatus& info)
{
	if (info.current_count_change == 1)
	{
		matched = info.total_count;
		UE_LOG(LogFastDDS, Log, TEXT("Subscriber matched."));
	}
	else if (info.current_count_change == -1)
	{
		matched = info.total_count;
		UE_LOG(LogFastDDS, Log, TEXT("Subscriber unmatched."));
	}
	else
	{
		UE_LOG(LogFastDDS, Warning,
			TEXT("%d is not a valid value for SubscriptionMatchedStatus current count change"),
			info.current_count_change);
	}
}
