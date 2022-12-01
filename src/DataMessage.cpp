#include "DataMessage.h"

DataMessage::DataMessage()
{
}

DataMessage::DataMessage(DataMessage_Type t)
{
    type = t;
}
/*
DataMessage::DataMessage(DataMessage_Type t, SEND_TYPE _sendType)
{
    type = t;
    sendType = _sendType;
}
*/