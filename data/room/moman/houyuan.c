// SN:l2m^QCX<M^?:l6Y8
// File(/data/room/moman/houyuan.c) of moman's room
// Create by LUBAN written by Doing Lu

     inherit PRIVATE_ROOM;

void create()
{
	set("short", "��Ժ");
	set ("long", @LONG
��������Է�ĺ�Ժ������һ����ɽ����Ȼ�������ǳ���ΰ������
һˮ�أ���ɽ���ߣ���Ȼ��Ϣ��������������֮���������ǳ����� 
LONG );

	set("exits", ([
                "south" : __DIR__"zhongting",
                "north" : __DIR__"huayuan",
                "east"  : __DIR__"lianwu",
                "west"  : __DIR__"chufang",
	]));

        set("outdoors", "songshan");
        set("no_sleep_room", 1);
        setup();

        set("room_owner", "ĳ��");
        set("room_name", "����Է");
        set("room_id", "bamboo");
        set("room_owner_id", "moman");
        set("room_position", "«���ٲ�");
}
