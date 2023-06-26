#include "Channel.hpp"
#include "Logger.hpp"

Channel::Channel(){};
Channel::Channel(const Channel &ref) { (void)ref; }

Channel::Channel(std::string channel_name)
	: _channel_name(channel_name)
	, _has_password(false)
	, _is_invite_only(false)
	, _is_restricted(true)
	, _limit(0)
{
	Logger("channel_create").ft_channel_create(this->_channel_name);
}
Channel::~Channel()
{
	this->_user_list.clear();
	Logger("channel_destory ").ft_channel_destory(this->_channel_name);
}
Channel &Channel::operator=(const Channel &ref)
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
}

int Channel::ft_channel_join_user(User *user)
{
	if (this->_user_list.find(user->ft_get_user_name()) != this->_user_list.end())
		return (1);
	if (this->_limit && this->_limit <= this->_user_list.size())
		return (471); 
	this->_user_list.insert(std::pair<std::string, User *>(user->ft_get_user_name(), user));
	user->ft_append_channel(this);
	this->ft_invite_delete_user(user);
	Logger(user->ft_get_nick_name()).ft_join(this->_channel_name);
	return (0);
}

int Channel::ft_channel_join_user(User *user, std::string password)
{
	if (this->_user_list.find(user->ft_get_user_name()) != this->_user_list.end())
		return (1);
	if (this->_limit && this->_limit <= this->_user_list.size())
		return (471);
	if (!this->ft_invite_has_user(user) || !this->_password.compare(password))
		return (475);
	this->_user_list.insert(std::pair<std::string, User *>(user->ft_get_user_name(), user));
	user->ft_append_channel(this);
	this->ft_invite_delete_user(user);
	Logger(user->ft_get_nick_name()).ft_join(this->_channel_name);
	return (0);
}

int Channel::ft_channel_leave_user(User *user)
{
	if (!user)
	{
		Logger("ft_channel_leave_user :  NULL").ft_error();
		return (1);
	}
	this->ft_privilege_user_delete(user->ft_get_user_name());
	if (this->_user_list.find(user->ft_get_user_name()) == this->_user_list.end())
		return (442);
	this->_user_list.erase(user->ft_get_user_name());
	user->ft_delete_channel(this->_channel_name);
	Logger(user->ft_get_nick_name()).ft_leave(this->_channel_name);
	return (0);
}

void Channel::ft_send_all(std::string user_name, std::string buf)
{
	std::map<std::string, User *>::iterator it = this->_user_list.begin();
	while (it != this->_user_list.end())
	{
		if ((*it).first != user_name)
			send((*it).second->ft_get_fd(), buf.c_str(), buf.length(), 0);
		it++;
	}
}

void Channel::ft_send_me(std::string user_name, std::string buf)
{
	send(this->_user_list.at(user_name)->ft_get_fd(), buf.c_str(), buf.length(), 0);
}

int Channel::ft_privilege_user_authorization(User *user)
{
	if (this->_privilege_user_map.find(user->ft_get_user_name()) != this->_privilege_user_map.end())
		return (1);
	this->_privilege_user_map.insert(std::pair<std::string, User *>(user->ft_get_user_name(), user));
	return (0);
}

int Channel::ft_privilege_user_delete(std::string user_name)
{
	if (this->_privilege_user_map.find(user_name) == this->_privilege_user_map.end())
		return (1);
	this->_privilege_user_map.erase(user_name);
	return (0);
}

bool Channel::ft_privilege_has_user(std::string user_name)
{
	if (this->_privilege_user_map.find(user_name) != this->_privilege_user_map.end())
		return (true);
	return (false);
}

int Channel::ft_invite_append_user(User *user)
{
	if (this->_invite_map.find(user->ft_get_user_name()) != this->_invite_map.end())
		return (0);
	this->_invite_map.insert(std::pair<std::string, User* >(user->ft_get_user_name(), user));
	return (0);
}

int Channel::ft_invite_delete_user(User *user)
{
	if (this->_invite_map.find(user->ft_get_user_name()) != this->_invite_map.end())
		return (0);
	this->_invite_map.erase(user->ft_get_user_name());
	return (0);
}

bool Channel::ft_invite_has_user(User *user)
{
	if (this->_invite_map.find(user->ft_get_user_name()) != this->_invite_map.end())
		return (true);
	return (false);
}

std::string const &Channel::ft_get_name() { return this->_channel_name; }
std::string const &Channel::ft_get_topic() { return this->_channel_topic; }
std::string const &Channel::ft_get_password() { return this->_password; }
size_t const &Channel::ft_get_limit() { return this->_limit; }
bool const &Channel::ft_get_has_password() { return this->_has_password; }
bool const &Channel::ft_get_restrict() { return this->_is_restricted; }
bool const &Channel::ft_get_invite() { return this->_is_invite_only; }
std::map<std::string, User *> &Channel::ft_get_user_list() { return this->_user_list; }
User *Channel::ft_get_topic_user() { return this->_channel_topic_user; }
const std::string &Channel::ft_get_topic_time() { return this->_channel_topic_time; }
void Channel::ft_set_limit(size_t limit) { this->_limit = limit; }
void Channel::ft_set_password(const std::string new_password) { this->_password = new_password; }
void Channel::ft_set_restrict(bool on) { this->_is_restricted = on; }
void Channel::ft_set_has_password(bool on) { this->_has_password = on; }
void Channel::ft_set_invite(bool on) { this->_is_invite_only = on; }
void Channel::ft_set_topic(const std::string new_topic) { this->_channel_topic = new_topic; }
void Channel::ft_set_topic_user(User *user) { this->_channel_topic_user = user; }
void Channel::ft_set_topic_time(const std::string &time) { this->_channel_topic_time = time; }
