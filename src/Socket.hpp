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
	std::string _recv_msg;
	std::string _send_msg;

	Socket();
	Socket(const Socket &ref);
	Socket &operator=(const Socket &ref);

	void ft_create_socket();

public:
	Socket(int fd, sockaddr *socket_info);
	Socket(const char *IP, const char *port);
	~Socket();

	int ft_poll();
	int ft_get_socket_fd();
	std::string ft_get_socket_IP();
	void ft_set_time();
	time_t ft_get_time();
	Socket *ft_accept();
	bool ft_ping();
	bool ft_pong(std::string msg);
	std::string ft_push_recv_msg(std::string recv_msg);
	void ft_set_recv_msg(std::string recv_msg);
	void ft_append_send_msg(std::string send_msg);
	void ft_send_msg();
};
#endif
