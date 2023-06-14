#include "Channel.hpp"

bool	Channel::ft_channel_join_user(User *user)
{
	this->_user_list.insert( std::pair<std::string, User *>(user->ft_get_user_name(), user));
	return (true);
}


void	Channel::ft_channel_leave_user(User *user)
{
	std::map<std::string, User *>::iterator it = this->_user_list.find(user->ft_get_user_name());
	if (it != this->_user_list.end())
		this->_user_list.erase(user->ft_get_user_name());
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