#include <iostream>
#include <iomanip>

#include "UserControl.hpp"


UserControl::UserControl()
{
	this->_fd_map = new std::map<const int, User *>;
	this->_name_map = new std::map<const std::string, int>;
	this->_invite_map = new std::map<std::string, Channel *>;
	this->_nick_map = new std::map<std::string, int>;
	std::cout << std::setw(15) << "[UserControl] " << "create!!" << std::endl;
}

UserControl::UserControl(const UserControl& ref)
{
	*this=ref;
	std::cout << std::setw(15) << "[UserControl] " << "copy!!" << std::endl;
}

UserControl::~UserControl()
{
	this->_fd_map->clear();
	this->_name_map->clear();
	this->_invite_map->clear();
	this->_nick_map->clear();
	/// leak 확인
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
	return (0);
}


User   *UserControl::ft_get_user(const int fd)
{
	if (this->_fd_map->find(fd) == this->_fd_map->end())
		return (NULL);
	return (this->_fd_map->at(fd));
}

User	*UserControl::ft_get_user(const std::string user_name)
{
	if (this->_name_map->find(user_name) == this->_name_map->end())
		return (NULL);
	return (this->ft_get_user(this->_name_map->at(user_name)));
}

User	*UserControl::ft_get_nick(const std::string nick_name)
{
	if (this->_nick_map->find(nick_name) == this->_nick_map->end())
		return (NULL);
	return (this->ft_get_user(this->_nick_map->at(nick_name)));
}


int	UserControl::ft_append_nick_name(const std::string nick_name, User *user)
{

	if (this->_nick_map->find(nick_name) != this->_nick_map->end())
		return (433); // ERR_NICKNAMEINUSE
	this->ft_delete_nick_name(user->ft_get_nick_name());
	this->_nick_map->insert(std::pair<std::string, int>(nick_name, user->ft_get_fd()));
	return (0);
}

int UserControl::ft_delete_nick_name(const std::string nick_name)
{
	if (this->_nick_map->find(nick_name) == this->_nick_map->end())
		return (1);
	this->_nick_map->erase(nick_name);
	return (0);
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
