// SN:NJ[PM^@lUfa[D\IM
// File(/data/room/moman/yingke.c) of moman's room
// Create by LUBAN written by Doing Lu

#include <room.h>

     inherit PRIVATE_ROOM;

void create()
{
        set("short", "����Էӭ����");
	set ("long", @LONG
����������Է��ӭ������ֻ�������Ρ��輸���Դ��������ɣ���
���ֲ�ʧ���¡�ĳ�˾���������Ӵ�Ľ���ݷõĽ���Ӣ�ۡ��˷����͡�
����һ��С��ͨ�����ң�����֪��ʱ��������Ʒ�������ƣ�������ǲ��
LONG );

	set("exits", ([
		"north"  : __DIR__"yishiting",
                "south"  : __DIR__"zoudao",
                "east"   : __DIR__"chashi",
	]));

        create_door("east", "ľ��", "west", DOOR_CLOSED);

        set("objects", ([
                __DIR__"npc/yahuan1" : 1,
                __DIR__"npc/yahuan2" : 1,
        ]));

        set("no_sleep_room", 1);
        setup();

        set("room_owner", "ĳ��");
        set("room_name", "����Է");
        set("room_id", "bamboo");
        set("room_owner_id", "moman");
        set("room_position", "«���ٲ�");
}
