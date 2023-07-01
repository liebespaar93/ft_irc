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
		this->_send_msg = RPL_HELPSTART(this->_client, "*", "--------------------------------------------------- HELP -----------------------------------------------------");
		this->ft_append_msg();
		this->ft_set_client("705");
		this->_send_msg = RPL_HELPTXT(this->_client, "*", "[Usage for Sending Private messages]");
		this->ft_append_msg();
		this->_send_msg = RPL_HELPTXT(this->_client, "*", "- PRIVMSG - \"/privmsg nickname message\" : message to nickname");
		this->ft_append_msg();
		this->_send_msg = RPL_HELPTXT(this->_client, "*", "[Commands List]");
		this->ft_append_msg();
		this->_send_msg = RPL_HELPTXT(this->_client, "*", "-  JOIN  - \"/join channel_name\" : join a channel or create a channel if not exist.");
		this->ft_append_msg();
		this->_send_msg = RPL_HELPTXT(this->_client, "*", "-  LIST  - \"/list\" : list channels.");
		this->ft_append_msg();
		this->_send_msg = RPL_HELPTXT(this->_client, "*", "-  HELP  - \"/help\" : display HELP.");
		this->ft_append_msg();
		this->_send_msg = RPL_HELPTXT(this->_client, "*", "[Commands List in Channel]");
		this->ft_append_msg();
		this->_send_msg = RPL_HELPTXT(this->_client, "*", "-  KICK  - \"/kick nickname\" : kick the user who has the nickname out of the channel.");
		this->ft_append_msg();
		this->_send_msg = RPL_HELPTXT(this->_client, "*", "- INVITE - \"/invite nickname\" : invite the user who has the nickname.");
		this->ft_append_msg();
		this->_send_msg = RPL_HELPTXT(this->_client, "*", "-  TOPIC - \"/topic topic_content(or empty)\" : change the topic to topic_content or view the topic if empty.");
		this->ft_append_msg();
		this->_send_msg = RPL_HELPTXT(this->_client, "*", "-  MODE  - \"/mode options(+, -, i, t, k, o, l)\"");
		this->ft_append_msg();
		this->_send_msg = RPL_HELPTXT(this->_client, "*", "           \"/mode +(-)i\" : invite-only channel flag.");
		this->ft_append_msg();
		this->_send_msg = RPL_HELPTXT(this->_client, "*", "           \"/mode +(-)t\" : topic settable by channel operator only flag.");
		this->ft_append_msg();
		this->_send_msg = RPL_HELPTXT(this->_client, "*", "           \"/mode +(-)k password\" : set/unset the channel key.");
		this->ft_append_msg();
		this->_send_msg = RPL_HELPTXT(this->_client, "*", "           \"/mode +(-)o user_name\" : give/take channel operator privilege to user_name.");
		this->ft_append_msg();
		this->_send_msg = RPL_HELPTXT(this->_client, "*", "           \"/mode +l number | mode (-)l\" : set the user limit to channel, when unset it, it doesn't need the number parameter");
		this->ft_append_msg();
		this->ft_set_client("706");
		this->_send_msg = RPL_ENDOFHELP(this->_client, "*", "---------------------------------------------------------------------------------------------------------------");
		this->ft_append_msg();
	}
};
#endif
