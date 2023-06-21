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
	
	
	void ft_recv(std::vector<std::string> msg)
	{}

	// irssi로 여러 클라이언트를 돌리면서 /mode로 invtite only 설정을 해도 join이 되어서 테스트하기 굉장히 까다로움
	// lime으로 모드 설정과 invtite 테스트 예정
	// irssi로 했을시 초대받았다라는 메시지만 받고 채널 입장은 하지 않음
};

#endif
