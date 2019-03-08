// ITEM Made by player(�ɿɿ�:xiu) /data/item/x/xiu-doing.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Tue Jan 30 16:42:43 2001
#include <ansi.h>
#include <armor.h>

inherit HANDS;
inherit F_ITEMMAKE;

void create()
{
	set_name("΢��[2;37;0m", ({ "doing" }));
	set_weight(2100);
	set("item_make", 1);
	set("unit", "��");
	set("long", "������[1;35m����[2;37;0m���ƶ��ɵ�һ��ָ�ס�
ָ��Ե�Ͽ���һ��С�֣��ɿɿ�(xiu)
");
	set("value", 1);
	set("point", 250);
	set("material", "magic stone");
	set("wear_msg", "[33m$N[33mװ��΢��[2;37;0m[33m��[2;37;0m\n");
	set("remove_msg", "[33m$N[33m������΢��[2;37;0m[33m��[2;37;0m\n");
	if (! check_clone()) return;
	restore();
	set("armor_prop/armor", 10);
	set("armor_prop/finger", 10);
	set("armor_prop/claw", 10);
	set("armor_prop/unarmed_damage", apply_damage());

	setup();
}

string long() { return query("long") + item_long(); }
