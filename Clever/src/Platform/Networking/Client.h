#pragma once
#include  <string>
#include <glm/glm.hpp>
#include <WS2tcpip.h>
#include <vector>

namespace Clever {
	class Client {
	public:

		Client(std::string ipAddress, int port);
		~Client();

		void sendPosition(glm::vec3 position);
		glm::vec3 GetPositons();

	private:
		std::string m_IpAddress;
		int m_Port;
		SOCKET m_Sock = 0;
	};
}