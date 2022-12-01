#include "PlayerInputMessage.h"


PlayerInputMessage::PlayerInputMessage()
{
    type = DataMessage::DataMessage_Type::PLAYER_INPUT;
}

PlayerInputMessage::PlayerInputMessage(int _playerID, EVENT_TYPE _eventType, AZUL_KEY _key)
//    : base(DataMessage_Type.PLAYER_INPUT, _sendType)
{
    type = DataMessage::DataMessage_Type::PLAYER_INPUT;
    playerID = _playerID;
    eventType = _eventType;
    key = _key;
}
/*
PlayerInputMessage::PlayerInputMessage(SEND_TYPE _sendType, int _playerID, EVENT_TYPE _eventType, AZUL_KEY _key)
{
    type = DataMessage::DataMessage_Type::PLAYER_INPUT;
    sendType = _sendType;
    playerID = _playerID;
    eventType = _eventType;
    key = _key;
}
*/
std::string PlayerInputMessage::Serialize()
{
    //writer.Write(this.playerID);
    //writer.Write(this.key);

    std::string typestr = std::to_string(static_cast<int>(type)) + ";";
    std::string IDstr = std::to_string(static_cast<int>(playerID)) + ";";
    std::string eventtypestr = std::to_string(static_cast<int>(eventType)) + ";";
    std::string keystr = std::to_string(static_cast<int>(key)) + ";";

    std::string packet = typestr + IDstr + eventtypestr + keystr;


    return packet;
}

PlayerInputMessage* PlayerInputMessage::Deserialize(std::string packet)
{
    PlayerInputMessage* output = new PlayerInputMessage();

    output->type = static_cast<DataMessage::DataMessage_Type>(std::stoi(packet));
    std::size_t pos = packet.find(";") + 1;
    packet = packet.substr(pos);
    output->playerID = static_cast<int>(std::stoi(packet));
    pos = packet.find(";") + 1;
    packet = packet.substr(pos);
    output->eventType = static_cast<EVENT_TYPE>(std::stoi(packet));
    pos = packet.find(";") + 1;
    packet = packet.substr(pos);
    output->key = static_cast<AZUL_KEY>(std::stoi(packet));

    return output;
}
