// regiser: entry.c
// by Doing

inherit ROOM;

void create()
{
	set("short", "������Դ");
	set("long", @LONG
�����һ��续�����ⰻȻ��С����ˮ����Ӣ�ͷף���һ��ʫ�����⡣
�ӱ���һ���ʯ��һŮ����ױ�ع�����ʯ��ü��˵�����İ�˼���Ա�һ
����Ӣ��ͦ�Σ���Ȼ������
        �Ա���һ������(paizi)����Ҳ��Ӧ����ϸ������
LONG );
	set("no_fight", 1);
	set("item_desc", ([
		"paizi" : "����ע�᣺register your-email��Ȼ������Էֱ�ȥ��ͬ�ĳ���ѡ����\n"
                          "������Ʒ�ʡ�\n",
	]));
	set("objects", ([
		__DIR__"npc/shuisheng" : 1,
                __DIR__"npc/diyun"     : 1,
	]));
	set("exits", ([
                "east"  : __DIR__"roome",
		"south" : __DIR__"rooms",
                "west"  : __DIR__"roomw",
		"north" : __DIR__"roomn",
	]));

	setup();
}

int valid_leave(object me, string dir)
{
        object ob;
        if (! objectp(ob = present("shui sheng", this_object())))
        {
                ob = new(__DIR__"npc/shuisheng");
                ob->move(this_object());
        }

        if (! me->query("registered"))
        {
                message_vision("ˮ��������$N˵������û��ע���أ�����ע��(register)��"
                               "��ȥ����\n", me);
		if (me->query_temp("email"))
			return notify_fail("�����ȷ������ĵ�ַ���;���(decide)�ɣ�\n");
                return notify_fail("�㻹����ע�᣿\n");
        }

        if (! objectp(ob = present("di yun", this_object())))
        {
                ob = new(__DIR__"npc/diyun");
                ob->move(this_object());
        }
        message_vision("���ƶ�$Nһ��ȭ����������·ȫ���Լ��ߣ������ߺã�\n", me);

        return 1;
}

