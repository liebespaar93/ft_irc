#ifndef INVITE_HPP
#define INVITE_HPP

#include "Cmd.hpp"

class Invite : public Cmd
{
private:
	/* data */
	Invite(const Invite &ref);

	Invite &operator=(const Invite &ref);

public:
	Invite() { this->_cmd = "INVITE"; };
	~Invite(){};

	// irssi로 했을시 초대받았다라는 메시지만 받고 채널 입장은 하지 않음
	// k 설정되어도 초대받으면 조인가능
};

#endif
