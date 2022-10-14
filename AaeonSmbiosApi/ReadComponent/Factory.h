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
#include "ParserType19.h"
#include "ParserType20.h"
#include "ParserType26.h"
#include "ParserType27.h"
#include "ParserType28.h"

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
			case 19:
			{
				s = new ParserType19();
				return s;
				break;
			}
			case 20:
			{
				s = new ParserType20();
				return s;
				break;
			}
			case 26:
			{
				s = new ParserType26();
				return s;
				break;
			}
			case 27:
			{
				s = new ParserType27();
				return s;
				break;
			}
			case 28:
			{
				s = new ParserType28();
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