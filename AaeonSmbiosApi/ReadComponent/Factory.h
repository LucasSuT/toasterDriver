#pragma once
#include "ParserType0.h"
#include "ParserType1.h"
#include "ParserType2.h"
#include "ParserType3.h"
#include "ParserType4.h"
#include "ParserType7.h"
#include "ParserType8.h"
#include "ParserType9.h"
#include "ParserType10.h"
#include "ParserType11.h"
#include "ParserType12.h"
#include "ParserType13.h"
#include "ParserType14.h"
#include "ParserType16.h"
#include "ParserType17.h"

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
			case 4:
			{
				s = new ParserType4();
				return s;
				break;
			}
			case 7:
			{
				s = new ParserType7();
				return s;
				break;
			}
			case 8:
			{
				s = new ParserType8();
				return s;
				break;
			}
			case 9:
			{
				s = new ParserType9();
				return s;
				break;
			}
			case 10:
			{
				s = new ParserType10();
				return s;
				break;
			}
			case 11:
			{
				s = new ParserType11();
				return s;
				break;
			}
			case 12:
			{
				s = new ParserType12();
				return s;
				break;
			}
			case 13:
			{
				s = new ParserType13();
				return s;
				break;
			}
			case 14:
			{
				s = new ParserType14();
				return s;
				break;
			}
			case 16:
			{
				s = new ParserType16();
				return s;
				break;
			}
			case 17:
			{
				s = new ParserType17();
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