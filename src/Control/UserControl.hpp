#ifndef USERCONTROL_HPP
# define USERCONTROL_HPP

#include <map>
#include <string>
#include <utility>

#include "User.hpp"
#include "Channel.hpp"

class UserControl
{
private:
	/* data */
	
	std::map<const int, User *> *_fd_map;
	std::map<const std::string, int> *_name_map;
    std::map<std::string, int> *_nick_map;

public:
	UserControl();
	UserControl(const UserControl& ref);
	~UserControl();

	UserControl&	operator=(const UserControl& ref);
	
	User	*ft_get_user(const int fd);
	User	*ft_get_user(const std::string user_name);
	User	*ft_get_nick(const std::string nick_name);
	UserControl	&ft_get_user_control_class() { return (*this); }

	int	ft_append_user(User *user);
	int	ft_delete_user(User *user);
	int	ft_append_user_name(const std::string user_name, User *user);
	int	ft_delete_user_name(const std::string user_name);
	int	ft_append_nick_name(const std::string nick_name, User *user);
	int	ft_delete_nick_name(const std::string nick_name);
};

#endif
