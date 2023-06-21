#ifndef TOPIC_HPP
#define TOPIC_HPP

#include "Cmd.hpp"

class Topic : public Cmd
{
private:
	/* data */
	Topic(const Topic &ref){};
	Topic &operator=(const Topic &ref) { return *this; };

public:
	Topic() { this->_cmd = "TOPIC"; };
	~Topic(){};

	void ft_recv(std::vector<std::string> msg)
	{
		if (msg.size() == 1)
		{
			this->ft_set_client("461");
			this->_send_msg = ERR_NEEDMOREPARAMS(this->_client, this->_cmd);
			this->ft_send();
			return;
		}
		if (!this->_server->ft_get_channel(msg[1]))
		{
			this->ft_set_client("403");
			this->_send_msg = ERR_NOSUCHCHANNEL(this->_client, msg[1]);
			this->ft_send();
			return;
		}
		if (!this->_user->ft_get_channel(msg[1]))
		{
			this->ft_set_client("442");
			this->_send_msg = ERR_NOTONCHANNEL(this->_client, msg[1]);
			this->ft_send();
			return;
		}
		if (msg.size() == 2)
		{
			// Response: :*.freenode.net 331 gye #test00 :No topic is set.
			if (this->_user->ft_get_channel(msg[1])->ft_get_topic() == "")
			{
				this->ft_set_client("331");
				this->_send_msg = RPL_NOTOPIC(this->_client, msg[1]);
				this->ft_send();
				return;
			}
			this->ft_set_client("332");
			this->_send_msg = RPL_TOPIC(this->_client, msg[1], this->_user->ft_get_channel(msg[1])->ft_get_topic());
			this->ft_send();
			this->ft_set_client("333");
			this->_send_msg = RPL_TOPICWHOTIME(this->_client, msg[1],
											   this->_server->ft_get_channel(msg[1])->ft_get_topic_user()->ft_get_nick_name(),
											   this->_server->ft_get_channel(msg[1])->ft_get_topic_time());
			this->ft_send();
			return;
		}
		// mode의 문제인지 topic의 문제인지 체크 mode -t했을때 일반유저도 변경이 가능해야하는데 변경 불가
		if (!this->_server->ft_get_channel(msg[1])->ft_get_restrict() || !this->_user->ft_get_channel(msg[1])->ft_privilege_has_user(this->_user->ft_get_user_name()))
		{
			// Response: :*.freenode.net 482 gyeongjukim #test00 :You do not have access to change the topic on this channel
			// ERR_CHANOPRIVSNEEDED
			this->ft_set_client("482");
			this->_send_msg = ERR_CHANOPRIVSNEEDED(this->_client, msg[1]);
			this->ft_send();
			return;
		}
		// Response: :gyeo!~gg@127.0.0.1  #test00 ::this is a test
		// Response: :gye!~gyeokim@freenode-n68.49c.2i380a.IP TOPIC #test00 :this is a test
		std::string topic_msg = "";
		for (int i = 2; i < msg.size(); i++)
			topic_msg += msg[i] + " ";
		this->_user->ft_get_channel(msg[1])->ft_set_topic(topic_msg);
		this->_user->ft_get_channel(msg[1])->ft_set_topic_user(this->_user);
		this->_user->ft_get_channel(msg[1])->ft_set_topic_time(this->_timestr);
		this->_send_msg = this->_user->ft_get_info() + " " + this->_cmd + " " + msg[1] + " :" +
						  this->_user->ft_get_channel(msg[1])->ft_get_topic();
		this->ft_send();
	}
};

#endif
