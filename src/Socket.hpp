#ifndef SOCKET_HPP
#define SOCKET_HPP

#ifndef SOCONN
#define SOCONN 100
#endif

#include <string>
#include <sys/poll.h>
#include <netdb.h>

class Socket
{
private:
	/* data */
	int _fd;
	addrinfo *_info;
	sockaddr _socket_info;
	pollfd _pfd;

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
	Socket *ft_accept();
};

#endif
