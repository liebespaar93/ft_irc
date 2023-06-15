#ifndef NICK_HPP
# define NICK_HPP

#include "Cmd.hpp"


class Nick: public Cmd
{
private:
	/* data */
	Nick(const Nick& ref) {};
	Nick&	operator=(const Nick& ref) {return *this;};

public:
	Nick() { this->_cmd = "NICK";};
	~Nick() {};

	void ft_recv(std::vector<std::string> msg)
	{
		// this._
	}
// 실제 상용시 2번째 파람에 닉으로 변경 같을경우 안함
// ERR_NONICKNAMEGIVEN (431)
// ERR_ERRONEUSNICKNAME (432)
// ERR_NICKNAMEINUSE (433)
// ERR_NICKCOLLISION (436)
//.nickname [ [ "!" user ] "@" host ] 성공시 밑에 예시
// Response: :test!~myname@freenode-tki.fvn.6ohrpn.IP NICK :test2

};

#endif
