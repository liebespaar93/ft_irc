#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <map>

#include "User.hpp"
class User;

class Channel
{

private:
	Channel();
	Channel(const Channel &ref){};
	Channel &operator=(const Channel &ref) {return *this;};
	/* data */
	std::string _channel_name;
	std::string _channel_topic;
	std::string _password;

	std::map<std::string, User *> _privilege_user_map;

	bool _has_password;
	bool _is_invite_only;
	bool _is_restricted;
	int _limit;

	std::map<std::string, User *> _user_list;

public:
	Channel(std::string channel_name) : _channel_name(channel_name){};
	~Channel() { this->_user_list.clear(); };

	std::string const &ft_get_name() { return this->_channel_name; };
	std::string const &ft_get_topic() { return this->_channel_topic; }
	std::string const &ft_get_password() { return this->_password; }

	int const &ft_get_limit() { return this->_limit; }
	bool const &ft_get_has_password() { return this->_has_password; }
	bool const &ft_get_restrict() { return this->_is_restricted; }
	bool const &ft_get_invite()  { return this->_is_invite_only; }
	std::map<std::string, User *> &ft_get_user_list() { return this->_user_list; }

	void ft_set_limit(int limit) { this->_limit = limit; }
	void ft_set_password(const std::string new_password) { this->_password = new_password; }
	void ft_set_restrict(bool on) { this->_is_restricted = on; }
	void ft_set_has_password(bool on) { this->_has_password = on; }
	void ft_set_invite(bool on) { this->_is_invite_only = on; }
	void ft_set_topic(const std::string new_topic) { this->_channel_topic = new_topic; }

	int ft_channel_join_user(User *user);
	int ft_channel_join_user(User *user, std::string password);
	int ft_channel_leave_user(User *user);
	void ft_send_all(std::string user_name, std::string buf);
	void ft_send_me(std::string user_name, std::string buf);

	int ft_privilege_user_authorization(User *user);
	int ft_privilege_user_delete(std::string user_name);
	std::string ft_privilege_has_user(std::string user_name);
};

#endif
