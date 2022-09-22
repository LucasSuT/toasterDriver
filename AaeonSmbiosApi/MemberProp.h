#pragma once

class MemberProp
{
public:
	unsigned char type_;
	unsigned char offset_;
	unsigned char length_;
	bool can_be_modified_;

	MemberProp()
	{
		type_ = 0xFF;
		offset_ = 0;
		length_ = 0;
		can_be_modified_ = false;
	}

	MemberProp(unsigned char type, unsigned char offset, unsigned char length, bool can_be_modified)
		: type_(type), offset_(offset), length_(length), can_be_modified_(can_be_modified){}
};

