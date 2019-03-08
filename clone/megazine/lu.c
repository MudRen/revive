#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIG "【幽风谷谷口】" HIY);
        set("long", 
@LONG                     
四周的悬崖包围着这个山谷,旁边有个石碑写着“幽风谷--闲人免进”
几个字。天上不时传来的苍鹰叫声时时刻刻提醒着你这是一个人迹罕至的地方,
但你在这里却感到无比地顺心如意.前面的小路被迷雾笼罩,你只能模糊的看
见一片树林里有几间殿宇。
LONG);
        set("exits", ([
             "north" : __DIR__"u1",
             "back" : "/d/city/guangchang",
	]));
        set("objects", ([
             "/d/baituo/npc/fox.c" : 1,
	]));
	replace_program(ROOM);
        setup ();     
}

