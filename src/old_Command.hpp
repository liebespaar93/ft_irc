#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <iostream>
#include <string>
#include <map>

#include "User.hpp"
#include "Server.hpp"
#include "UserControl.hpp"
#include "Color.hpp"

class Command : public UserControl
{
private:
	
public:

	int ft_cmd_list(std::string input, User *user, std::map<std::string, Channel *> &channel_list)
	{

		std::string channel_name;
		std::map<std::string, User *> user_list;
		std::string buf = "";

		if (input.size() == input.find_first_not_of(" \f\n\r\t\v"))
		{
			buf += "<< channel list >> \n";
			for (std::map<std::string, Channel *>::iterator it = channel_list.begin(); it != channel_list.end(); it++)
				buf += FG_LYELLOW + it->first + NO_COLOR + "\n";
			buf += "=============================\n";
			send(user->ft_get_fd(), buf.c_str(), buf.size(), 0);
			return (0);
		}
		if (input[0] != ' ')
			return (-1);
		input = input.substr(input.find_first_of(" \f\n\r\t\v"));
		if (input.compare(0, 3, "-c "))
			return (-1);
		input = input.substr(input.find_first_not_of(" \f\n\r\t\v"));
		channel_name = input.substr(0, input.find_first_of(" \f\n\r\t\v"));
		input = input.substr(input.find_first_of(" \f\n\r\t\v"));
		input = input.substr(input.find_first_not_of(" \f\n\r\t\v"));
		if (input.size() != 0)
			return (-1);
		if (channel_list.find(channel_name) == channel_list.end())
			return (-2); // no such channel
		user_list = channel_list[channel_name]->ft_get_user_list();

		buf += "<< " + channel_name + " user list >> \n";
		for (std::map<std::string, User *>::iterator it = user_list.begin(); it != user_list.end(); it++)
			buf += FG_CYAN + it->second->ft_get_user_name() + NO_COLOR +"\n";
		buf += "=============================\n";
		send(user->ft_get_fd(), buf.c_str(), buf.size(), 0);
		return (0);
	}

	int ft_cmd_join(std::string input, User *user, std::map<std::string, Channel *> &channel_list)
	{
		std::string buf = "";
		std::string channel_name;

		if (input.size() == input.find_first_not_of(" \f\n\r\t\v") && input[0] != ' ')
			return (-1);
		input = input.substr(input.find_first_of(" \f\n\r\t\v"));

		
		channel_name = input.substr(0, input.find_first_of(" \f\n\r\t\v"));
		input = input.substr(input.find_first_of(" \f\n\r\t\v"));
		input = input.substr(input.find_first_not_of(" \f\n\r\t\v"));
		if (input.size() != 0)
			return (-1);
		
		

		if (channel_list.find(channel_name) == channel_list.end())
		{
			//create
			channel_list.insert(channel_name, channel_list )
		}
		else
		{
			//join
		}
	}

	int ft_cmd_help(int user_fd)
	{
		std::string buf = "";
	
		buf += "--------------------------------------------------- HELP ---------------------------------------------------\n";
		buf += "[Usage for Sending Private messages]\n";
		buf += "\"@user_name message\"\n";
		buf += "[Command List in the Public Channel or General]\n";
		buf += "-  JOIN  - \"/join channel_name\" : join a channel or create a channel if not exist.\n";
		buf += "-  LIST  - \"/list [empty] or [-c channel_name]\" : list channel if there is an option or users in the channel.\n";
		buf += "-  HELP  - \"/help\" : display HELP.\n";
		buf += "[Command List in a Channel]\n";
		buf += "-  KICK  - \"/kick user_name\" : kick the user out of the channel.\n";
		buf += "- INVITE - \"/invite user_name\" : invite the user.\n";
		buf += "-  TOPIC - \"/topic topic_content(or empty)\" : change the topic as topic_content or view the topic if empty.\n";
		buf += "-  MODE  - \"/mode options(i, t, k, o, l)\"\n";
		buf += "           \"/mode i\" : set/remove invite-only channel.\n";
		buf += "           \"/mode t\" : set/remove the restrictions of the TOPIC command to channel operators.\n";
		buf += "           \"/mode k (-set password) or (-rm)\" : set/remove the channel key.\n";
		buf += "           \"/mode o user_name\" : give/take channel operator privilege to user_name.\n";
		buf += "           \"/mode l number\" : set/remove the user limit to channel if number is zero, the limitation is off.\n";
		buf += "------------------------------------------------------------------------------------------------------------\n";
		send(user_fd, buf.c_str(), buf.size(), 0);
		return (1);
	}

	void ft_kick(std::map<std::string, Channel *> list, const std::string &channel, const std::string &user)
	{
		// kick user out of the channel
		std::map<std::string, Channel *>::iterator it = list.find(channel);
		if (it == list.end())
		{
			std::cerr << "no channel" << std::endl;
			return ;
		}

		std::map<std::string, User *> user_it = (*it).second->ft_get_user_list();
		if (user_it.find(user) == user_it.end())
		{
			std::cerr<< "There is no such user." << std::endl;
			return ;
		}
		user_it.erase(user);
		std::cout << "Kicked " << user << "." << std::endl;
	}

	void ft_invite(User *invite_user)
	{
		// invite user in the public channel to this channel
		// the user can deny
		// what if the user in another channel?
		if (!invite_user)
		{
			std::cout << "There is no such user." << std::endl;
			return ;
		}

		invite_user->ft_get_channel_name();
		 

		std::string msg = 
			"you got an invitation from a channel. If you enter '/Y', you leave the channel and join the new one \n"
			"(/Y or /N)";

		send(invite_user->ft_get_fd(), msg.c_str(), msg.length(), 0);


		// if target exists
		// invite
		// else
		

	}

	std::string ft_topic(std::map<std::string, Channel *> list, const std::string &channel, const std::string &topic)
	{
		// can change the topic of the channel
		// & view the topic
		std::map<std::string, Channel *>::iterator it = list.find(channel);
		if (it == list.end())
		{
			std::cerr << "no such channel" << std::endl;
			return ;
		}

		if (it->second->ft_get_restrict() == true)
		{
			std::cerr << "restrictions of TOPIC command has set." << std::endl;
			return ;
		}

		if (topic == "")
			// display topic
			std::cout << "The topic of this channel is " << it->second->ft_get_topic() << std::endl;
		else // change topic
		{
			it->second->ft_set_topic(topic);
			std::cout << "Topic has changed." << std::endl;
		}
	}

	std::string ft_mode(std::map<std::string, Channel *> list, const std::string &channel, std::vector<std::string> option, const std::string &arg)
	{
		std::map<std::string, Channel *>::iterator it = list.find(channel);
		if (it == list.end())
		{
			std::cerr << "no such channel" << std::endl;
			return ;
		}
		if (option.size() == 0)
		{
			this->ft_help();
			return ;
		}
		// mode
		// option
		// i
		if (option.at(0) == "i")
		{
			if (it->second->ft_get_invite() == true)
				it->second->ft_set_invite(false);
			else
				it->second->ft_set_invite(true);
		}
		// t
		else if (option.at(0) == "t")
		{
			if (it->second->ft_get_restrict() == true)
				it->second->ft_set_restrict(false);
			else
				it->second->ft_set_restrict(true);
		}
		// k
		else if (option.at(0) == "k")
		{
			if (option.size() != 2)
			{
				this->ft_help();
				return ;
			}
			if (option.at(1) == "-set")
			{
				if (it->second->ft_get_has_password() == true)
				{
					std::cout << "Already set" << std::endl;
					return ;
				}
				else
				{
					it->second->ft_set_has_password(true);
					it->second->ft_set_password(arg);
					std::cout << "Channel key has set" << std::endl;
				}
			}
			else if (option.at(1) == "-rm")
			{
				if (it->second->ft_get_has_password() == true)
				{
					it->second->ft_set_has_password(false);
					it->second->ft_set_password("");
				}
				else
				{
					std::cout << "Already unset" << std::endl;
				}
			}
		}
		// o
		else if (option.at(0) == "o")
		{
			User *tmp = it->second->ft_get_user(arg);
			if (this->ft_isOp(tmp))
			{
				std::cout << tmp->ft_get_user_name() << " is already an operator." << std::endl;
			}
			else
			{
				tmp->ft_set_auth(User::OPERATOR);
			}
		}
		// l
		else if (option.at(0) == "l")
		{
			if (arg.find_first_not_of("0123456789") != std::string::npos)
			{
				it->second->ft_set_limit(atoi(arg.c_str()));
			}
			else
			{
				this->ft_help();
			}
		}
	}

	bool ft_isOp(User *user)
	{
		return user->ft_get_auth() <= User::OPERATOR ? true : false;
	}
};

#endif
