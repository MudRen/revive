// File(/data/room/doing/xiaoyuan.c) of doing's room
// Create by LUBAN written by Doing Lu

     inherit PRIVATE_ROOM;

void create()
{
        set("short", "����СԺ");
	set ("long", @LONG
������һ�����ķ�����Ժ�ӣ�Ժǽ�����ú�ש���ɣ�����ߣ���
�Ƿǳ���ˬ���䡣Ժ�м��ù�ľ������Ȼ��һ��������Դ�ĸо���
Ժ��������Լ������̨��Ժ�ӵı�����һ��ľ�š� 
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
    
        set("room_owner", "΢��");
        set("room_name", "����");
        set("room_OWNER_ID", "doing");
        set("room_id", "test");
        set("room_position", "����̨");
}
