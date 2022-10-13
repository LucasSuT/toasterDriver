#pragma once

class MemberProp
{
public:
	unsigned char data_type_;
	unsigned char offset_;
	unsigned char length_;
	bool can_be_modified_;
	bool is_extra_processing_;

	MemberProp()
	{
		data_type_ = 0xFF;
		offset_ = 0;
		length_ = 0;
		can_be_modified_ = false;
		is_extra_processing_ = false;
	}

	MemberProp(unsigned char data_type, unsigned char offset, unsigned char length, bool can_be_modified)
		: data_type_(data_type), offset_(offset), length_(length), can_be_modified_(can_be_modified), is_extra_processing_(false){}
	MemberProp(unsigned char data_type, unsigned char offset, unsigned char length, bool can_be_modified, bool is_extra_processing)
		: data_type_(data_type), offset_(offset), length_(length), can_be_modified_(can_be_modified), is_extra_processing_(is_extra_processing){}
};

