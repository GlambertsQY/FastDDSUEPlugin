#include "SubListener.h"

#include "fastdds/dds/subscriber/SampleInfo.hpp"
#include <fastdds/dds/subscriber/DataReader.hpp>

using namespace eprosima::fastdds::dds;
// void SubListener::on_data_available(eprosima::fastdds::dds::DataReader* reader)
// {
	// // Take data
	// eprosima::fastdds::dds::SampleInfo info;
	//
	// if (reader->take_next_sample(&st, &info) == eprosima::fastrtps::types::ReturnCode_t::RETCODE_OK)
	// {
	// 	if (info.valid_data)
	// 	{
	// 		// Print your structure data here.
	// 		// ++samples;
	// 		// std::cout << "Sample received, count=" << samples << std::endl;
	// 		getStr = st.JsonString();
	// 		// GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, s);
	// 	}
	// }
// }

void SubListener::on_subscription_matched(eprosima::fastdds::dds::DataReader* reader,
	const eprosima::fastdds::dds::SubscriptionMatchedStatus& info)
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
