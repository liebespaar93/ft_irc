#include "Channel.hpp"
#include "Logger.hpp"

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
