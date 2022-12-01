#include "DataMessage.h"
#include "AzulCore.h"
#include "EventType.h"
class CollisionMessage : public DataMessage
{
public:
    friend class CollisionMessageFactory;

    int Object1ID;
    int Object2ID;

    virtual std::string Serialize() override;

    static CollisionMessage* Deserialize(std::string packet);

    CollisionMessage();

    CollisionMessage(int _object1ID, int _object2ID);

    //CollisionMessage(SEND_TYPE _sendType, int _object1ID, int _object2ID);


};