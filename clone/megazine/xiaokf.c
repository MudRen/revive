// Room: /u/wfoxd/xiaokf.c

inherit ROOM;

void create()
{
	set("short", "【幽风山庄小客房】");
	set("long", @LONG
这儿是山庄的小客房，布置一般，是给一些二流角色住。
LONG
	);
	set("exits", ([ /* sizeof() == 1 */
  		"north" : __DIR__"wroom",
	]));

	setup();
	replace_program(ROOM);
}
