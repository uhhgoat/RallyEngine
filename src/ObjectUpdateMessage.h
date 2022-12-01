#include "DataMessage.h"
#include "AzulCore.h"
#include "EventType.h"
class ObjectUpdateMessage : public DataMessage
{
public:
    friend class ObjectUpdateMessageFactory;

    int ObjectTypeID;
    int ObjectID;
    Matrix Transform;

    virtual std::string Serialize() override;

    static ObjectUpdateMessage* Deserialize(std::string packet);

    ObjectUpdateMessage();

    ObjectUpdateMessage(int _objectTypeID, int _objectID, Matrix _transform);

    //ObjectUpdateMessage(SEND_TYPE _sendType, int _objectTypeID, int _objectID, Matrix _transform);


};