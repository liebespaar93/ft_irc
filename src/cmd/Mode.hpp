#ifndef MODE_HPP
#define MODE_HPP

#include "Cmd.hpp"

class Mode : public Cmd
{
private:
	/* data */
	Mode(const Mode &ref) { (void)ref; };
	Mode &operator=(const Mode &ref)
	{
		(void)ref;
		return *this;
	};
	bool _sign;
	int _param;
	int _msg_size;
	std::vector<std::string> _response_arr;

public:
	Mode()
	{
		this->_cmd = "MODE";
	};
	~Mode(){};

	void ft_recv(std::vector<std::string> msg)
	{
		if (!this->_user->ft_get_login())
			return;
		if (msg.size() <= 2)
		{
			this->ft_set_client("461");
			this->_send_msg = ERR_NEEDMOREPARAMS(this->_client, this->_cmd);
			this->ft_append_msg();
			return;
		}
		if (!this->_user->ft_get_channel(msg[1]))
		{
			this->ft_set_client("401");
			this->_send_msg = ERR_NOSUCHNICK(this->_client, this->_user->ft_get_nick_name());
			this->ft_append_msg();
			return;
		}
		if (!this->_user->ft_get_channel(msg[1])->ft_privilege_has_user(this->_user->ft_get_user_name()))
		{
			this->ft_set_client("482");
			this->_send_msg = ERR_CHANOPRIVSNEEDED(this->_client, msg[1]);
			this->ft_append_msg();
			return;
		}
		this->_msg_size = msg.size();
		this->_channel = msg[1];
		this->_response_arr.clear();
		this->_response_arr.push_back("");
		this->_sign = true;
		this->_param = 3;

		if (2 < msg.size())
		{
			size_t k = 0;

			while (k < msg[2].size())
			{
				if (msg[2][k] == '+')
				{
					this->_sign = true;
					if (this->_response_arr[0].size() &&
						this->_response_arr[0][this->_response_arr[0].size() - 1] == '-')
					{
						this->_response_arr[0][this->_response_arr[0].size() - 1] = '+';
					}
					else
					{
						this->_response_arr[0] += "+";
					}
				}
				else if (msg[2][k] == '-')
				{
					this->_sign = false;
					if (this->_response_arr[0].size() &&
						this->_response_arr[0][this->_response_arr[0].size() - 1] == '+')
					{
						this->_response_arr[0][this->_response_arr[0].size() - 1] = '-';
					}
					else
					{
						this->_response_arr[0] += "-";
					}
				}
				else
				{
					switch (msg[2][k])
					{
					case 'i': // invite-only
						ft_invite_only();
						break;
					case 't': // only operator can modify topic
						ft_topic_restrict();
						break;
					case 'k': // key set
						ft_key_set(msg);
						this->_param++;
						break;
					case 'o': // give the privilage of operator
						ft_give_auth(msg);
						this->_param++;
						break;
					case 'l': // limit the number of members in channel
						ft_set_limit(msg);
						break;
					default:
						this->ft_set_client("472");
						this->_send_msg = ERR_UNKNOWNMODE(this->_client, msg[2][k]);
						this->ft_append_msg();
						break;
					}
				}
				k++;
			}
		}
		this->_send_msg = this->_user->ft_get_info() + " " + this->_cmd + " " + this->_channel + " ";
		while (this->_response_arr[0].size())
		{
			if (this->_response_arr[0][this->_response_arr[0].size() - 1] == '-' ||
				this->_response_arr[0][this->_response_arr[0].size() - 1] == '+')
				this->_response_arr[0].pop_back();
			else
				break;
		}
		if (!this->_response_arr[0].size())
			return;
		for (size_t i = 0; i < this->_response_arr.size(); i++)
		{
			if (i + 1 == this->_response_arr.size())
				this->_send_msg += ":";
			this->_send_msg += this->_response_arr[i] + " ";
		}
		this->ft_append_msg();
		this->_server->ft_send_msg_to_channel(this->_user, this->_user->ft_get_channel(this->_channel), this->_send_msg);
	}

	void ft_invite_only()
	{
		if (this->_sign)
		{
			if (!this->_user->ft_get_channel(this->_channel)->ft_get_invite())
			{
				this->_user->ft_get_channel(this->_channel)->ft_set_invite(true);
				this->_response_arr[0] += "i";
			}
		}
		else
		{
			if (this->_user->ft_get_channel(this->_channel)->ft_get_invite())
			{
				this->_user->ft_get_channel(this->_channel)->ft_set_invite(false);
				this->_response_arr[0] += "i";
			}
		}
	}

	void ft_topic_restrict()
	{
		if (this->_sign)
		{
			if (!this->_user->ft_get_channel(this->_channel)->ft_get_restrict())
			{
				this->_user->ft_get_channel(this->_channel)->ft_set_restrict(true);
				this->_response_arr[0] += "t";
			}
		}
		else
		{
			if (this->_user->ft_get_channel(this->_channel)->ft_get_restrict())
			{
				this->_user->ft_get_channel(this->_channel)->ft_set_restrict(false);
				this->_response_arr[0] += "t";
			}
		}
	}

	void ft_key_set(std::vector<std::string> msg)
	{
		if (!(this->_param < this->_msg_size))
		{
			this->ft_set_client("461");
			this->_send_msg = ERR_NEEDMOREPARAMS(this->_client, this->_cmd);
			this->ft_append_msg();
			return;
		}
		if (this->_sign)
		{
			if (this->_user->ft_get_channel(this->_channel)->ft_get_has_password())
				return;
			this->_user->ft_get_channel(this->_channel)->ft_set_password(msg[this->_param]);
			this->_user->ft_get_channel(this->_channel)->ft_set_has_password(true);
			this->_response_arr[0] += "k";
			this->_response_arr.push_back(msg[this->_param]);
		}
		else
		{
			if (!this->_user->ft_get_channel(this->_channel)->ft_get_has_password())
				return;
			if (this->_user->ft_get_channel(this->_channel)->ft_get_password().compare(msg[this->_param]))
			{
				this->ft_set_client("800");
				this->_send_msg = this->_client + " error: you put wrong password";
				this->ft_append_msg();
				return;
			}
			this->_user->ft_get_channel(this->_channel)->ft_set_password("");
			this->_user->ft_get_channel(this->_channel)->ft_set_has_password(false);
			this->_response_arr[0] += "k";
			this->_response_arr.push_back(msg[this->_param]);
		}
	}

	void ft_give_auth(std::vector<std::string> msg)
	{
		if (!(this->_param < this->_msg_size))
		{
			this->ft_set_client("461");
			this->_send_msg = ERR_NEEDMOREPARAMS(this->_client, this->_cmd);
			this->ft_append_msg();
			return;
		}
		if (!this->_server->ft_get_nick(msg[this->_param]))
		{
			this->ft_set_client("441");
			this->_send_msg = ERR_USERNOTINCHANNEL(this->_client, msg[this->_param], msg[1]);
			this->ft_append_msg();
			return;
		}
		if (!this->_server->ft_get_nick(msg[this->_param])->ft_get_channel(this->_channel))
		{
			this->ft_set_client("401");
			this->_send_msg = ERR_NOSUCHNICK(this->_client, this->_user->ft_get_nick_name());
			this->ft_append_msg();
			return;
		}
		if (this->_sign)
		{
			if (!this->_user->ft_get_channel(this->_channel)->ft_privilege_has_user(this->_server->ft_get_nick(msg[this->_param])->ft_get_user_name()))
			{
				this->_user->ft_get_channel(this->_channel)->ft_privilege_user_authorization(this->_server->ft_get_nick(msg[this->_param]));
				this->_response_arr[0] += "o";
				this->_response_arr.push_back(msg[this->_param]);
			}
		}
		else
		{
			if (this->_user->ft_get_channel(this->_channel)->ft_privilege_has_user(this->_server->ft_get_nick(msg[this->_param])->ft_get_user_name()))
			{
				this->_user->ft_get_channel(this->_channel)->ft_privilege_user_delete(this->_server->ft_get_nick(msg[this->_param])->ft_get_user_name());
				this->_response_arr[0] += "o";
				this->_response_arr.push_back(msg[this->_param]);
			}
		}
	}

	void ft_set_limit(std::vector<std::string> msg)
	{
		if (msg[this->_param].find_first_not_of("0123456789") != std::string::npos)
		{
			this->ft_set_client("696");
			this->_send_msg = ERR_INVALIDMODEPARAM(this->_client, this->_channel, "l", msg[this->_param], "wrong type of the parameter");
			this->ft_append_msg();
			return;
		}
		if (this->_sign)
		{
			this->_user->ft_get_channel(this->_channel)->ft_set_limit(atoi(msg[this->_param].c_str()));
			this->_response_arr[0] += "l";
			this->_response_arr.push_back(msg[this->_param]);
		}
		else
		{
			if (this->_user->ft_get_channel(this->_channel)->ft_get_limit())
			{
				this->_user->ft_get_channel(this->_channel)->ft_set_limit(0);
				this->_response_arr[0] += "l";
			}
		}
	}
};

#endif
