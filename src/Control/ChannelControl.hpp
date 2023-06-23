#ifndef CHANNELCONTROL_HPP
#define CHANNELCONTROL_HPP

#include <map>
#include <string>
#include "Channel.hpp"

class ChannelControl
{
private:
    /* data */
    std::map<const std::string, Channel *> *_channel_map;

    void ft_append_channel(Channel *channel);

public:
    ChannelControl();
    ChannelControl(const ChannelControl &ref);
    ~ChannelControl();

    ChannelControl &operator=(const ChannelControl &ref);

    ChannelControl &ft_get_channel_control_class() { return (*this); }
    Channel *ft_get_channel(const std::string &channel_name);
    std::map<const std::string, Channel *> *ft_get_channel_map() { return this->_channel_map; }

    int ft_join_channel(User *user, std::string channel_name, std::string &symbol);
    int ft_join_channel(User *user, std::string channel_name, std::string password, std::string &symbol);
    int ft_leave_channel(User *user, std::string channel_name);
    int ft_send_msg_to_channel(User *user, Channel *channel, const std::string &msg);
    int ft_send_all_in_channels(User *user, const std::string &msg);
};

#endif
