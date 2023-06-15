#ifndef JOIN_HPP
# define JOIN_HPP

#include "Cmd.hpp"
#include "Utile.hpp"

class Join: public Cmd
{
private:
	/* data */
	Join(const Join& ref) {};

	Join&	operator=(const Join& ref) {return *this;};
public:
	Join() { this->_cmd = "JOIN"; };
	~Join(){};

	void ft_recv(std::vector<std::string> msg)
	{
		std::vector<std::string> channel;
		std::vector<std::string> password;
		int code;

		if (msg.size() == 1)
		{
			this->_send_msg = ERR_NEEDMOREPARAMS(this->_client,this->_cmd);
			this->ft_send();
			return;
		}
		if (msg.size() > 1)
			channel = split(msg[1], ",");
		if (msg.size() > 2)
			password = split(msg[2], ",");
		
		int i = 0;
		while (i < channel.size())
		{
			if (password.size() > i)
				code = this->_server->ft_join_channel(this->_user, channel.at(i), password.at(i));
			else
				code = this->_server->ft_join_channel(this->_user, channel.at(i));
			if (code == 471)
			{
				this->_send_msg = ERR_CHANNELISFULL(this->_client, this->_channel);
				this->ft_send();
			}
			else if (code == 475)
			{
				this->_send_msg = ERR_BADCHANNELKEY(this->_client, this->_channel);
				this->ft_send();
			}
			else if (code == 0 )
			{
				this->_send_msg = this->_client + " " + this->_cmd + " :" + this->_channel;
				this->ft_send();
				this->_send_msg = RPL_NAMREPLY(this->_client, this->_symbol, this->_channel, this->_prefix, this->_user->ft_get_nick_name());
				this->ft_send();
				this->_send_msg = RPL_ENDOFNAMES(this->_client, this->_channel);
				this->ft_send();
			}
		}
		
	}
};
// Request: JOIN #channel_name
// Response: :nick_name!~myname@freenode-pig.su5.hqs74b.IP JOIN :#channel_name
// Response: :*.freenode.net 353 nick_name = #channel_name :@nick_name
// Response: :*.freenode.net 366 nick_name #ar :End of /NAMES list.
// Request: MODE #channel_name +sn
// Response: :nick_name!~myname@freenode-pig.su5.hqs74b.IP MODE #channel_name :+s

#endif
