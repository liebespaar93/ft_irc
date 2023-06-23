#ifndef SOCKET_HPP
#define SOCKET_HPP

#ifndef SOCONN
#define SOCONN 100
#endif

#include <string>
#include <sys/poll.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <ctime>

class Socket
{
private:
	/* data */
	int _fd;
	addrinfo *_info;
	sockaddr _socket_info;
	pollfd _pfd;
	time_t _time;
	bool _ping_check;
	std::string _msg;

	Socket(){};
	Socket(const Socket &ref);
	Socket &operator=(const Socket &ref) { return *this; };

	void ft_create_socket();

public:
	Socket(int fd, sockaddr *socket_info);
	Socket(const char *IP, const char *port);
	~Socket();

	int ft_poll();

	int ft_get_socket_fd() { return this->_fd; };
	std::string ft_get_socket_IP() { return ((std::string)inet_ntoa(((sockaddr_in *)&this->_socket_info)->sin_addr)); }

	void ft_set_time() { this->_time = time(NULL); }
	time_t ft_get_time() { return this->_time; }

	Socket *ft_accept();

	bool ft_ping();
	bool ft_pong(std::string msg);
	std::string ft_push_msg(std::string msg) { this->_msg += msg;  return this->_msg;};
	void ft_set_msg(std::string msg) { this->_msg = msg; };
};
#endif
