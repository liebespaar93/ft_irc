#include <iostream>
#include <iomanip>

#include "UserControl.hpp"


UserControl::UserControl()
{
	this->_fd_map = new std::map<const int, User *>;
	this->_name_map = new std::map<const std::string, int>;
	this->_invite_map = new std::map<std::string, Channel *>;
	std::cout << std::setw(15) << "[UserControl] " << "create!!" << std::endl;
}

UserControl::UserControl(const UserControl& ref)
{
	*this=ref;
	std::cout << std::setw(15) << "[UserControl] " << "copy!!" << std::endl;
}

UserControl::~UserControl()
{
	std::cout << std::setw(15) << "[UserControl] " << "delete!!" << std::endl;
}

UserControl&	UserControl::operator=(const UserControl& ref)
{
	this->_fd_map = ref._fd_map;
	this->_name_map = ref._name_map;
	this->_invite_map = ref._invite_map;
	std::cout << std::setw(15) << "[UserControl] " << "operator=!!" << std::endl;
	return (*this);
}

int	UserControl::ft_append_user(User *user)
{
	this->_fd_map->insert( std::pair<const int, User *>(user->ft_get_fd(), user ));
	// this->_name_map->insert( std::pair<std::string, const int>( user->ft_get_user_name(), user->ft_get_fd() ));
}

User   *UserControl::ft_get_user(const int &fd)
{
	std::map<const int, User *>::iterator it = this->_fd_map->find(fd);
	if (it == this->_fd_map->end())
		return (NULL);
	return ((*it).second);
}

User	*UserControl::ft_get_user(const std::string &user_name)
{
	std::map<const std::string, int>::iterator it = this->_name_map->find(user_name);
	if (it == this->_name_map->end())
		return (NULL);
	return (this->ft_get_user((*it).second));
}



void UserControl::ft_invite_channel(std::string user_name, Channel *user_channel)
{
	User *invite_user = this->ft_get_user(user_name);
	this->_invite_map->insert(  std::pair<std::string, Channel *>(user_name, user_channel));
}



// bool	Channel::ft_channel_invite_refuse(User *user)
// {
// 	if (this->_invite_list.at(user->ft_get_user_name()));
// 	{
// 		this->_invite_list.erase(user->ft_get_user_name());
// 	}
// }
// 	if (this->_invite_list.at(user->ft_get_user_name()));
// 	{
// 		this->_invite_list.erase(user->ft_get_user_name());
// 	}
    // ft_channel_invite_accept() = leave & join