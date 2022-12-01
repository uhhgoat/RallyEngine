#include "ObjectUpdateMessage.h"


ObjectUpdateMessage::ObjectUpdateMessage()
{
    type = DataMessage::DataMessage_Type::UPDATE;
}

ObjectUpdateMessage::ObjectUpdateMessage(int _objectTypeID, int _objectID, Matrix _transform)
//    : base(DataMessage_Type.PLAYER_INPUT, _sendType)
{
    type = DataMessage::DataMessage_Type::UPDATE;
    ObjectTypeID = _objectTypeID;
    ObjectID = _objectID;
    Transform = _transform;
}
/*
ObjectUpdateMessage::ObjectUpdateMessage(SEND_TYPE _sendType, int _objectTypeID, int _objectID, Matrix _transform)
{
    type = DataMessage::DataMessage_Type::UPDATE;
    sendType = _sendType;
    ObjectTypeID = _objectTypeID;
    ObjectID = _objectID;
    Transform = _transform;
}
*/
std::string ObjectUpdateMessage::Serialize()
{
    //writer.Write(this.playerID);
    //writer.Write(this.key);

    std::string typestr = std::to_string(static_cast<int>(type)) + ";";
    std::string objTypeIDstr = std::to_string(ObjectTypeID) + ";";
    std::string objIDstr = std::to_string(ObjectID) + ";";
    std::string transformstr = std::to_string(Transform.M0()) + ";"
        + std::to_string(Transform.M1()) + ";"
        + std::to_string(Transform.M2()) + ";"
        + std::to_string(Transform.M3()) + ";"
        + std::to_string(Transform.M4()) + ";"
        + std::to_string(Transform.M5()) + ";"
        + std::to_string(Transform.M6()) + ";"
        + std::to_string(Transform.M7()) + ";"
        + std::to_string(Transform.M8()) + ";"
        + std::to_string(Transform.M9()) + ";"
        + std::to_string(Transform.M10()) + ";"
        + std::to_string(Transform.M11()) + ";"
        + std::to_string(Transform.M12()) + ";"
        + std::to_string(Transform.M13()) + ";"
        + std::to_string(Transform.M14()) + ";"
        + std::to_string(Transform.M15()) + ";";

    std::string packet = typestr + objTypeIDstr + objIDstr + transformstr;


    return packet;
}

ObjectUpdateMessage* ObjectUpdateMessage::Deserialize(std::string packet)
{
    ObjectUpdateMessage* output = new ObjectUpdateMessage();

    output->type = static_cast<DataMessage::DataMessage_Type>(std::stoi(packet));
    std::size_t pos = packet.find(";") + 1;
    packet = packet.substr(pos);
    output->ObjectTypeID = (std::stoi(packet));
    pos = packet.find(";") + 1;
    packet = packet.substr(pos);
    output->ObjectID = (std::stoi(packet));
    pos = packet.find(";") + 1;
    packet = packet.substr(pos);
#pragma region  TransformMatrix
    float M0 = (std::stof(packet));
    pos = packet.find(";") + 1;
    packet = packet.substr(pos);
    float M1 = (std::stof(packet));
    pos = packet.find(";") + 1;
    packet = packet.substr(pos);
    float M2 = (std::stof(packet));
    pos = packet.find(";") + 1;
    packet = packet.substr(pos);
    float M3 = (std::stof(packet));
    pos = packet.find(";") + 1;
    packet = packet.substr(pos);
    float M4 = (std::stof(packet));
    pos = packet.find(";") + 1;
    packet = packet.substr(pos);
    float M5 = (std::stof(packet));
    pos = packet.find(";") + 1;
    packet = packet.substr(pos);
    float M6 = (std::stof(packet));
    pos = packet.find(";") + 1;
    packet = packet.substr(pos);
    float M7 = (std::stof(packet));
    pos = packet.find(";") + 1;
    packet = packet.substr(pos);
    float M8 = (std::stof(packet));
    pos = packet.find(";") + 1;
    packet = packet.substr(pos);
    float M9 = (std::stof(packet));
    pos = packet.find(";") + 1;
    packet = packet.substr(pos);
    float M10 = (std::stof(packet));
    pos = packet.find(";") + 1;
    packet = packet.substr(pos);
    float M11 = (std::stof(packet));
    pos = packet.find(";") + 1;
    packet = packet.substr(pos);
    float M12 = (std::stof(packet));
    pos = packet.find(";") + 1;
    packet = packet.substr(pos);
    float M13 = (std::stof(packet));
    pos = packet.find(";") + 1;
    packet = packet.substr(pos);
    float M14 = (std::stof(packet));
    pos = packet.find(";") + 1;
    packet = packet.substr(pos);
    float M15 = (std::stof(packet));
#pragma endregion

    output->Transform.set(Vect(M0, M1, M2, M3), Vect(M4, M5, M6, M7), Vect(M8, M9, M10, M11), Vect(M12, M13, M14, M15));

    return output;
}
