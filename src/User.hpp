#ifndef USER_HPP
#define USER_HPP

#include <string>
#include <map>
#include "Socket.hpp"
#include "Channel.hpp"

class Channel;

class User
{

private:
	/* data */
	int _fd;
	std::string _user_name;
	std::string _nick_name;
	std::string _IP;
	std::map<std::string, Channel *> _channel_list;
	bool _pass;

	User(){};
	User(const User &ref){};
	User &operator=(const User &ref)
	{
		*this = ref;
		return *this;
	};

public:
	User(int fd) : _fd(fd), _user_name(""), _nick_name(""), _IP(""), _pass(false){};
	~User(){};

	const int &ft_get_fd() { return this->_fd; };
	const std::string ft_get_user_name() { return this->_user_name; };
	const std::string ft_get_nick_name() { return this->_nick_name; };
	const std::map<std::string, Channel *> ft_get_channel_list() { return this->_channel_list; };
	const inline size_t ft_get_channel_size() { return this->_channel_list.size(); };
	bool ft_get_pass() { return this->_pass; }
	std::string ft_get_IP() { return this->_IP; };

	void ft_set_nick_name(std::string nick_name) { this->_nick_name = nick_name; };
	void ft_set_user_name(std::string user_name) { this->_user_name = user_name; };
	void ft_set_IP(std::string IP) { this->_IP = IP; };
	void ft_set_pass() { this->_pass = true; }

	void ft_append_channel(Channel *channel);
	void ft_delete_channel(std::string channel_name);
};

#endif
