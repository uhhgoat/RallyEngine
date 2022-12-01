#include "GameStateMessage.h"


GameStateMessage::GameStateMessage()
{
    type = DataMessage::DataMessage_Type::GAME_STATE;
}

GameStateMessage::GameStateMessage(int _gameState)
//    : base(DataMessage_Type.PLAYER_INPUT, _sendType)
{
    type = DataMessage::DataMessage_Type::GAME_STATE;
    GameState = _gameState;
}
/*
GameStateMessage::GameStateMessage(SEND_TYPE _sendType, int _gameState)
{
    type = DataMessage::DataMessage_Type::GAME_STATE;
    sendType = _sendType;
    GameState = _gameState;
}
*/
std::string GameStateMessage::Serialize()
{
    //writer.Write(this.playerID);
    //writer.Write(this.key);

    std::string typestr = std::to_string(static_cast<int>(type)) + ";";
    std::string gamestatestr = std::to_string(GameState) + ";";

    std::string packet = typestr + gamestatestr;


    return packet;
}

GameStateMessage* GameStateMessage::Deserialize(std::string packet)
{
    GameStateMessage* output = new GameStateMessage();

    output->type = static_cast<DataMessage::DataMessage_Type>(std::stoi(packet));
    std::size_t pos = packet.find(";") + 1;
    packet = packet.substr(pos);
    output->GameState = (std::stoi(packet));


    return output;
}
