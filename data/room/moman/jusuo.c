// SN:n\3<aRYQn`XAFWDO
// File(/data/room/moman/jusuo.c) of moman's room
// Create by LUBAN written by Doing Lu

#include <room.h>

     inherit PRIVATE_ROOM;

void create()
{
	set("short", "����");
	set ("long", @LONG
�˴�����ĳ����Ϣ������ĵط���ֻ�����μ�齣���һ�������ƣ�
ǽ������һ��ī�񣬱����ݺᣬī�����죬����ɭɭ֮�⡣���Ϸ���
һ�����٣�һ�ܶ��¥�Ͼ������˵����ң����������鷿��
LONG );

	set("exits", ([
		"up"   : __DIR__"woshi",
                "west" : __DIR__"shufang",
	]));

        set("no_sleep_room", 1);
        setup();

        set("KEY_DOOR", ([
                "exit" : "east",
                "room" : __DIR__"huayuan",
        ]));
    
        set("room_owner", "ĳ��");
        set("room_name", "����Է");
        set("room_id", "bamboo");
        set("room_owner_id", "moman");
        set("room_position", "«���ٲ�");
}
