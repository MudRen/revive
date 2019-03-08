// ITEM Made by player(¿É¿É¿É:xiu) /data/item/x/xiu-staff.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Tue Jan 30 17:03:21 2001
#include <ansi.h>
#include <weapon.h>

inherit STAFF;
inherit F_ITEMMAKE;

void create()
{
	set_name("¸ÖÕÈ[2;37;0m", ({ "staff" }));
	set_weight(9000);
	set("item_make", 1);
	set("unit", "¸ù");
	set("long", "ÕâÊÇÓÉ[1;35mÉñÌú[2;37;0mÁ¶ÖÆ¶ø³ÉµÄÒ»¸ùÕÈ¡£
ÕÈ±úÉÏ¿Ì×ÅÒ»ĞĞĞ¡×Ö£º¿É¿É¿É(xiu)
");
	set("value", 1);
	set("point", 250);
	set("material", "magic stone");
	set("wield_msg", "[1;36m$N[1;36mÒ»ÉùÇåĞ¥£¬¶¶³öÒ»¸ù[1;36m$n[1;36m¡£[2;37;0m\n");
	set("unwield_msg", "$NËæÊÖÒ»Ä¨£¬ÊÕÆğÁË$n¡£\n");
	if (! check_clone()) return;
	restore();
	init_staff(apply_damage());

	setup();
}

string long() { return query("long") + item_long(); }
