// SN:lf;XId4OE?llPjDl
// File(/data/room/moman/yishiting.c) of moman's room
// Create by LUBAN written by Doing Lu

#include <room.h>

     inherit PRIVATE_ROOM;

void create()
{
	set("short", "������");
	set ("long", @LONG
���������Է����ĳ�˺���Ҫ������������ĵط��������ش��
�ա������ٳ���ĳ��������ˣ�Ҳ�������³��������������ͣ���
�õ�����һ��������ͨ����������
LONG );

	set("exits", ([
                "east"   : __DIR__"yanwu1",
                "west"   : __DIR__"yanwu2",
		"north"  : __DIR__"zhongting",
                "south"  : __DIR__"yingke",
	]));

        set("no_sleep_room", 1);
        setup();

        set("room_owner", "ĳ��");
        set("room_name", "����Է");
        set("room_id", "bamboo");
        set("room_owner_id", "moman");
        set("room_position", "«���ٲ�");
}
