#include <iostream>
#include <WS2tcpip.h>
#include <string>
#include <sstream>
#pragma comment (lib, "ws2_32.lib")

void main()
{
    //Initialize winsock
    WSADATA wsData;
    WORD ver = MAKEWORD(2, 2);

    int winsockOK = WSAStartup(ver, &wsData);
    if (winsockOK != 0)
    {
        std::cerr << "Can't initialize winsock! Quitting" << std::endl;
        return;
    }

    //Create a socket
    SOCKET listening = socket(AF_INET, SOCK_STREAM, 0);
    if (listening == INVALID_SOCKET)
    {
        std::cerr << "Can't create a socket! Quitting" << std::endl;
        return;
    }

    //Bind the socket to an ip address and port
    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(54000);
    hint.sin_addr.S_un.S_addr = INADDR_ANY;

    bind(listening, (sockaddr*)&hint, sizeof(hint));

    //Tell winsock the socket is for listening
    listen(listening, SOMAXCONN);

    fd_set master;
    FD_ZERO(&master);

    FD_SET(listening, &master);

    while (true)
    {
        fd_set copy = master;

        int socketCount = select(0, &copy, nullptr, nullptr, nullptr);

        for (int i = 0; i < socketCount; i++)
        {
            SOCKET sock = copy.fd_array[i];
            if (sock == listening)
            {
                //Accept the new connection
                SOCKET client = accept(listening, nullptr, nullptr);

                std::cout << "Hello new person" << std::endl;

                //Add the new connection to the list of connected clients
                FD_SET(client, &master);
            }
            else
            {
                char buf[4096];
                ZeroMemory(buf, 4096);

                int bytesIn = recv(sock, buf, 4096, 0);
                if (bytesIn <= 0)
                {
                    //Drop the client
                    closesocket(sock);
                    FD_CLR(sock, &master);
                }
                else 
                {
                    for (int i = 0; i < master.fd_count; i++)
                    {
                        SOCKET outSock = master.fd_array[i];
                        
                        std::ostringstream ss;

                        ss << buf;

                        std::string strOut = ss.str();

                        std::cout << strOut << std::endl;

                        if (outSock != listening && outSock != sock)
                        {
                            send(outSock, strOut.c_str(), strOut.size() + 1, 0);
                        }
                    }
                }
            }
        }
    }

    //Cleanup winsock
    WSACleanup();
}


////Wait for a connection
    //sockaddr_in client;
    //int clientSize = sizeof(client);

    //SOCKET clientSocket = accept(listening, (sockaddr*)&client, &clientSize);
    //if (clientSocket == INVALID_SOCKET)
    //{
    //    std::cerr << "accept Socket Invalid! Quitting" << std::endl;
    //    return;
    //}

    //char host[NI_MAXHOST];      //Client's remote name
    //char service[NI_MAXSERV];   //Service (I.E. port) the client is connected on

    //ZeroMemory(host, NI_MAXHOST);
    //ZeroMemory(service, NI_MAXSERV);

    //if (getnameinfo((sockaddr*)&client, sizeof(client), host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0)
    //{
    //   std::cout << host << " Connected on port " << service << std::endl;
    //}
    //else
    //{
    //    inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
    //    std::cout << host << " connected on port " <<
    //        ntohs(client.sin_port) << std::endl;
    //}

    ////Close listening socket
    //closesocket(listening);

    //// While loop: acceto and echo message back to client
    //char buf[4096];

    //while (true)
    //{
    //    ZeroMemory(buf, 4096);

    //    //Wait for client to send data
    //    int bytesRecieved = recv(clientSocket, buf, 4096, 0);
    //    if (bytesRecieved == SOCKET_ERROR)
    //    {
    //        std::cerr << "Error in recv(). Quitting" << std::endl;
    //    }

    //    if (bytesRecieved == 0)
    //    {
    //        std::cout << "Client disconnected " << std::endl;
    //        break;
    //    }

    //    //Echo message back to client

    //    std::string s(buf, sizeof(buf));
    //    std::cout << "The client sent the message " << s << std::endl;
    //    send(clientSocket, buf, bytesRecieved + 1, 0);
    //    
    //}
    //Close socket