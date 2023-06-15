#include "Channel.hpp"

int	Channel::ft_channel_join_user(User *user)
{
	if (this->_user_list.find(user->ft_get_user_name()) != this->_user_list.end())
		return (1);
	if (this->_limit <= this->_user_list.size())
		return (471); // ERR_CHANNELISFULL
	this->_user_list.insert( std::pair<std::string, User *>(user->ft_get_user_name(), user));
	return (0);
}

int	Channel::ft_channel_join_user(User *user, std::string password)
{
	if (this->_user_list.find(user->ft_get_user_name()) != this->_user_list.end())
		return (1);
	if (this->_limit <= this->_user_list.size())
		return (471); // ERR_CHANNELISFULL
	if (!this->_password.compare(password))
		return (475); // ERR_BADCHANNELKEY
	this->_user_list.insert( std::pair<std::string, User *>(user->ft_get_user_name(), user));
	return (0);
}

int	Channel::ft_channel_leave_user(User *user)
{
	this->ft_privilege_user_delete(user->ft_get_user_name());
	if (this->_user_list.find(user->ft_get_user_name()) == this->_user_list.end())
		return (442);
	this->_user_list.erase(user->ft_get_user_name());
	return (0);
}



void	Channel::ft_send_all(std::string user_name, std::string buf)
{
	 std::map<std::string, User *>::iterator it = this->_user_list.begin();
	 while (it != this->_user_list.end())
	 {
		if ((*it).first != user_name)
			send((*it).second->ft_get_fd(), buf.c_str(), buf.length(), 0);
		it++;
	 }
}

void	Channel::ft_send_me(std::string user_name, std::string buf)
{
	send(this->_user_list.at(user_name)->ft_get_fd(), buf.c_str(), buf.length(), 0);
}

int	Channel::ft_privilege_user_authorization(User *user)
{
	if (this->_privilege_user_map.find(user->ft_get_user_name()) != this->_privilege_user_map.end())
		return (1);
	this->_privilege_user_map.insert(std::pair<std::string, User *>(user->ft_get_user_name(), user));
	return (0);
}

int	Channel::ft_privilege_user_delete(std::string user_name)
{
	if (this->_privilege_user_map.find(user_name) == this->_privilege_user_map.end())
		return (1);
	this->_privilege_user_map.erase(user_name);
	if (this->_privilege_user_map.size() == 0 && this->_user_list.size() != 0)
		this->ft_privilege_user_authorization(this->_user_list.at(0));
	return (0);
}