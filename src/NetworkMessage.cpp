#include "NetworkMessage.h"
#include "PlayerInputMessage.h"
#include "GameStateMessage.h"
#include "ObjectUpdateMessage.h"
#include "CollisionMessage.h"
#include "ConnectionCancelMessage.h"

NetworkMessage::~NetworkMessage()
{
    delete data;
}

void NetworkMessage::Set_Data(DataMessage* _data)
{
    data = _data;
    data_type = data->type;
}

DataMessage* NetworkMessage::GetData()
{
    return data;
}

std::string NetworkMessage::Serialize()
{
    //writer.Write((int)data_type);
    //std::string typestr = std::to_string(static_cast<int>(data_type)) + ";";

    //data.Serialize(ref writer);
    std::string datastr = data->Serialize();

    return datastr;
}

NetworkMessage* NetworkMessage::Deserialize(std::string bytes)
{
    //BinaryReader reader = new BinaryReader(new MemoryStream(bytes));
    NetworkMessage* output = new NetworkMessage();

    output->data_type = static_cast<DataMessage::DataMessage_Type>(std::stoi(bytes));

    //COULD MAYBE CHANGE THIS TO JUST RETURN THE DATA
    switch (output->data_type)
    {
    case DataMessage::DataMessage_Type::PLAYER_INPUT:
        output->data = PlayerInputMessage::Deserialize(bytes);
        break;
    case DataMessage::DataMessage_Type::UPDATE:
        output->data = ObjectUpdateMessage::Deserialize(bytes);
        break;
    case DataMessage::DataMessage_Type::COLLISION:
        output->data = CollisionMessage::Deserialize(bytes);
        break;
    case DataMessage::DataMessage_Type::GAME_STATE:
        output->data = GameStateMessage::Deserialize(bytes);
        break;
    case DataMessage::DataMessage_Type::CANCEL:
        output->data = ConnectionCancelMessage::Deserialize(bytes);
        break;
    default:
        assert(!"INVALID DATA TYPE");
        break;
    }

    return output;
}