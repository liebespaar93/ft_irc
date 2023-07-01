#ifndef TOPIC_HPP
#define TOPIC_HPP

#include "Cmd.hpp"

class Topic : public Cmd
{
private:
	/* data */
	Topic(const Topic &ref) { (void)ref; };
	Topic &operator=(const Topic &ref)
	{
		(void)ref;
		return *this;
	};

public:
	Topic() { this->_cmd = "TOPIC"; };
	~Topic(){};

	void ft_recv(std::vector<std::string> msg)
	{
		if (!this->_user->ft_get_login())
			return;
		if (msg.size() == 1)
		{
			this->ft_set_client("461");
			this->_send_msg = ERR_NEEDMOREPARAMS(this->_client, this->_cmd);
			this->ft_append_msg();
			return;
		}
		if (!this->_server->ft_get_channel(msg[1]))
		{
			this->ft_set_client("403");
			this->_send_msg = ERR_NOSUCHCHANNEL(this->_client, msg[1]);
			this->ft_append_msg();
			return;
		}
		if (!this->_user->ft_get_channel(msg[1]))
		{
			this->ft_set_client("442");
			this->_send_msg = ERR_NOTONCHANNEL(this->_client, msg[1]);
			this->ft_append_msg();
			return;
		}
		if (msg.size() == 2)
		{
			if (this->_user->ft_get_channel(msg[1])->ft_get_topic() == "")
			{
				this->ft_set_client("331");
				this->_send_msg = RPL_NOTOPIC(this->_client, msg[1]);
				this->ft_append_msg();
				return;
			}
			this->ft_set_client("332");
			this->_send_msg = RPL_TOPIC(this->_client, msg[1], this->_user->ft_get_channel(msg[1])->ft_get_topic());
			this->ft_append_msg();
			this->ft_set_client("333");
			this->_send_msg = RPL_TOPICWHOTIME(this->_client, msg[1],
											   this->_server->ft_get_channel(msg[1])->ft_get_topic_user()->ft_get_nick_name(),
											   this->_server->ft_get_channel(msg[1])->ft_get_topic_time());
			this->ft_append_msg();
			return;
		}
		if (this->_server->ft_get_channel(msg[1])->ft_get_restrict() && !this->_user->ft_get_channel(msg[1])->ft_privilege_has_user(this->_user->ft_get_user_name()))
		{
			this->ft_set_client("482");
			this->_send_msg = ERR_CHANOPRIVSNEEDED(this->_client, msg[1]);
			this->ft_append_msg();
			return;
		}
		std::string topic_msg = msg[2];
		if (msg[2].at(0) == ':')
			topic_msg = msg[2].substr(1, msg[2].size());
		if (3 < msg.size())
		{
			topic_msg = msg[2].substr(1, msg[2].size());
			for (size_t i = 3; i < msg.size(); i++)
				topic_msg += " " + msg[i];
		}
		this->_user->ft_get_channel(msg[1])->ft_set_topic(topic_msg);
		this->_user->ft_get_channel(msg[1])->ft_set_topic_user(this->_user);
		this->_user->ft_get_channel(msg[1])->ft_set_topic_time(this->_timestr);
		this->_send_msg = this->_user->ft_get_info() + " " + this->_cmd + " " + msg[1] + " :" +
						  this->_user->ft_get_channel(msg[1])->ft_get_topic();
		this->_server->ft_send_msg_to_channel(this->_user, this->_user->ft_get_channel(msg[1]), this->_send_msg);
		this->ft_append_msg();
	}
};

#endif
