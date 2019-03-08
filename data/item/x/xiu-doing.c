// ITEM Made by player(¿É¿É¿É:xiu) /data/item/x/xiu-doing.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Tue Jan 30 16:42:43 2001
#include <ansi.h>
#include <armor.h>

inherit HANDS;
inherit F_ITEMMAKE;

void create()
{
	set_name("Î¢³¾[2;37;0m", ({ "doing" }));
	set_weight(2100);
	set("item_make", 1);
	set("unit", "Ì×");
	set("long", "ÕâÊÇÓÉ[1;35mÉñÌú[2;37;0mÁ¶ÖÆ¶ø³ÉµÄÒ»Ì×Ö¸Ì×¡£
Ö¸Ì×ÔµÉÏ¿Ì×ÅÒ»ĞĞĞ¡×Ö£º¿É¿É¿É(xiu)
");
	set("value", 1);
	set("point", 250);
	set("material", "magic stone");
	set("wear_msg", "[33m$N[33m×°±¸Î¢³¾[2;37;0m[33m¡£[2;37;0m\n");
	set("remove_msg", "[33m$N[33mÍÑÏÂÁËÎ¢³¾[2;37;0m[33m¡£[2;37;0m\n");
	if (! check_clone()) return;
	restore();
	set("armor_prop/armor", 10);
	set("armor_prop/finger", 10);
	set("armor_prop/claw", 10);
	set("armor_prop/unarmed_damage", apply_damage());

	setup();
}

string long() { return query("long") + item_long(); }
