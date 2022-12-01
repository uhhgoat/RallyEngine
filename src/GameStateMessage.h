#include "DataMessage.h"
#include "AzulCore.h"
#include "EventType.h"
class GameStateMessage : public DataMessage
{
public:
    friend class GameStateMessageFactory;

    int GameState;

    virtual std::string Serialize() override;

    static GameStateMessage* Deserialize(std::string packet);

    GameStateMessage();

    GameStateMessage(int _gameState);

    //GameStateMessage(SEND_TYPE _sendType, int _gameState);


};