#include <array>
#include <cerrno>
#include <chrono>
#include <cstdint>
#include <iostream>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

std::array<uint8_t, 1536> packet; // (3<<9)
sockaddr_in scaServer, scaMulti;

int main() {
	int recv_fd = socket(AF_INET, SOCK_DGRAM, 0), send_fd = socket(AF_INET, SOCK_DGRAM, 0);
	if (recv_fd < 0 || send_fd < 0) {
		std::cerr << "Can't create sockets.\n";
		return 0;
	}

	scaServer.sin_family = AF_INET;
	scaServer.sin_addr.s_addr = inet_addr("192.167.1.1");
	scaServer.sin_port = htons(9430);

	scaMulti.sin_family = AF_INET;
	scaMulti.sin_addr.s_addr = inet_addr("239.28.4.94");
	scaMulti.sin_port = htons(5005);

	if (bind(recv_fd, (sockaddr const *)&scaServer, sizeof(scaServer)) < 0) {
		std::cerr << "bind for receive socket failed\n";
		return 0;
	}

	auto time = std::chrono::system_clock::now();
	for (int i=0; ; ++i) {
		int bytes = recv(recv_fd, packet.data(), packet.size(), 0);
		int val = sendto(send_fd, packet.data(), bytes, 0, (sockaddr const *)&scaMulti, sizeof(scaMulti));
		if (val == -1)
			std::cerr << "Error: " <<  errno << std::endl;
		auto prev_time = time;
		time = std::chrono::system_clock::now();
		auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(time - prev_time);
		std::cout << i << ' ' << size_t(packet[0]) << ' ' <<  bytes << ' ' << diff.count() << std::endl;
//		for (int j=0; j<bytes; ++j)
//			std::cout << size_t(packet[j]) << ' ';
//		std::cout << std::endl;
	}

	return 0;
}
