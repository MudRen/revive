inherit ROOM;

void create()
{
        set("short", "���ķ�ɽׯ�ſڡ�" );
        set("long",
@LONG                     
��Ŀ����������ߵ�����������������������������ߡ������
����һ�¸�ǽ(wall)��ס�����ȥ·���������Ը����鿴��һ��ȴֻ����
һ�����ţ�men).
LONG
);
        set("exits", ([
                "enter" : __DIR__"ygc",
                "south" : __DIR__"lu1",
]));
        set("objects",([
                 "/d/baituo/npc/guanjia" :1,
                 "/d/hangzhou/npc/maque" : 2,
]));
        set("item_desc", ([
                 "men" : "һ��һ�����ߵĴ��š�\n",
                              "wall" : "һ�ºܸߺܸߵ�ǽ��\n",
]));  
        set("no_clean_up", 1);
        set("valid_startroom", 1);
        setup ();
	replace_program(ROOM);
}
