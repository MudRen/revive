inherit ROOM;

void create()
{
        set("short", "【幽风山庄门口】" );
        set("long",
@LONG                     
你磕磕碰碰终于走到了树林深处，看来这里比你想想的难走。你可以
看见一堵高墙(wall)挡住了你的去路。你向两旁各处查看了一下却只发现
一扇铁门（men).
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
                 "men" : "一个一丈来高的大门。\n",
                              "wall" : "一堵很高很高的墙。\n",
]));  
        set("no_clean_up", 1);
        set("valid_startroom", 1);
        setup ();
	replace_program(ROOM);
}
