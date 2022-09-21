#pragma once

class MemberProp
{
public:
	unsigned char type_;
	unsigned char offset_;
	unsigned char length_;
	bool revise_;

	MemberProp()
	{
		type_ = 0xFF;
		offset_ = 0;
		length_ = 0;
		revise_ = false;
	}

	MemberProp(unsigned char type, unsigned char offset, unsigned char length, bool revise)
		: type_(type), offset_(offset), length_(length), revise_(revise){}
};

