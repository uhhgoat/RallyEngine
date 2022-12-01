#include "CollisionMessage.h"


CollisionMessage::CollisionMessage()
{
    type = DataMessage::DataMessage_Type::COLLISION;
}

CollisionMessage::CollisionMessage(int _object1ID, int _object2ID)
//    : base(DataMessage_Type.PLAYER_INPUT, _sendType)
{
    type = DataMessage::DataMessage_Type::COLLISION;
    Object1ID = _object1ID;
    Object2ID = _object2ID;
}
/*
CollisionMessage::CollisionMessage(SEND_TYPE _sendType, int _object1ID, int _object2ID)
{
    type = DataMessage::DataMessage_Type::COLLISION;
    sendType = _sendType;
    Object1ID = _object1ID;
    Object2ID = _object2ID;
}
*/
std::string CollisionMessage::Serialize()
{

    std::string typestr = std::to_string(static_cast<int>(type)) + ";";
    std::string obj1IDstr = std::to_string(Object1ID) + ";";
    std::string obj2IDstr = std::to_string(Object2ID) + ";";

    std::string packet = typestr + obj1IDstr + obj2IDstr;


    return packet;
}

CollisionMessage* CollisionMessage::Deserialize(std::string packet)
{
    CollisionMessage* output = new CollisionMessage();

    output->type = static_cast<DataMessage::DataMessage_Type>(std::stoi(packet));
    std::size_t pos = packet.find(";") + 1;
    packet = packet.substr(pos);
    output->Object1ID = (std::stoi(packet));
    pos = packet.find(";") + 1;
    packet = packet.substr(pos);
    output->Object2ID = (std::stoi(packet));

    return output;
}
