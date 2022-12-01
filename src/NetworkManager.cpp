#include "NetworkManager.h"
#include "NetworkMessage.h"
#include "SceneManager.h"

NetworkManager* NetworkManager::ptrInstance = nullptr;

NetworkManager::NetworkManager()
{
    state = NetworkState::OFFLINE;
    protocol = PROTOCOL::UDP;
    *recvbuf = 0;
}

void NetworkManager::Delete()
{
    delete ptrInstance;
    ptrInstance = nullptr;
}

void NetworkManager::HostConnection()
{
    REC_SHUTDOWN = false;
    WSADATA wsaData;

    SOCKET ListenSocket = INVALID_SOCKET;
    ClientSocket = INVALID_SOCKET;

    struct addrinfo* result = NULL;
    struct addrinfo hints;



    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        DebugMsg::out("WSAStartup failed with error: %d\n", iResult);
        state = NetworkState::OFFLINE;
        return;
    }

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    // Resolve the server address and port
    iResult = getaddrinfo("127.0.0.1", DEFAULT_PORT, &hints, &result);
    if (iResult != 0) {
        DebugMsg::out("getaddrinfo failed with error: %d\n", iResult);
        WSACleanup();
        state = NetworkState::OFFLINE;
        return;
    }

    // Create a SOCKET for connecting to server
    ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (ListenSocket == INVALID_SOCKET) {
        DebugMsg::out("socket failed with error: %ld\n", WSAGetLastError());
        freeaddrinfo(result);
        WSACleanup();
        state = NetworkState::OFFLINE;
        return;
    }

    // Setup the TCP listening socket
    iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
    if (iResult == SOCKET_ERROR) {
        DebugMsg::out("bind failed with error: %d\n", WSAGetLastError());
        freeaddrinfo(result);
        closesocket(ListenSocket);
        WSACleanup();
        state = NetworkState::OFFLINE;
        return;
    }

    freeaddrinfo(result);

    iResult = listen(ListenSocket, SOMAXCONN);
    if (iResult == SOCKET_ERROR) {
        DebugMsg::out("listen failed with error: %d\n", WSAGetLastError());
        closesocket(ListenSocket);
        WSACleanup();
        state = NetworkState::OFFLINE;
        return;
    }

    // Accept a client socket
    ClientSocket = accept(ListenSocket, NULL, NULL);
    if (ClientSocket == INVALID_SOCKET) {
        DebugMsg::out("accept failed with error: %d\n", WSAGetLastError());
        closesocket(ListenSocket);
        WSACleanup();
        state = NetworkState::OFFLINE;
        return;
    }

    // No longer need server socket
    closesocket(ListenSocket);

    if (state == NetworkState::PENDING_HOST)
    {
        state = NetworkState::HOST;
        SceneManager::GetCurrentScene()->NotifyClientConnect(true);

        receiveThread = std::thread(&NetworkManager::Receive, this);
    }

}

void NetworkManager::ConnectToHost()
{
    REC_SHUTDOWN = false;
    WSADATA wsaData;
    ClientSocket = INVALID_SOCKET;
    struct addrinfo* result = NULL,
        * ptr = NULL,
        hints;



    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        DebugMsg::out("WSAStartup failed with error: %d\n", iResult);
        state = NetworkState::OFFLINE;
        return;
    }

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    // Resolve the server address and port
    iResult = getaddrinfo("127.0.0.1", DEFAULT_PORT, &hints, &result);
    if (iResult != 0) {
        DebugMsg::out("getaddrinfo failed with error: %d\n", iResult);
        WSACleanup();
        state = NetworkState::OFFLINE;
        return;
    }

    // Attempt to connect to an address until one succeeds
    for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {

        // Create a SOCKET for connecting to server
        ClientSocket = socket(ptr->ai_family, ptr->ai_socktype,
            ptr->ai_protocol);
        if (ClientSocket == INVALID_SOCKET) {
            DebugMsg::out("socket failed with error: %ld\n", WSAGetLastError());
            WSACleanup();
            state = NetworkState::OFFLINE;
            return;
        }

        // Connect to server.
        iResult = connect(ClientSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
        if (iResult == SOCKET_ERROR) {
            closesocket(ClientSocket);
            ClientSocket = INVALID_SOCKET;
            continue;
        }
        break;
    }

    freeaddrinfo(result);

    if (ClientSocket == INVALID_SOCKET) {
        DebugMsg::out("Unable to connect to server!\n");
        WSACleanup();
        state = NetworkState::OFFLINE;
        SceneManager::GetCurrentScene()->NotifyConnectToHost(false);
        return;
    }

    SceneManager::GetCurrentScene()->NotifyConnectToHost(true);

    receiveThread = std::thread(&NetworkManager::Receive, this);

}

void NetworkManager::HostConnectionUDP()
{
    REC_SHUTDOWN = false;
    WSADATA wsaData;

    //SOCKET ListenSocket = INVALID_SOCKET;
    ClientSocket = INVALID_SOCKET;

    struct addrinfo* result = NULL;
    struct addrinfo hints;



    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        DebugMsg::out("WSAStartup failed with error: %d\n", iResult);
        state = NetworkState::OFFLINE;
        return;
    }

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_protocol = IPPROTO_UDP;
    hints.ai_flags = AI_PASSIVE;

    // Resolve the server address and port
    iResult = getaddrinfo("127.0.0.1", DEFAULT_PORT, &hints, &result);
    if (iResult != 0) {
        DebugMsg::out("getaddrinfo failed with error: %d\n", iResult);
        WSACleanup();
        state = NetworkState::OFFLINE;
        return;
    }

    // Create a SOCKET for connecting to server
    ClientSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (ClientSocket == INVALID_SOCKET) {
        DebugMsg::out("socket failed with error: %ld\n", WSAGetLastError());
        freeaddrinfo(result);
        WSACleanup();
        state = NetworkState::OFFLINE;
        return;
    }

    // Setup the UDP listening socket
    iResult = bind(ClientSocket, result->ai_addr, (int)result->ai_addrlen);
    if (iResult == SOCKET_ERROR) {
        DebugMsg::out("bind failed with error: %d\n", WSAGetLastError());
        freeaddrinfo(result);
        closesocket(ClientSocket);
        WSACleanup();
        state = NetworkState::OFFLINE;
        return;
    }

    freeaddrinfo(result);

    //NEED TO LISTEN FOR CONNECTION WITH RecvFrom
    char udpbuff[100];

    sockaddr_in from;
    int size = sizeof(from);
    int ret = recvfrom(ClientSocket, udpbuff, sizeof(udpbuff), 0, reinterpret_cast<SOCKADDR*>(&from), &size);
    if (ret < 0)
    {
        //throw std::system_error(WSAGetLastError(), std::system_category(), "recvfrom failed");
        DebugMsg::out("recvfrom failed with error: %d\n", WSAGetLastError());
        //freeaddrinfo(result);
        closesocket(ClientSocket);
        WSACleanup();
        state = NetworkState::OFFLINE;
        return;
    }
    udpbuff[ret] = 0;
    ClientUDPAddr = from;


    char* connConf = "connection confirmed";
    ret = sendto(ClientSocket, connConf, sizeof(connConf), 0, reinterpret_cast<SOCKADDR*>(&ClientUDPAddr), sizeof(ClientUDPAddr));
    if (ret < 0)
    {
        DebugMsg::out("sendto failed with error: %d\n", WSAGetLastError());
        closesocket(ClientSocket);
        WSACleanup();
        ClientSocket = INVALID_SOCKET;
        state = NetworkState::OFFLINE;
    }


    if (state == NetworkState::PENDING_HOST)
    {
        state = NetworkState::HOST;
        SceneManager::GetCurrentScene()->NotifyClientConnect(true);
        receiveThread = std::thread(&NetworkManager::ReceiveUDP, this);
    }

}

void NetworkManager::ConnectToHostUDP()
{
    REC_SHUTDOWN = false;
    WSADATA wsaData;
    ClientSocket = INVALID_SOCKET;
    struct addrinfo* result = NULL,
        * ptr = NULL,
        hints;



    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        DebugMsg::out("WSAStartup failed with error: %d\n", iResult);
        state = NetworkState::OFFLINE;
        return;
    }

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_protocol = IPPROTO_UDP;

    // Resolve the server address and port
    iResult = getaddrinfo("127.0.0.1", DEFAULT_PORT, &hints, &result);
    if (iResult != 0) {
        DebugMsg::out("getaddrinfo failed with error: %d\n", iResult);
        WSACleanup();
        state = NetworkState::OFFLINE;
        return;
    }

    // Attempt to connect to an address until one succeeds
    for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {

        // Create a SOCKET for connecting to server
        ClientSocket = socket(ptr->ai_family, ptr->ai_socktype,
            ptr->ai_protocol);
        if (ClientSocket == INVALID_SOCKET) {
            DebugMsg::out("socket failed with error: %ld\n", WSAGetLastError());
            WSACleanup();
            state = NetworkState::OFFLINE;
            return;
        }

        char* disc = "discovery request";

        sockaddr_in add;
        add.sin_family = AF_INET;
        inet_pton(AF_INET, "127.0.0.1", &add.sin_addr.s_addr);
        add.sin_port = htons(u_short(std::stoi(DEFAULT_PORT)));

        int ret = sendto(ClientSocket, disc, sizeof(disc), 0, reinterpret_cast<SOCKADDR*>(&add), sizeof(add));
        if (ret < 0)
        {
            closesocket(ClientSocket);
            ClientSocket = INVALID_SOCKET;
            continue;
        }
        break;
    }

    freeaddrinfo(result);

    if (ClientSocket == INVALID_SOCKET) {
        DebugMsg::out("Unable to connect to server!\n");
        WSACleanup();
        state = NetworkState::OFFLINE;
        SceneManager::GetCurrentScene()->NotifyConnectToHost(false);
        return;
    }
    char udpbuff[100];
    sockaddr_in from;
    int size = sizeof(from);
    int ret = recvfrom(ClientSocket, udpbuff, sizeof(udpbuff), 0, reinterpret_cast<SOCKADDR*>(&from), &size);
    if (ret < 0)
    {
        //throw std::system_error(WSAGetLastError(), std::system_category(), "recvfrom failed");
        DebugMsg::out("recvfrom failed with error: %d\n", WSAGetLastError());
        //freeaddrinfo(result);
        closesocket(ClientSocket);
        WSACleanup();
        state = NetworkState::OFFLINE;
        return;
    }
    udpbuff[ret] = 0;
    ServerUDPAddr = from;

    SceneManager::GetCurrentScene()->NotifyConnectToHost(true);

    receiveThread = std::thread(&NetworkManager::ReceiveUDP, this);
}

void NetworkManager::Receive()
{
    // Receive until the peer shuts down the connection
    while (!REC_SHUTDOWN)
    {
        NetworkMessage* NetMess;
        iResult = recv(ClientSocket, recvbuf, recvbuflen, 0);
        if (iResult > 0)
        {
            //FOR NOW WILL JUST PRINT MESSAGE
            DebugMsg::out("Bytes received: %d\n", iResult);
            std::string str(recvbuf, iResult);
            //DebugMsg::out("Message received: %s\n", str.c_str());

            NetMess = NetworkMessage::Deserialize(str);
            OutQueue.push_back(NetMess->GetData());
            //delete NetMess;
            NetMessCollection.push_back(NetMess);
        }
        else if (iResult == 0)
        {
            DebugMsg::out("Connection closing...\n");
            ShutdownConnections();
        }
        else {
            DebugMsg::out("recv failed with error: %d\n", WSAGetLastError());
            closesocket(ClientSocket);
            WSACleanup();
            state = NetworkState::OFFLINE;
            return;
        }
    }
}

void NetworkManager::CloseConnectThread()
{
    if (clientConnect.joinable())
        clientConnect.join();
}

void NetworkManager::ShutdownConnections()
{
    // shutdown the connection since we're done
    iResult = shutdown(ClientSocket, SD_SEND);
    if (iResult == SOCKET_ERROR) {
        DebugMsg::out("shutdown failed with error: %d\n", WSAGetLastError());
        closesocket(ClientSocket);
        WSACleanup();
        state = NetworkState::OFFLINE;
        return;
    }
    iResult = shutdown(ClientSocket, SD_RECEIVE);
    if (iResult == SOCKET_ERROR) {
        DebugMsg::out("shutdown failed with error: %d\n", WSAGetLastError());
        closesocket(ClientSocket);
        WSACleanup();
        state = NetworkState::OFFLINE;
        return;
    }

    REC_SHUTDOWN = true;

    // cleanup
    closesocket(ClientSocket);
    WSACleanup();

    //state = NetworkState::OFFLINE;
    if (hostOpen.joinable())
        hostOpen.join();
    if (clientConnect.joinable())
        clientConnect.join();


}

void NetworkManager::Send(DataMessage* _data)
{
    //create network message for uniform formatting to send across
    NetworkMessage* NetMess = new NetworkMessage();
    //DebugMsg::out("%s \n", sendbuf);

    // Send an initial buffer
    if (Instance().state == NetworkState::OFFLINE)
    {
        DebugMsg::out("Currently Offline... \n");
        delete _data;
        return;
    }
    if (Instance().state == NetworkState::PENDING_HOST)
    {
        DebugMsg::out("Waiting for Connections... \n");
        delete _data;
        return;
    }

    //cast the datamessage to proper data type and set value in network message
    switch (_data->type)
    {
    case DataMessage::DataMessage_Type::PLAYER_INPUT:
    {
        PlayerInputMessage* playerInput = (PlayerInputMessage*)_data;
        NetMess->Set_Data(playerInput);
        break;
    }
    case DataMessage::DataMessage_Type::UPDATE:
    {
        ObjectUpdateMessage* objUpdate = (ObjectUpdateMessage*)_data;
        NetMess->Set_Data(objUpdate);
        break;
    }
    case DataMessage::DataMessage_Type::GAME_STATE:
    {
        GameStateMessage* gameState = (GameStateMessage*)_data;
        NetMess->Set_Data(gameState);
        break;
    }
    case DataMessage::DataMessage_Type::COLLISION:
    {
        CollisionMessage* collision = (CollisionMessage*)_data;
        NetMess->Set_Data(collision);
        break;
    }
    case DataMessage::DataMessage_Type::CANCEL:
    {
        ConnectionCancelMessage* collision = (ConnectionCancelMessage*)_data;
        NetMess->Set_Data(collision);
        break;
    }
    default:
        break;
    }
    //serialize network message to sendable format
    std::string bytes = NetMess->Serialize();

    //send data
    Instance().iSendResult = send(Instance().ClientSocket, bytes.c_str(), (int)strlen(bytes.c_str()), 0);

    if (Instance().iSendResult == SOCKET_ERROR) {
        DebugMsg::out("send failed with error: %d\n", WSAGetLastError());
        closesocket(Instance().ClientSocket);
        WSACleanup();
        Instance().state = NetworkState::OFFLINE;
        return;
    }

    DebugMsg::out("Bytes Sent: %ld\n", Instance().iSendResult);
    //DebugMsg::out("Message Sent: %s\n", bytes.c_str());

    delete NetMess;

}

void NetworkManager::ReceiveUDP()
{
    // Receive until the peer shuts down the connection
    while (!REC_SHUTDOWN)
    {
        NetworkMessage* NetMess;

        sockaddr_in from;
        int size = sizeof(from);
        iResult = recvfrom(ClientSocket, recvbuf, recvbuflen, 0, reinterpret_cast<SOCKADDR*>(&from), &size);
        if (iResult > 0)
        {
            //FOR NOW WILL JUST PRINT MESSAGE
            DebugMsg::out("Bytes received: %d\n", iResult);
            std::string str(recvbuf, iResult);
            //DebugMsg::out("Message received: %s\n", str.c_str());

            NetMess = NetworkMessage::Deserialize(str);
            OutQueue.push_back(NetMess->GetData());
            //delete NetMess;
            NetMessCollection.push_back(NetMess);
        }
        else if (iResult == 0)
        {
            DebugMsg::out("Connection closing...\n");
            ShutdownConnections();
        }
        else {
            DebugMsg::out("recvFrom failed with error: %d\n", WSAGetLastError());
            closesocket(ClientSocket);
            WSACleanup();
            state = NetworkState::OFFLINE;
            return;
        }
    }
}

void NetworkManager::SendUDP(DataMessage* _data)
{
    //create network message for uniform formatting to send across
    NetworkMessage* NetMess = new NetworkMessage();
    //DebugMsg::out("%s \n", sendbuf);

    // Send an initial buffer
    if (Instance().state == NetworkState::OFFLINE)
    {
        DebugMsg::out("Currently Offline... \n");
        delete _data;
        return;
    }
    if (Instance().state == NetworkState::PENDING_HOST)
    {
        DebugMsg::out("Waiting for Connections... \n");
        delete _data;
        return;
    }

    //cast the datamessage to proper data type and set value in network message
    switch (_data->type)
    {
    case DataMessage::DataMessage_Type::PLAYER_INPUT:
    {
        PlayerInputMessage* playerInput = (PlayerInputMessage*)_data;
        NetMess->Set_Data(playerInput);
        break;
    }
    case DataMessage::DataMessage_Type::UPDATE:
    {
        ObjectUpdateMessage* objUpdate = (ObjectUpdateMessage*)_data;
        NetMess->Set_Data(objUpdate);
        break;
    }
    case DataMessage::DataMessage_Type::GAME_STATE:
    {
        GameStateMessage* gameState = (GameStateMessage*)_data;
        NetMess->Set_Data(gameState);
        break;
    }
    case DataMessage::DataMessage_Type::COLLISION:
    {
        CollisionMessage* collision = (CollisionMessage*)_data;
        NetMess->Set_Data(collision);
        break;
    }
    case DataMessage::DataMessage_Type::CANCEL:
    {
        ConnectionCancelMessage* collision = (ConnectionCancelMessage*)_data;
        NetMess->Set_Data(collision);
        break;
    }
    default:
        break;
    }
    //serialize network message to sendable format
    std::string bytes = NetMess->Serialize();

    //send data
    if (Instance().state == NetworkState::HOST)
        Instance().iSendResult = sendto(Instance().ClientSocket, bytes.c_str(), (int)strlen(bytes.c_str()), 0, reinterpret_cast<SOCKADDR*>(&Instance().ClientUDPAddr), sizeof(Instance().ClientUDPAddr));
    else if (Instance().state == NetworkState::CLIENT)
        Instance().iSendResult = sendto(Instance().ClientSocket, bytes.c_str(), (int)strlen(bytes.c_str()), 0, reinterpret_cast<SOCKADDR*>(&Instance().ServerUDPAddr), sizeof(Instance().ServerUDPAddr));

    if (Instance().iSendResult == SOCKET_ERROR) {
        DebugMsg::out("send failed with error: %d\n", WSAGetLastError());
        closesocket(Instance().ClientSocket);
        WSACleanup();
        Instance().state = NetworkState::OFFLINE;
        return;
    }

    DebugMsg::out("Bytes Sent: %ld\n", Instance().iSendResult);
    //DebugMsg::out("Message Sent: %s\n", bytes.c_str());

    delete NetMess;
}

void NetworkManager::EstablishHost()
{
    assert(Instance().state == NetworkState::OFFLINE);
    if (Instance().protocol == PROTOCOL::TCP)
    {
        Instance().state = NetworkState::PENDING_HOST;
        DebugMsg::out("Waiting for Client Connections...");
        Instance().hostOpen = std::thread(&NetworkManager::HostConnection, Instance().ptrInstance);
    }
    else if (Instance().protocol == PROTOCOL::UDP)
    {
        Instance().state = NetworkState::PENDING_HOST;
        DebugMsg::out("Waiting for Client Connections...");
        Instance().hostOpen = std::thread(&NetworkManager::HostConnectionUDP, Instance().ptrInstance);
    }
}

void NetworkManager::EstablishClient()
{
    assert(Instance().state == NetworkState::OFFLINE);
    if (Instance().protocol == PROTOCOL::TCP)
    {
        Instance().state = NetworkState::CLIENT;
        if (Instance().clientConnect.joinable())
            Instance().clientConnect.join();
        DebugMsg::out("Attempting Connection to Host...");
        Instance().clientConnect = std::thread(&NetworkManager::ConnectToHost, Instance().ptrInstance);
    }
    else if (Instance().protocol == PROTOCOL::UDP)
    {
        Instance().state = NetworkState::CLIENT;
        if (Instance().clientConnect.joinable())
            Instance().clientConnect.join();
        DebugMsg::out("Attempting Connection to Host...");
        Instance().clientConnect = std::thread(&NetworkManager::ConnectToHostUDP, Instance().ptrInstance);
    }
}

void NetworkManager::SendData(DataMessage* message)
{
    if (Instance().state == NetworkState::OFFLINE)
    {
        delete message;
        return;
    }
    if (Instance().state == NetworkState::PENDING_HOST)
    {
        delete message;
        return;
    }
    Instance().InQueue.push_back(message);
}

void NetworkManager::CancelHost()
{
    if (Instance().state == NetworkState::PENDING_HOST)
    {
        if (Instance().protocol == PROTOCOL::TCP)
            Instance().StopAccept();
        if (Instance().protocol == PROTOCOL::UDP)
            Instance().StopAcceptUDP();

        if (Instance().receiveThread.joinable())
            Instance().receiveThread.join();
        if (Instance().hostOpen.joinable())
            Instance().hostOpen.join();
        Instance().state = NetworkState::OFFLINE;
    }
    else if (Instance().state == NetworkState::HOST)
    {
        //send cancel message to client
        ConnectionCancelMessage* mess = new ConnectionCancelMessage();
        if (Instance().protocol == PROTOCOL::TCP)
            Instance().Send(mess);
        if (Instance().protocol == PROTOCOL::UDP)
            Instance().SendUDP(mess);

        Instance().REC_SHUTDOWN = true;

        //delete mess;
        Instance().ShutdownConnections();

        if (Instance().receiveThread.joinable())
            Instance().receiveThread.join();
        SceneManager::GetCurrentScene()->NotifyClientDisconnected();
    }
}

void NetworkManager::CancelClient()
{
    if (Instance().state == NetworkState::CLIENT)
    {
        //send cancel message to client
        ConnectionCancelMessage* mess = new ConnectionCancelMessage();
        if (Instance().protocol == PROTOCOL::TCP)
            Instance().Send(mess);
        if (Instance().protocol == PROTOCOL::UDP)
            Instance().SendUDP(mess);

        Instance().REC_SHUTDOWN = true;

        if (Instance().receiveThread.joinable())
            Instance().receiveThread.join();

        Instance().ShutdownConnections();
        Instance().state = NetworkState::OFFLINE;
        SceneManager::GetCurrentScene()->NotifyHostDisconnected();
    }
}

void NetworkManager::SetProtocol(NetworkManager::PROTOCOL _protocol)
{
    Instance().protocol = _protocol;
}

void NetworkManager::StopAccept()
{
    state = NetworkState::OFFLINE;
    WSADATA wsaData;
    SOCKET ConnectSocket = INVALID_SOCKET;
    struct addrinfo* result = NULL,
        * ptr = NULL,
        hints;


    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        DebugMsg::out("WSAStartup failed with error: %d\n", iResult);
        state = NetworkState::OFFLINE;
        return;
    }

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    // Resolve the server address and port
    iResult = getaddrinfo("127.0.0.1", DEFAULT_PORT, &hints, &result);
    if (iResult != 0) {
        DebugMsg::out("getaddrinfo failed with error: %d\n", iResult);
        WSACleanup();
        state = NetworkState::OFFLINE;
        return;
    }

    // Attempt to connect to an address until one succeeds
    for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {

        // Create a SOCKET for connecting to server
        ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype,
            ptr->ai_protocol);
        if (ConnectSocket == INVALID_SOCKET) {
            DebugMsg::out("socket failed with error: %ld\n", WSAGetLastError());
            WSACleanup();
            state = NetworkState::OFFLINE;
            return;
        }

        // Connect to server.
        iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
        if (iResult == SOCKET_ERROR) {
            closesocket(ConnectSocket);
            ConnectSocket = INVALID_SOCKET;
            continue;
        }
        break;
    }

    // shutdown the connection since no more data will be sent
    iResult = shutdown(ConnectSocket, SD_SEND);
    if (iResult == SOCKET_ERROR) {
        DebugMsg::out("shutdown failed with error: %d\n", WSAGetLastError());
        closesocket(ConnectSocket);
        WSACleanup();
        state = NetworkState::OFFLINE;
        return;
    }

    // cleanup
    closesocket(ConnectSocket);
    WSACleanup();
    state = NetworkState::OFFLINE;
}

void NetworkManager::StopAcceptUDP()
{
    state = NetworkState::OFFLINE;
    WSADATA wsaData;
    SOCKET ConnectSocket = INVALID_SOCKET;
    struct addrinfo* result = NULL,
        * ptr = NULL,
        hints;



    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        DebugMsg::out("WSAStartup failed with error: %d\n", iResult);
        state = NetworkState::OFFLINE;
        return;
    }

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_protocol = IPPROTO_UDP;

    // Resolve the server address and port
    iResult = getaddrinfo("127.0.0.1", DEFAULT_PORT, &hints, &result);
    if (iResult != 0) {
        DebugMsg::out("getaddrinfo failed with error: %d\n", iResult);
        WSACleanup();
        state = NetworkState::OFFLINE;
        return;
    }

    // Attempt to connect to an address until one succeeds
    for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {

        // Create a SOCKET for connecting to server
        ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype,
            ptr->ai_protocol);
        if (ConnectSocket == INVALID_SOCKET) {
            DebugMsg::out("socket failed with error: %ld\n", WSAGetLastError());
            WSACleanup();
            state = NetworkState::OFFLINE;
            return;
        }

        char* canc = "cancel request";

        sockaddr_in add;
        /* DEPRECATED
        add.sin_family = AF_INET;
        add.sin_addr.s_addr = inet_pton("127.0.0.1");
        add.sin_port = htons(u_short(std::stoi(DEFAULT_PORT)));
        //*/
        add.sin_family = AF_INET;
        inet_pton(AF_INET, "127.0.0.1", &add.sin_addr.s_addr);
        add.sin_port = htons(u_short(std::stoi(DEFAULT_PORT)));

        int ret = sendto(ConnectSocket, canc, sizeof(canc), 0, reinterpret_cast<SOCKADDR*>(&add), sizeof(add));
        if (ret < 0)
        {
            closesocket(ConnectSocket);
            ConnectSocket = INVALID_SOCKET;
            continue;
        }
        break;
    }

    freeaddrinfo(result);

    if (ConnectSocket == INVALID_SOCKET) {
        DebugMsg::out("Unable to connect to server!\n");
        WSACleanup();
        state = NetworkState::OFFLINE;
        SceneManager::GetCurrentScene()->NotifyConnectToHost(false);
        return;
    }
    char udpbuff[100];
    sockaddr_in from;
    int size = sizeof(from);
    int ret = recvfrom(ConnectSocket, udpbuff, sizeof(udpbuff), 0, reinterpret_cast<SOCKADDR*>(&from), &size);
    if (ret < 0)
    {
        //throw std::system_error(WSAGetLastError(), std::system_category(), "recvfrom failed");
        DebugMsg::out("recvfrom failed with error: %d\n", WSAGetLastError());
        //freeaddrinfo(result);
        closesocket(ConnectSocket);
        WSACleanup();
        state = NetworkState::OFFLINE;
        return;
    }
    udpbuff[ret] = 0;

    // shutdown the connection since no more data will be sent
    iResult = shutdown(ConnectSocket, SD_SEND);
    if (iResult == SOCKET_ERROR) {
        DebugMsg::out("shutdown failed with error: %d\n", WSAGetLastError());
        closesocket(ConnectSocket);
        WSACleanup();
        state = NetworkState::OFFLINE;
        return;
    }

    // cleanup
    closesocket(ConnectSocket);
    WSACleanup();
    state = NetworkState::OFFLINE;
}

void NetworkManager::ClearStoredMessages()
{
    for (NetworkMessage* dm : NetMessCollection)
    {
        delete dm;
    }
    NetMessCollection.clear();
}

void NetworkManager::ProcessInputQueue()
{
    std::list<DataMessage*>::iterator it;
    it = Instance().InQueue.begin();
    while (it != Instance().InQueue.end())
    {
        if (Instance().protocol == PROTOCOL::TCP)
            NetworkManager::Send(*it);
        else if (Instance().protocol == PROTOCOL::UDP)
            NetworkManager::SendUDP(*it);
        it = Instance().InQueue.erase(it);
    }
    //Instance().ClearStoredMessages();
    //Instance().NetMessCollection.clear();
}

void NetworkManager::ProcessOutputQueue()
{
    std::list<DataMessage*>::iterator it;
    it = Instance().OutQueue.begin();
    while (it != Instance().OutQueue.end())
    {
        switch ((*it)->type)
        {
        case DataMessage::DataMessage_Type::PLAYER_INPUT:
        {
            //PlayerInputMessage* inMess = (PlayerInputMessage*)(*it);
            Instance().ProcessInputMessage((PlayerInputMessage*)(*it));
            //delete inMess;
            break;
        }
        case DataMessage::DataMessage_Type::UPDATE:
        {
            //ObjectUpdateMessage* inMess = (ObjectUpdateMessage*)(*it);
            Instance().ProcessUpdateMessage((ObjectUpdateMessage*)(*it));
            //delete inMess;
            break;
        }
        case DataMessage::DataMessage_Type::GAME_STATE:
        {
            //GameStateMessage* inMess = (GameStateMessage*)(*it);
            Instance().ProcessGameStateMessage((GameStateMessage*)(*it));
            //delete inMess;
            break;
        }
        case DataMessage::DataMessage_Type::COLLISION:
        {
            //CollisionMessage* inMess = (CollisionMessage*)(*it);
            Instance().ProcessCollisionMessage((CollisionMessage*)(*it));
            //delete inMess;
            break;
        }
        case DataMessage::DataMessage_Type::CANCEL:
        {
            //incoming cancel message
            //ConnectionCancelMessage* inMess = (ConnectionCancelMessage*)(*it);
            //inMess;
            //DO SOMETHING WITH THIS INFORMATION
            //call cancel now as if cancel was pressed
            if (Instance().state == NetworkState::CLIENT)
                Instance().CancelClient();
            if (Instance().state == NetworkState::HOST)
                Instance().CancelHost();
            //delete inMess;
            break;
        }
        default:
            break;
        }
        it = Instance().OutQueue.erase(it);
    }
    Instance().ClearStoredMessages();
}

NetworkManager::~NetworkManager()
{
    if (state == NetworkState::PENDING_HOST)
        StopAccept();

    for (DataMessage* dm : InQueue)
    {
        delete dm;
    }
    for (DataMessage* dm : OutQueue)
    {
        delete dm;
    }

    //ClearStoredMessages();
    NetMessCollection.clear();

    //exitSignal.set_value();
    REC_SHUTDOWN = true;

    ShutdownConnections();

    if (receiveThread.joinable())
        receiveThread.join();
    if (hostOpen.joinable())
        hostOpen.join();
    if (clientConnect.joinable())
        clientConnect.join();
}

