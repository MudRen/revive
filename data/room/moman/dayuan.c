// SN:bnIM[7NKh]g[C0ma
// File(/data/room/moman/dayuan.c) of moman's room
// Create by LUBAN written by Doing Lu

     inherit PRIVATE_ROOM;

void create()
{
        set("short", "����Է");
	set ("long", @LONG
һ��խխ�����ӵľ�ͷ����һƬ�ô������ԣ�ӭ��ҡҷ������
��Ȼ��ֻ�������϶������������ڸ��٣�СԺ��һƬ��������������
����Ȼ�������硣
LONG );

	set("exits", ([
		"north"  : __DIR__"qianting",
                "out"    : "/d/songshan/luyanpubu",
	]));

        set("outdoors", "songshan");
        set("no_sleep_room", 1);
        set("valid_startroom", 1);
        setup();

        set("room_owner", "ĳ��");
        set("room_name", "����Է");
        set("room_OWNER_id", "moman");
        set("room_id", "bamboo");
        set("room_owner_id", "moman");
        set("room_position", "«���ٲ�");
}
