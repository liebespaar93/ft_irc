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
	// /topic은 request랑 response가 없다...?
	// /topic 정하기 전에 '/topic'을 하면 'No topic set for #room_name'
	// '/topic abc def ghi'를 하면
	// Request: TOPIC #test02 :abc def ghi
	// Response: :gyeongjukim!~gyeongjuk@2748-3f2-dd20-23f5-64d.50.120.ip TOPIC #test02 :abc def ghi
	// gyeongjukim changed the topic of #test02 to: abc def ghi
	// '/topic' 하면 아래 메시지가 채팅방에 나오고 request 요청은 없다.
	// 23:55 -!- Topic for #test02: abc def ghi
	// 23:55 -!- Topic set by gyeongjukim
	//           [~gyeongjuk@2748-3f2-dd20-23f5-64d.50.120.ip] [Sat Jun 17 23:54:21 2023]
};

#endif
