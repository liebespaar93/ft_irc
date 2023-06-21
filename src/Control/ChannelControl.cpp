#include <iostream>
#include <iomanip>

# include "ChannelControl.hpp"
# include "Logger.hpp"

ChannelControl::ChannelControl()
{
    this->_channel_map = new std::map<const std::string, Channel *>;

    std::cout << std::setw(15) << "[ChannelControl] " << "create!!" << std::endl;
}

ChannelControl::ChannelControl(const ChannelControl& ref)
    :_channel_map(ref._channel_map)
{
    std::cout << std::setw(15) << "[ChannelControl] " << "copy!!" << std::endl;
}

ChannelControl::~ChannelControl()
{
    std::cout << std::setw(15) << "[ChannelControl] " << "delete!!" << std::endl;
}

ChannelControl&	ChannelControl::operator=(const ChannelControl& ref)
{
    this->_channel_map = ref._channel_map;
    std::cout << std::setw(15) << "[ChannelControl] " << "operator=!!" << std::endl;
    return (*this);
}

int ChannelControl::ft_join_channel(User *user, std::string channel_name, std::string &symbol)
{
	if (this->_channel_map->find(channel_name) == this->_channel_map->end())
	{
		Channel *new_channel = new Channel(channel_name);
		new_channel->ft_channel_join_user(user);
		new_channel->ft_privilege_user_authorization(user);
		this->ft_append_channel(new_channel);
		symbol = "=";
		return (0);
	}
	symbol = "@";
	return (this->_channel_map->at(channel_name)->ft_channel_join_user(user));
}

int ChannelControl::ft_join_channel(User *user, std::string channel_name, std::string password, std::string &symbol)
{
	if (this->_channel_map->find(channel_name) == this->_channel_map->end())
	{
		Channel *new_channel = new Channel(channel_name);
		new_channel->ft_channel_join_user(user);
		new_channel->ft_privilege_user_authorization(user);
		this->ft_append_channel(new_channel);
		symbol = "=";
		return (0);
	}
	symbol = "@";
	return (this->_channel_map->at(channel_name)->ft_channel_join_user(user, password));

}

int ChannelControl::ft_leave_channel(User *user, std::string channel_name)
{
	if (this->_channel_map->find(channel_name) == this->_channel_map->end())
		return (403); // ERR_NOSUCHCHANNEL
	if (this->_channel_map->at(channel_name)->ft_channel_leave_user(user))
		return (442); // ERR_NOTONCHANNEL
	if (this->_channel_map->at(channel_name)->ft_get_user_list().size() == 0)
	{
		Channel *tmp = this->_channel_map->at(channel_name);
		this->_channel_map->erase(channel_name);
		delete tmp;
	}
	return (0);
}

void ChannelControl::ft_append_channel(Channel *channel)
{
	this->_channel_map->insert(std::pair<std::string, Channel *>(channel->ft_get_name(), channel));
}

Channel *ChannelControl::ft_get_channel(const std::string &channel_name)
{
	if (this->_channel_map->find(channel_name) == this->_channel_map->end())
		return (NULL);
	return (this->_channel_map->at(channel_name));
}
