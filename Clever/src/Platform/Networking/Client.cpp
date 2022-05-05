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
		std::string space_delimiter = ",";

		ZeroMemory(buf, 4096);
		int bytesRecieved = recv(m_Sock, buf, 4096, 0);
		if (bytesRecieved > 0)
		{
			std::string data = std::string(buf, 0, bytesRecieved);

			std::vector<std::string> words{};

			size_t pos = 0;
			while ((pos = data.find(space_delimiter)) != std::string::npos) {
				words.push_back(data.substr(0, pos));
				data.erase(0, pos + space_delimiter.length());
			}
			float one = std::stof(words[0]);
			float two = std::stof(words[1]);
			float three = std::stof(words[2]);

			return glm::vec3(one, two, three);
		}
		return {0,0,0};
	}

	void Client::sendPosition(glm::vec3 position)
	{
		std::string data = std::to_string(position[0]) + "," + std::to_string(position[1]) + "," + std::to_string(position[2]);
		int sendResult = send(m_Sock, data.c_str(), data.size() + 1, 0);
	}
}