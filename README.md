# FastDDSUEPlugin

## Description
This repository showcases a cross-platform Fast DDS plugin for Unreal Engine, 
enabling the creation of subscribers and publishers with specified TopicName, DomainID, and ParticipantName. 
Available for C++ only.

## Support Platforms
- Unreal Engine 4.27.2 - 5.4.4
- Windows(x86, arm64), android(arm64) 

## Building Environment
- Visual Studio 2022
- Windows 11 SDK 10.0.22621.0
- NDK 25.1.8937393

| Library Name     | Commit ID                                                | Source/Website                                   |
|------------------|----------------------------------------------------------|--------------------------------------------------|
| Fast DDS         | original/2.12.x 107ea8d64942102696840cd7d3e4cf93fa7a143e | [Fast DDS](https://github.com/eProsima/Fast-DDS) |
| Fast CDR         | original/master 2f655844f80b6c038e81d3a1d055265469eef00d | [Fast CDR](https://github.com/eProsima/Fast-CDR) |
| Foonathan Memory | original/master d54c7f16fa903a06974ce02ad6ef383fe2230b6f | [Foonathan Memory](https://github.com/foonathan/memory)                             |



## Usage
### Create subscriber
1. Create a new C++ class that inherits from class `SubListener`
```c++
class YOURPROJECT_API BaseSubListener : public SubListener
{
public:

	virtual void on_data_available(eprosima::fastdds::dds::DataReader* reader) override;
	
	BaseSubListener();
};
```
2. Override function `on_data_available()`
```c++
void DYAckListener::on_data_available(eprosima::fastdds::dds::DataReader* reader)
{
	// Take data
	eprosima::fastdds::dds::SampleInfo info;
	if (reader->take_next_sample(&st, &info) == eprosima::fastrtps::types::ReturnCode_t::RETCODE_OK)
	{
	    if (info.valid_data)
	    {
	        AsyncTask(ENamedThreads::GameThread, [this]()
	        {
	            FString ReceivedString = st.JsonString().c_str();
	            // Your parsing logic, run on GameThread.
	        });
	    }
	}
}
```
3. Declare an object of type `JsonStrSubscriber`.
```c++
UCLASS()
class YOURPROJECT_API AYourActor : public AActor
{
	GENERATED_BODY()

private:
	JsonStrSubscriber* YourSub;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
}
```
4. You may initialize object `YourSub` in function `BeginPlay()`
```c++
void AYourActor::BeginPlay()
{
	Super::BeginPlay();
	YourSub = new JsonStrSubscriber();
	YourSub->setParams(TEXT("DomainID"), TEXT("ParticipantName"), TEXT("TopicName"), 
	    new BaseListener());
	if (YourSub->init())
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, "YourSub initialized");
	}
}
```
5. Test your subscriber
### Create publisher
1. Declare an object of type `JsonStrSubscriber`.
```c++
UCLASS()
class YOURPROJECT_API AYourActor : public AActor
{
	GENERATED_BODY()

private:
	JsonStrPublisher* YourPub;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
}
```
2. Initialize object `YourPub` in function `BeginPlay()`
```c++
void AYourActor::BeginPlay()
{
	Super::BeginPlay();
	YourPub = new JsonStrPublisher();
	YourPub->setParams(TEXT("DomainID"), TEXT("ParticipantName"), TEXT("TopicName"));
	if (YourPub->init())
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, "YourPub initialized");
	}
}
```
3. Send your message: `YourPub->SendMessage(SendString);`
## Bugs
1. `bEnableExceptions = true;` in `FastDDSUEPlugin.Build.cs` does not seem to take effect on Unreal 5.4.4, 
only if setting `bEnableExceptions = true;` in `YourGameModule.Build.cs`
2. `PublicDefinitions.Add("__APPLE__=0");` in `FastDDSUEPlugin.Build.cs` does not seem to take effect