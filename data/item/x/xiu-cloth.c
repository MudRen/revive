// ITEM Made by player(¿É¿É¿É:xiu) /data/item/x/xiu-cloth.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Tue Jan 30 17:31:56 2001
#include <ansi.h>
#include <armor.h>

inherit CLOTH;
inherit F_ITEMMAKE;

void create()
{
	set_name("²¼ÒÂ[2;37;0m", ({ "cloth" }));
	set_weight(1050);
	set("item_make", 1);
	set("unit", "ÕÅ");
	set("long", "ÕâÊÇÓÉ[1;37m±ù²ÏË¿[2;37;0mÁ¶ÖÆ¶ø³ÉµÄÒ»ÕÅ¼×¡£
¼×ÔµÉÏ¿Ì×ÅÒ»ĞĞĞ¡×Ö£º¿É¿É¿É(xiu)
");
	set("value", 1);
	set("point", 250);
	set("material", "silk");
	set("wear_msg", "[33m$N[33m×°±¸²¼ÒÂ[2;37;0m[33m¡£[2;37;0m\n");
	set("remove_msg", "[33m$N[33mÍÑÏÂÁË²¼ÒÂ[2;37;0m[33m¡£[2;37;0m\n");
	if (! check_clone()) return;
	restore();
	set("armor_prop/armor", apply_armor());

	setup();
}

string long() { return query("long") + item_long(); }
