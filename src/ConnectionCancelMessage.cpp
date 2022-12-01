#include "ConnectionCancelMessage.h"


ConnectionCancelMessage::ConnectionCancelMessage()
{
    type = DataMessage::DataMessage_Type::CANCEL;
}

void ConnectionCancelMessage::Initialize()
{
    type = DataMessage::DataMessage_Type::CANCEL;
}

std::string ConnectionCancelMessage::Serialize()
{
    //writer.Write(this.playerID);
    //writer.Write(this.key);

    std::string typestr = std::to_string(static_cast<int>(type)) + ";";

    std::string packet = typestr;


    return packet;
}

ConnectionCancelMessage* ConnectionCancelMessage::Deserialize(std::string packet)
{
    ConnectionCancelMessage* output = new ConnectionCancelMessage();

    output->type = static_cast<DataMessage::DataMessage_Type>(std::stoi(packet));


    return output;
}
