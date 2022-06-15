#pragma once
#include <string>

class MemberProp
{
public:
	std::string type_;
	unsigned char offset_;
	unsigned char length_;

	MemberProp()
	{
		type_ = "null";
		offset_ = 0;
		length_ = 0;
	}

	MemberProp(std::string type, unsigned char offset, unsigned char length)
		: type_(type), offset_(offset), length_(length) {}
};

