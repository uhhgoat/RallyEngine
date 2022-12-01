#include "DataMessage.h"
#include "AzulCore.h"
#include "EventType.h"
class PlayerInputMessage : public DataMessage
{
public:
    friend class PlayerInputMessageFactory;

    int playerID;
    EVENT_TYPE eventType;
    AZUL_KEY key;

    virtual std::string Serialize() override;

    static PlayerInputMessage* Deserialize(std::string packet);

    PlayerInputMessage();

    PlayerInputMessage(int _playerID, EVENT_TYPE _eventType, AZUL_KEY _key);

    //PlayerInputMessage(SEND_TYPE _sendType, int _playerID, EVENT_TYPE _eventType, AZUL_KEY _key);


};