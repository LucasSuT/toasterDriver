#pragma once
#include "ParserType0.h"
#include "ParserType1.h"
#include "ParserType2.h"
#include "ParserType3.h"

class Factory {
public:
	Parser* GetParser(int type)
	{
		if (s)
		{
			delete(s);
			s = NULL;
		}
		switch (type)
		{
			case 0:
			{
				s = new ParserType0();
				return s;
				break;
			}
			case 1:
			{
				s = new ParserType1();
				return s;
				break;
			}
			case 2:
			{
				s = new ParserType2();
				return s;
				break;
			}
			case 3:
			{
				s = new ParserType3();
				return s;
				break;
			}
			default:
			{
				return NULL;
				break;
			}
		}
	}

	~Factory()
	{
		if (s)
		{
			delete(s);
			s = NULL;
		}
	}
private:
	Parser* s = NULL;
};