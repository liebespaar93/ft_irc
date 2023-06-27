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
	Channel(const Channel &ref);
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
	Channel(std::string channel_name);
	~Channel();
	Channel &operator=(const Channel &ref);

	std::string const &ft_get_name();
	std::string const &ft_get_topic();
	std::string const &ft_get_password();

	size_t const &ft_get_limit();
	bool const &ft_get_has_password();
	bool const &ft_get_restrict();
	bool const &ft_get_invite();
	std::map<std::string, User *> &ft_get_user_list();
	User *ft_get_topic_user();
	const std::string &ft_get_topic_time();

	void ft_set_limit(size_t limit);
	void ft_set_password(const std::string new_password);
	void ft_set_restrict(bool on);
	void ft_set_has_password(bool on);
	void ft_set_invite(bool on);
	void ft_set_topic(const std::string new_topic);
	void ft_set_topic_user(User *user);
	void ft_set_topic_time(const std::string &time);

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

	bool ft_mode_has();
};

#endif
