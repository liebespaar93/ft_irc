#include "User.hpp"

User::User(){}
User::User(const User &ref) { (void)ref; }
User &User::operator=(const User &ref)
{
	this->_fd = ref._fd;
	return *this;
}
User::User(int fd) : _fd(fd)
				 , _user_name("")
				 , _nick_name("")
				 , _IP("")
				 , _pass(false)
				 , _login(false)
				 , _wellcome(false)
{	
}
User::~User()
{
	this->ft_quit();
}

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

Channel *User::ft_get_channel(const std::string &channel_name)
{
	if (this->_channel_list.find(channel_name) == this->_channel_list.end())
		return (NULL);
	return (this->_channel_list.at(channel_name));
}

void User::ft_quit()
{
	while (this->_channel_list.begin() != this->_channel_list.end())
	{
		this->_channel_list.begin()->second->ft_channel_leave_user(this);
	}
}

const int &User::ft_get_fd() { return this->_fd; }
const std::string User::ft_get_user_name() { return this->_user_name; }
const std::string User::ft_get_nick_name() { return this->_nick_name; }
const std::string User::ft_get_real_name() { return this->_real_name; }
const std::map<std::string, Channel *> User::ft_get_channel_list() { return this->_channel_list; }
size_t User::ft_get_channel_size() { return this->_channel_list.size(); }
bool User::ft_get_pass() { return this->_pass; }
bool User::ft_get_login() { return this->_login; }
bool User::ft_get_wellcome() { return this->_wellcome; }
std::string User::ft_get_IP() { return this->_IP; }
std::string User::ft_get_info() { return ":" + this->_nick_name + "!~" + this->_user_name + "@" + this->_IP; }
void User::ft_set_nick_name(std::string nick_name) { this->_nick_name = nick_name; }
void User::ft_set_user_name(std::string user_name) { this->_user_name = user_name; }
void User::ft_set_real_name(std::string real_name) { this->_real_name = real_name; }
void User::ft_set_IP(std::string IP) { this->_IP = IP; }
void User::ft_set_pass() { this->_pass = true; }
void User::ft_set_login() { this->_login = true; }
void User::ft_set_wellcome() { this->_wellcome = true; }
