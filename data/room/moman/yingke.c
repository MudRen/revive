// SN:NJ[PM^@lUfa[D\IM
// File(/data/room/moman/yingke.c) of moman's room
// Create by LUBAN written by Doing Lu

#include <room.h>

     inherit PRIVATE_ROOM;

void create()
{
        set("short", "绿竹苑迎客厅");
	set ("long", @LONG
这里是绿竹苑的迎客厅，只见桌、椅、茶几均以粗竹子做成，简
单又不失精致。某人经常在这里接待慕名拜访的江湖英雄、八方来客。
东面一个小门通往茶室，三五知已时常在那里品茗、打牌，娱乐消遣。
LONG );

	set("exits", ([
		"north"  : __DIR__"yishiting",
                "south"  : __DIR__"zoudao",
                "east"   : __DIR__"chashi",
	]));

        create_door("east", "木门", "west", DOOR_CLOSED);

        set("objects", ([
                __DIR__"npc/yahuan1" : 1,
                __DIR__"npc/yahuan2" : 1,
        ]));

        set("no_sleep_room", 1);
        setup();

        set("room_owner", "某人");
        set("room_name", "绿竹苑");
        set("room_id", "bamboo");
        set("room_owner_id", "moman");
        set("room_position", "芦岩瀑布");
}
