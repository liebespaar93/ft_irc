#ifndef TOPIC_HPP
#define TOPIC_HPP

#include "Cmd.hpp"

class Topic : public Cmd
{
private:
	/* data */

public:
	Topic();
	Topic(const Topic &ref);
	~Topic();

	Topic &operator=(const Topic &ref);

	void ft_recv(std::vector<std::string> msg)
	{
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
			else
			{
				this->_send_msg = this->_user->ft_get_channel(msg[1])->ft_get_topic();
				this->ft_send();
				return;
			}
		}
		else if (msg.size() > 2)
		{
			if (!this->_user->ft_get_channel(msg[1])->ft_privilege_has_user(this->_user->ft_get_user_name()))
			{
				// Response: :*.freenode.net 482 gyeongjukim #test00 :You do not have access to change the topic on this channel
				// ERR_CHANOPRIVSNEEDED
				this->ft_set_client("482");
				this->_send_msg = ERR_CHANOPRIVSNEEDED(this->_client, msg[1]);
				this->ft_send();
				return;
			}
			else
			{
				// Response: :gye!~gyeokim@freenode-n68.49c.2i380a.IP TOPIC #test00 :this is a test
				this->_user->ft_get_channel(msg[1])->ft_set_topic(msg[3]);
				this->_send_msg = ":" + this->_user->ft_get_nick_name() + this->_user->ft_get_user_name() + "@" +
								  this->_user->ft_get_IP() + " " + this->_cmd + " " + msg[1] + " :" +
								  this->_user->ft_get_channel(msg[1])->ft_get_topic();
				this->ft_send();
				return;
			}
		}
	}
};

#endif
