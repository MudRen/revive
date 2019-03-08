// File(/data/room/doing/xiaoyuan.c) of doing's room
// Create by LUBAN written by Doing Lu

     inherit PRIVATE_ROOM;

void create()
{
        set("short", "测试小院");
	set ("long", @LONG
这里是一个四四方方的院子，院墙都是用红砖砌成，不算高，但
是非常清爽利落。院中几棵古木成荫，隐然有一种世外桃源的感觉。
院子外面隐约是紫气台，院子的北面有一扇木门。 
LONG );

        set("room_key", "1 of doing");
	setup();

	set("exits", ([
                "out"    : "/d/huashan/ziqitai",
	]));

        set("outdoors", "xx");
        set("no_sleep_room", 1);
        set("valid_startroom", 1);

        set("KEY_DOOR", ([
                "exit" : "north",
                "room" : __DIR__"dating",
        ]));
    
        set("room_owner", "微尘");
        set("room_name", "测试");
        set("room_OWNER_ID", "doing");
        set("room_id", "test");
        set("room_position", "紫气台");
}
