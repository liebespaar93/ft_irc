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
    std::map<std::string, Channel *> *_invite_map;

public:
	UserControl();
	UserControl(const UserControl& ref);
	~UserControl();

	UserControl&	operator=(const UserControl& ref);
	
	int	ft_append_user(User *user);

	User	*ft_get_user(const int &fd);
	User	*ft_get_user(const std::string &user_name);
	UserControl	&ft_get_user_control_class() { return (*this); }


	void ft_invite_channel(std::string user_name, Channel *user_channel);

};

#endif
