
#include "User.hpp"


void User::ft_append_channel(Channel *channel)
{
	this->_channel_list.insert(
		std::pair<std::string, Channel *>(channel->ft_get_name(), channel));
}

void User::ft_delete_channel(std::string channel_name)
{
	if (this->_channel_list.find(channel_name) != this->_channel_list.end())
	{
		this->_channel_list.erase(channel_name);
	}
}
