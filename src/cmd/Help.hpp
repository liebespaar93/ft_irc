#ifndef HELP_HPP
#define HELP_HPP

#include "Cmd.hpp"

class Help : public Cmd
{
private:
	/* data */
	Help(const Help &ref) { (void)ref; };
	Help &operator=(const Help &ref)
	{
		(void)ref;
		return *this;
	};

public:
	Help()
	{
		this->_cmd = "HELP";
	};

	~Help(){};

	void ft_recv(std::vector<std::string> msg)
	{
		(void)msg;
		this->_subject = "start";
		this->ft_set_client("704");
		this->_send_msg = RPL_HELPSTART(this->_client, this->_subject, "--------------------------------------------------- HELP -----------------------------------------------------");
		this->ft_send();
		this->ft_set_client("705");
		this->_send_msg = RPL_HELPTXT(this->_client, this->_subject, "[Usage for Sending Private messages]");
		this->ft_send();
		this->_send_msg = RPL_HELPTXT(this->_client, this->_subject, "- PRIVMSG - \"/privmsg nickname message\" : message to nickname");
		this->ft_send();
		this->_send_msg = RPL_HELPTXT(this->_client, this->_subject, "[Command List in the Public Channel or General]");
		this->ft_send();
		this->_send_msg = RPL_HELPTXT(this->_client, this->_subject, "-  JOIN  - \"/join channel_name\" : join a channel or create a channel if not exist.");
		this->ft_send();
		this->_send_msg = RPL_HELPTXT(this->_client, this->_subject, "-  LIST  - \"/list\" : list channels.");
		this->ft_send();
		this->_send_msg = RPL_HELPTXT(this->_client, this->_subject, "-  HELP  - \"/help\" : display HELP.");
		this->ft_send();
		this->_send_msg = RPL_HELPTXT(this->_client, this->_subject, "[Command List in a Channel]");
		this->ft_send();
		this->_send_msg = RPL_HELPTXT(this->_client, this->_subject, "-  KICK  - \"/kick nickname\" : kick the user who has the nickname out of the channel.");
		this->ft_send();
		this->_send_msg = RPL_HELPTXT(this->_client, this->_subject, "- INVITE - \"/invite nickname\" : invite the user who has the nickname.");
		this->ft_send();
		this->_send_msg = RPL_HELPTXT(this->_client, this->_subject, "-  TOPIC - \"/topic topic_content(or empty)\" : change the topic as topic_content or view the topic if empty.");
		this->ft_send();
		this->_send_msg = RPL_HELPTXT(this->_client, this->_subject, "-  MODE  - \"/mode options(+, -, i, t, k, o, l)\"");
		this->ft_send();
		this->_send_msg = RPL_HELPTXT(this->_client, this->_subject, "           \"/mode +(-)i\" : invite-only channel flag.");
		this->ft_send();
		this->_send_msg = RPL_HELPTXT(this->_client, this->_subject, "           \"/mode +(-)t\" : topic settable by channel operator only flag.");
		this->ft_send();
		this->_send_msg = RPL_HELPTXT(this->_client, this->_subject, "           \"/mode +(-)k password\" : set/unset the channel key.");
		this->ft_send();
		this->_send_msg = RPL_HELPTXT(this->_client, this->_subject, "           \"/mode +(-)o user_name\" : give/take channel operator privilege to user_name.");
		this->ft_send();
		this->_send_msg = RPL_HELPTXT(this->_client, this->_subject, "           \"/mode +l number | mode (-)l\" : set the user limit to channel, when unset it, it doesn't need the number parameter");
		this->ft_send();
		this->ft_set_client("706");
		this->_send_msg = RPL_ENDOFHELP(this->_client, this->_subject, "---------------------------------------------------------------------------------------------------------------");
		this->ft_send();
	}
};
#endif
