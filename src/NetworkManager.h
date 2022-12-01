#pragma once
#include <assert.h>

#include "AzulCore.h"

#include "WinSockWrapper.h"
#include "Ws2tcpip.h"
#include <stdio.h>
#include <thread>
#include <future>

#pragma comment(lib, "Ws2_32.lib")

#include <stdio.h>
#include <list>
#include "PlayerInputMessage.h"
#include "GameStateMessage.h"
#include "ObjectUpdateMessage.h"
#include "CollisionMessage.h"
#include "NetworkMessage.h"
#include "ConnectionCancelMessage.h"

#define DEFAULT_PORT "27015"
#define DEFAULT_BUFLEN 512

class NetworkManager
{
public:
	enum class NetworkState
	{
		OFFLINE,
		HOST,
		PENDING_HOST,
		CLIENT
	};
	enum class PROTOCOL
	{
		TCP = 0,
		UDP
	};
	/*!
	\brief Called to host a network connection
	*/
	static void EstablishHost();

	/*!
	\brief Called to join a hosted network connection
	*/
	static void EstablishClient();

	/*!
	\brief Called to send a DataMessage through the network
	*/
	static void SendData(DataMessage* message);

	/*!
	\brief Called to get the current network state
	*/
	static NetworkState getState() { return Instance().state; }

	/*!
	\brief Called to cancel a hosted or pending host connection
	*/
	static void CancelHost();

	/*!
	\brief Called to cancel a client's connection to a host
	*/
	static void CancelClient();

	/*!
	\brief Called to set the protocol used for sending and receving messages
	*/
	static void SetProtocol(NetworkManager::PROTOCOL _protocol);

private:
	friend class Rally;
	friend class Serializer;

	NetworkManager::PROTOCOL protocol;

	std::list<DataMessage*> OutQueue;
	std::list<DataMessage*> InQueue;

	std::list<NetworkMessage*> NetMessCollection;

	static NetworkManager* ptrInstance;

	NetworkManager();
	NetworkManager(const NetworkManager&) = delete;
	NetworkManager& operator=(const NetworkManager&) = delete;
	~NetworkManager();


	static NetworkManager& Instance()
	{
		if (!ptrInstance)
			ptrInstance = new NetworkManager;
		return *ptrInstance;
	};

	NetworkState state;

	std::thread hostOpen;
	std::thread clientConnect;
	std::thread receiveThread;
	//std::promise<void> exitSignal;

	bool REC_SHUTDOWN = false;

	int iResult = 0;
	int iSendResult = 0;
	char recvbuf[DEFAULT_BUFLEN];
	int recvbuflen = DEFAULT_BUFLEN;

	sockaddr_in ClientUDPAddr;
	sockaddr_in ServerUDPAddr;

	SOCKET ClientSocket = INVALID_SOCKET;

	

	
	static void Delete();

	void HostConnection();
	void ConnectToHost();

	void HostConnectionUDP();
	void ConnectToHostUDP();

	void Receive();
	static void Send(DataMessage* _data);

	void ReceiveUDP();
	static void SendUDP(DataMessage* _data);

	void CloseConnectThread();
	void ShutdownConnections();

	void StopAccept();
	void StopAcceptUDP();

	void ClearStoredMessages();

	static void ProcessInputQueue();

	static void ProcessOutputQueue();

	static void ProcessInputMessage(PlayerInputMessage* inputMessage);
	static void ProcessGameStateMessage(GameStateMessage* stateMessage);
	static void ProcessUpdateMessage(ObjectUpdateMessage* updateMessage);
	static void ProcessCollisionMessage(CollisionMessage* colMessage);

};
