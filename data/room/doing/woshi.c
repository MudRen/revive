// File(/data/room/doing/woshi.c) of doing's room
// Create by LUBAN written by Doing Lu

#include <room.h>

     inherit PRIVATE_ROOM;

void create()
{
        set("short", "��������");
	set ("long", @LONG
�������˵����ң���ʰ�þ����������ϴ�����һ�Ŵ󴲣�������
һ�����ӣ�����һ����ܣ��������һЩ�顣�������Ӳ��õ÷ǳ���
�أ������ݻ������������ס� 
LONG );

	setup();

        set("exits", ([
                "west" : __DIR__"dating",
        ]));

        create_door("west", "ľ��", "east", DOOR_CLOSED);
    
        set("sleep_room", 1);
        set("loving_room", 1);
        set("no_fight", 1);
    
        set("room_owner", "΢��");
        set("room_name", "����");
        set("room_id", "test");
        set("room_position", "����̨");
}
