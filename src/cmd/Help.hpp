#ifndef HELP_HPP
# define HELP_HPP

#include "Cmd.hpp"

class Help: public Cmd
{
private:
	/* data */
	Help(const Help& ref) {};
	Help&	operator=(const Help& ref) { return *this; };

public:
	Help()
	{
		this->_cmd = "HELP";
	};
	
	~Help() {};

	void ft_recv(std::vector<std::string> msg)
	{
		/* new need   txt 를 읽어와 출력 혹은 집접 출력*/
		// RPL_HELPSTART(this->_client, this->_subject, "--------------------------------------------------- HELP -----------------------------------------------------");
		// this->ft_send();
		// RPL_HELPTXT(this->_client, this->_subject, "[Usage for Sending Private messages]");
		// this->ft_send();
		// RPL_HELPTXT(this->_client, this->_subject, "[Command List in the Public Channel or General]");
		// this->ft_send();
		// RPL_HELPTXT(this->_client, this->_subject, "-  JOIN  - \"/join channel_name\" : join a channel or create a channel if not exist.");
		// this->ft_send();
		// RPL_HELPTXT(this->_client, this->_subject, "-  LIST  - \"/list [empty] or [-c channel_name]\" : list channel if there is an option or users in the channel.");
		// this->ft_send();
		// RPL_HELPTXT(this->_client, this->_subject, "-  HELP  - \"/help\" : display HELP.");
		// this->ft_send();
		// RPL_HELPTXT(this->_client, this->_subject, "[Command List in a Channel]");
		// this->ft_send();
		// RPL_HELPTXT(this->_client, this->_subject, "-  KICK  - \"/kick user_name\" : kick the user out of the channel.");
		// this->ft_send();
		// RPL_HELPTXT(this->_client, this->_subject, "- INVITE - \"/invite user_name\" : invite the user.");
		// this->ft_send();
		// RPL_HELPTXT(this->_client, this->_subject, "-  TOPIC - \"/topic topic_content(or empty)\" : change the topic as topic_content or view the topic if empty.");
		// this->ft_send();
		// RPL_HELPTXT(this->_client, this->_subject, "-  MODE  - \"/mode options(i, t, k, o, l)\"");
		// this->ft_send();
		// RPL_HELPTXT(this->_client, this->_subject, "           \"/mode i\" : set/remove invite-only channel.");
		// this->ft_send();
		// RPL_HELPTXT(this->_client, this->_subject, "           \"/mode t\" : set/remove the restrictions of the TOPIC command to channel operators.");
		// this->ft_send();
		// RPL_HELPTXT(this->_client, this->_subject, "           \"/mode k (-set password) or (-rm)\" : set/remove the channel key.");
		// this->ft_send();
		// RPL_HELPTXT(this->_client, this->_subject, "           \"/mode o user_name\" : give/take channel operator privilege to user_name.");
		// this->ft_send();
		// RPL_HELPTXT(this->_client, this->_subject, "           \"/mode l number\" : set/remove the user limit to channel if number is zero, the limitation is of");
		// this->ft_send();
		// RPL_ENDOFHELP(this->_client, this->_subject,"---------------------------------------------------------------------------------------------------------------");
		// this->ft_send();
	}
};
//Request: HELPOP CUSER
//Response: :*.freenode.net 704 nick_name CUSER :User Commands
//Response: :*.freenode.net 705 nick_name CUSER :ACCEPT      ADMIN       AWAY        COMMANDS    CYCLE       DCCALLOW
//Response: :*.freenode.net 706 nick_name CUSER :End of /HELPOP.
#endif
