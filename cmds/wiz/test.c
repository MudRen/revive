// test.c

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        write(ESC "[" + arg);
        write("abcdefg\n");
	return 1;
}

int help()
{
	write(@TEXT
ָ���ʽ��test

	return 1;
TEXT );
}
