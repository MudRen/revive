// Room: /u/wfoxd/wroom.c

inherit ROOM;

void create()
{
	set("short", "走廊");
	set("long", @LONG
这是去山庄西边的走廊。你可以看见走廊上精致无比的雕刻画。
LONG
	);
	set("exits", ([ /* sizeof() == 4 */
  		"north" : __DIR__"chuchangshi",
  		"south" : __DIR__"xiaokf",
  		"east" : __DIR__"ygc",
  		"west" : __DIR__"xiaohuayuan",
	]));

	setup();
	replace_program(ROOM);
}
