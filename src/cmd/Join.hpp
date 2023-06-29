#ifndef JOIN_HPP
#define JOIN_HPP

#include "Cmd.hpp"
#include "Utile.hpp"

class Join : public Cmd
{
private:
	/* data */
	Join(const Join &ref) { (void)ref; };

	Join &operator=(const Join &ref)
	{
		(void)ref;
		return *this;
	};

public:
	Join() { this->_cmd = "JOIN"; };
	~Join(){};

	void ft_recv(std::vector<std::string> msg)
	{
		if (!this->_user->ft_get_login())
			return;
		Channel *channel_info;
		std::map<std::__1::string, User *> channel_user_list;
		std::vector<std::string> channel;
		std::vector<std::string> password;
		int code;

		if (msg.size() == 1)
		{
			this->_send_msg = ERR_NEEDMOREPARAMS(this->_client, this->_cmd);
			this->ft_send();
			return;
		}
		if (msg.size() > 1)
			channel = split(msg[1], ",");
		if (msg.size() > 2)
			password = split(msg[2], ",");
		size_t i = 0;
		while (i < channel.size())
		{
			if (password.size() > i)
				code = this->_server->ft_join_channel(this->_user, channel.at(i), password.at(i), this->_symbol);
			else
				code = this->_server->ft_join_channel(this->_user, channel.at(i), this->_symbol);
			if (code == 471)
			{
				this->ft_set_client("471");
				this->_send_msg = ERR_CHANNELISFULL(this->_client, channel.at(i));
				this->ft_send();
			}
			else if (code == 475)
			{
				this->ft_set_client("475");
				this->_send_msg = ERR_BADCHANNELKEY(this->_client, channel.at(i));
				this->ft_send();
			}
			else if (code == 473)
			{
				this->ft_set_client("473");
				this->_send_msg = ERR_INVITEONLYCHAN(this->_client, channel.at(i));
				this->ft_send();
			}
			else if (code == 0)
			{
				channel_info = this->_server->ft_get_channel(channel[i]);
				channel_user_list = channel_info->ft_get_user_list();
				this->_prefix = channel_info->ft_privilege_has_user(this->_user->ft_get_user_name()) ? "@" : "";
				this->_send_msg = this->_user->ft_get_info() + " " + this->_cmd + " :" + channel[i];
				this->ft_send();

				this->ft_set_client("353");
				this->_prefix = channel_info->ft_privilege_has_user(this->_user->ft_get_user_name()) ? "@" : "";
				this->_send_msg = RPL_NAMREPLY(this->_client, this->_symbol, channel.at(i), this->_prefix, this->_user->ft_get_nick_name());
				for (std::map<std::__1::string, User *>::iterator it = channel_user_list.begin(); it != channel_user_list.end(); it++)
				{
					if (this->_user->ft_get_user_name() != it->first)
					{
						this->_prefix = channel_info->ft_privilege_has_user(it->first) ? "@" : "";
						this->_send_msg += " " + this->_prefix + this->_server->ft_get_user(it->first)->ft_get_nick_name();
					}
				}
				this->ft_send();
				this->ft_set_client("366");
				this->_send_msg = RPL_ENDOFNAMES(this->_client, this->_channel);
				this->ft_send();
				for (std::map<std::__1::string, User *>::iterator it = channel_user_list.begin(); it != channel_user_list.end(); it++)
				{
					if (this->_user->ft_get_user_name() != it->first)
					{
						this->_send_msg = this->_user->ft_get_info() + " " + this->_cmd + " :" + channel[i];
						this->ft_send(it->second->ft_get_fd());
					}
				}
				if (this->_server->ft_get_channel(channel.at(i))->ft_get_topic() != "")
				{
					this->ft_set_client("332");
					this->_send_msg = RPL_TOPIC(this->_client, msg[1], this->_user->ft_get_channel(msg[1])->ft_get_topic());
					this->ft_send();
					this->ft_set_client("333");
					this->_send_msg = RPL_TOPICWHOTIME(this->_client, msg[1],
													this->_server->ft_get_channel(msg[1])->ft_get_topic_user()->ft_get_nick_name(),
													this->_server->ft_get_channel(msg[1])->ft_get_topic_time());
				}
				if (this->_server->ft_get_channel(channel.at(i))->ft_mode_has())
				{
					this->ft_set_client("324");
					this->_send_msg = RPL_CHANNELMODEIS(this->_client, msg[1], this->_server->ft_get_channel(msg[1])->ft_mode_string());
					this->ft_send();
				}
			}
			i++;
		}
	}
};
#endif
