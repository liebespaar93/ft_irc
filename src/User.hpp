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
	std::string _real_name;
	std::string _user_name;
	std::string _nick_name;
	std::string _IP;
	std::map<std::string, Channel *> _channel_list;
	bool _pass;
	bool _login;
	bool _wellcome;

	User();
	User(const User &ref);
	User &operator=(const User &ref);

public:
	User(int fd);
	~User();

	const int &ft_get_fd();
	const std::string ft_get_user_name();
	const std::string ft_get_nick_name();
	const std::string ft_get_real_name();
	const std::map<std::string, Channel *> ft_get_channel_list();
	size_t ft_get_channel_size();
	Channel *ft_get_channel(const std::string &channel_name);
	bool ft_get_pass();
	bool ft_get_login();
	bool ft_get_wellcome();
	std::string ft_get_IP();
	std::string ft_get_info();

	void ft_set_nick_name(std::string nick_name);
	void ft_set_user_name(std::string user_name);
	void ft_set_real_name(std::string real_name);
	void ft_set_IP(std::string IP);
	void ft_set_pass();
	void ft_set_login();
	void ft_set_wellcome();

	void ft_quit();

	void ft_append_channel(Channel *channel);
	void ft_delete_channel(std::string channel_name);
};

#endif
