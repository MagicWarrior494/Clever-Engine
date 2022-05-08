#include "cvpch.h"
#include "Client.h"
#pragma comment (lib, "ws2_32.lib")

namespace Clever {

	Client::Client(std::string ipAddress, int port)
		: m_IpAddress(ipAddress), m_Port(port)
	{
		//Initialize WinSock
		WSAData data;
		WORD ver = MAKEWORD(2, 2);
		int winSockResult = WSAStartup(ver, &data);
		if (winSockResult != 0)
		{
			std::cerr << "Can't initialize winsock! Quitting, Err # " << winSockResult << std::endl;
			return;
		}

		//Create Socket
		m_Sock = socket(AF_INET, SOCK_STREAM, 0);
		if (m_Sock == INVALID_SOCKET)
		{
			std::cerr << "Can't create a socket! Quitting, Err # " << WSAGetLastError() << std::endl;
			WSACleanup();
			return;
		}

		//Fill in a hint structure
		sockaddr_in hint;
		hint.sin_family = AF_INET;
		hint.sin_port = htons(port);
		inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr);

		//Connect to server
		int connResult = connect(m_Sock, (sockaddr*)&hint, sizeof(hint));
		if (connResult == SOCKET_ERROR)
		{
			std::cerr << "Can't connect to server, err # " << WSAGetLastError() << std::endl;
			closesocket(m_Sock);
			WSACleanup();
			return;
		}

		unsigned long nonBlocking = 1;
		int result = ioctlsocket(m_Sock, FIONBIO, &nonBlocking);
		if (result == SOCKET_ERROR)
		{
			int error = WSAGetLastError();
			closesocket(m_Sock);
			WSACleanup();
		}
	}
	
	Client::~Client()
	{
		closesocket(m_Sock);
		WSACleanup();
	}

	glm::vec3 Client::GetPositons()
	{
		char buf[4096];

		ZeroMemory(buf, 4096);
		int bytesRecieved = recv(m_Sock, buf, 4096, 0);
		if (bytesRecieved > 0)
		{
			std::ostringstream ss;
			ss << buf;

			std::string data = ss.str();

			std::vector<float> positions{};

			std::stringstream s_stream(data); //create string stream from the string
			while (s_stream.good()) {
				std::string substr;
				getline(s_stream, substr, ','); //get first string delimited by comma
				std::cout << substr << std::endl;
				positions.push_back(std::stof(substr));
			}

			if (positions.size() == 3)
			{
				m_Pos = { positions.at(0), positions.at(1), positions.at(2) };
				return { positions.at(0), positions.at(1), positions.at(2) };
			}
		}
		return m_Pos;
	}

	void Client::sendPosition(glm::vec3 position)
	{
		std::string data = std::to_string(position.x) + "," + std::to_string(position.y) + "," + std::to_string(position.z);
		int sendResult = send(m_Sock, data.c_str(), data.size() + 1, 0);
	}
}