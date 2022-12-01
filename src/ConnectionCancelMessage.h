#include "DataMessage.h"
#include "AzulCore.h"
#include "EventType.h"
class ConnectionCancelMessage : public DataMessage
{
public:
    friend class ConnectionCancelMessageFactory;


    virtual std::string Serialize() override;

    static ConnectionCancelMessage* Deserialize(std::string packet);

    ConnectionCancelMessage();


    void Initialize();


};