#ifndef USER_HPP
#define USER_HPP

#include <string>
#include "Socket.hpp"

class User
{

private:
	/* data */
	int _fd;
	std::string _user_name;
	std::string _nick_name;
	std::string _IP;

	User(){};
	User(const User &ref){};
	User &operator=(const User &ref)
	{
		*this = ref;
		return *this;
	};

public:
	User(int fd): _fd(fd), _user_name(""), _nick_name(""), _IP(""){};
	~User(){};

	const int &ft_get_fd() { return this->_fd; };
	const std::string &ft_get_user_name() { return this->_user_name; };
	const std::string &ft_get_nick_name() { return this->_nick_name; };
	void ft_set_nick_name(std::string nick_name) { this->_nick_name = nick_name; };
	void ft_set_user_name(std::string user_name) { this->_user_name = user_name; };
	void ft_set_IP(std::string IP) { this->_IP = IP; };
};

#endif
