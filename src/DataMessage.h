#pragma once

class DataMessage
{
public:
    enum class DataMessage_Type
    {
        GAME_STATE = 0,
        UPDATE,
        PLAYER_INPUT,
        COLLISION,
        PLAYER_ID,
        FIRE,
        CANCEL
    };
    /*
    enum class SEND_TYPE
    {
        LOCAL = 0,
        NETWORKED
    };
    */


    DataMessage_Type type;
    //SEND_TYPE sendType;

    DataMessage();
    virtual ~DataMessage() = default;

    //DataMessage(DataMessage_Type t, SEND_TYPE _sendType);
    DataMessage(DataMessage_Type t);
    virtual std::string Serialize() = 0;

};