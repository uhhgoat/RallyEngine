#pragma once
#include "DataMessage.h"
class NetworkMessage
{
public:
    DataMessage::DataMessage_Type data_type;
    DataMessage* data;

    NetworkMessage() = default;
    ~NetworkMessage();

    void Set_Data(DataMessage* _data);

    DataMessage* GetData();

    std::string Serialize();

    static NetworkMessage* Deserialize(std::string bytes);

};