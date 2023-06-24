#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <map>
#include <iostream>

#include "User.hpp"
#include "Logger.hpp"
class User;

class Channel
{

private:
	Channel();
	Channel(const Channel &ref) { (void)ref; };
	/* data */
	std::string _channel_name;
	std::string _channel_topic;
	User *_channel_topic_user;
	std::string _channel_topic_time;
	std::string _password;

	std::map<std::string, User *> _privilege_user_map;

	bool _has_password;
	bool _is_invite_only;
	bool _is_restricted;
	size_t _limit;

	std::map<std::string, User *> _user_list;
	std::map<std::string, User *> _invite_map;

public:
	Channel(std::string channel_name)
		: _channel_name(channel_name), _has_password(false), _is_invite_only(false), _is_restricted(false), _limit(0)
	{
		Logger("channel_create").ft_channel_create(this->_channel_name);
	};
	~Channel()
	{
		this->_user_list.clear();
		Logger("channel_destory ").ft_channel_destory(this->_channel_name);
	};

	Channel &operator=(const Channel &ref)
	{
		this->_channel_name = ref._channel_name;
		this->_channel_topic = ref._channel_topic;
		this->_password = ref._password;
		this->_privilege_user_map = ref._privilege_user_map;
		this->_has_password = ref._has_password;
		this->_is_invite_only = ref._is_invite_only;
		this->_is_restricted = ref._is_restricted;
		this->_limit = ref._limit;
		this->_invite_map = ref._invite_map;
		return *this;
	};

	std::string const &ft_get_name() { return this->_channel_name; };
	std::string const &ft_get_topic() { return this->_channel_topic; };
	std::string const &ft_get_password() { return this->_password; };

	size_t const &ft_get_limit() { return this->_limit; };
	bool const &ft_get_has_password() { return this->_has_password; };
	bool const &ft_get_restrict() { return this->_is_restricted; };
	bool const &ft_get_invite() { return this->_is_invite_only; };
	std::map<std::string, User *> &ft_get_user_list() { return this->_user_list; };
	User *ft_get_topic_user() { return this->_channel_topic_user; };
	const std::string &ft_get_topic_time() { return this->_channel_topic_time; };

	void ft_set_limit(size_t limit) { this->_limit = limit; };
	void ft_set_password(const std::string new_password) { this->_password = new_password; };
	void ft_set_restrict(bool on) { this->_is_restricted = on; };
	void ft_set_has_password(bool on) { this->_has_password = on; };
	void ft_set_invite(bool on) { this->_is_invite_only = on; };
	void ft_set_topic(const std::string new_topic) { this->_channel_topic = new_topic; };
	void ft_set_topic_user(User *user) { this->_channel_topic_user = user; };
	void ft_set_topic_time(const std::string &time) { this->_channel_topic_time = time; };

	int ft_channel_join_user(User *user);
	int ft_channel_join_user(User *user, std::string password);
	int ft_channel_leave_user(User *user);
	void ft_send_all(std::string user_name, std::string buf);
	void ft_send_me(std::string user_name, std::string buf);

	int ft_privilege_user_authorization(User *user);
	int ft_privilege_user_delete(std::string user_name);
	bool ft_privilege_has_user(std::string user_name);

	int ft_invite_append_user(User *user);
	int ft_invite_delete_user(User *user);
	bool ft_invite_has_user(User *user);
};

#endif
