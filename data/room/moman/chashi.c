// SN:=g?`lDH;hn:5^;U\
// File(/data/room/moman/chashi.c) of moman's room
// Create by LUBAN written by Doing Lu

#include <room.h>

     inherit PRIVATE_ROOM;

void create()
{
	set("short", "����");
	set ("long", @LONG
��һ������С�ɵĲ��ң������Եþ��¡�������һ�輸�������
�ż���ˮ�������������ӡ����׻���Сʳ����������������������Ů��
�����������˵ķԸ�(tea)��
LONG );

	set("exits", ([
		"west"  : __DIR__"yingke",
	]));

        set("objects", ([
                __DIR__"npc/yahuan3" : 1,
                __DIR__"npc/yahuan4" : 1,
        ]));

        create_door("west", "ľ��", "east", DOOR_CLOSED);

        set("no_sleep_room", 1);
        setup();

        set("room_owner", "ĳ��");
        set("room_name", "����Է");
        set("room_id", "bamboo");
        set("room_owner_id", "moman");
        set("room_position", "«���ٲ�");
}
