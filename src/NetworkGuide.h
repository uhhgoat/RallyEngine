/*! \page networkdemo Multiplayer Games

\section netsetup Network Setup
The Network Manager can be used to make games playable with two players on a LAN connection. \n
The Network Manager provides the ability to host a connection, join a connection, and send messages. \n
Once a connection is established, various messages can be sent across the network and processed by the engine. \n
To set up a network connection, one instance needs to host, and another needs to attempt to connect. \n
The Network Manager can be queried for the current state of the network. \n
\n
Host
\code
if (NetworkManager::getState() == NetworkManager::NetworkState::OFFLINE)
	{
		NetworkManager::EstablishHost();
	}
\endcode
\n
Client
\code
if (NetworkManager::getState() == NetworkManager::NetworkState::OFFLINE)
	{
		NetworkManager::EstablishClient();
	}
\endcode
\n
Cancel methods can be called to cancel a connection. If either cancels while connected, both will disconnect and reset to OFFLINE. \n
\code
NetworkManager::CancelHost();
NetworkManager::CancelClient();
\endcode
\n
\section netmess Creating Network Messages
There are four types of messages available for use. Collision, Game State, Object Update, and Player Input. \n
Each has a file with a process method associated with it. To use these messages, they must be initialized with the proper data, sent through \n
the Network Manager, and the process method needs to be implemented to determine what the receiver will do with the information. \n
\code
ObjectUpdateMessage* upmess = new ObjectUpdateMessage(typeID, objectID, worldTransform);
NetworkManager::SendData(upmess);
\endcode
\n
ProcessUpdateMessage.cpp
\code
void NetworkManager::ProcessUpdateMessage(ObjectUpdateMessage* updateMessage)
{
	if (updateMessage->ObjectTypeID == (int)GameManager::OBJ_TYPE::ENEMYTANK)
	{
		GameManager::GetEnemy(updateMessage->ObjectID)->world = updateMessage->Transform;
	}
}
\endcode
\n
The messages are managed and cleanup up at the appropriate time by the Network Manager. \n
\n
\section netprotocol TCP vs UDP
The Network Manager uses TCP protocol by default. TCP ensures reliable and ordered messages, but is slower than UDP. \n
UDP is faster but does not guarantee that messages are recieved in order or at all in some cases. \n
If you wish to switch protocol to UDP, call SetProtocol once before establishing any network connection. Otherwise, use of the \n
network is no different, except that the risks need to be managed. \n
\n
\code
	NetworkManager::SetProtocol(NetworkManager::PROTOCOL::UDP);
\endcode
\n
\n
\n
*/