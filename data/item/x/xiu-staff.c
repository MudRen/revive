// ITEM Made by player(�ɿɿ�:xiu) /data/item/x/xiu-staff.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Tue Jan 30 17:03:21 2001
#include <ansi.h>
#include <weapon.h>

inherit STAFF;
inherit F_ITEMMAKE;

void create()
{
	set_name("����[2;37;0m", ({ "staff" }));
	set_weight(9000);
	set("item_make", 1);
	set("unit", "��");
	set("long", "������[1;35m����[2;37;0m���ƶ��ɵ�һ���ȡ�
�ȱ��Ͽ���һ��С�֣��ɿɿ�(xiu)
");
	set("value", 1);
	set("point", 250);
	set("material", "magic stone");
	set("wield_msg", "[1;36m$N[1;36mһ����Х������һ��[1;36m$n[1;36m��[2;37;0m\n");
	set("unwield_msg", "$N����һĨ��������$n��\n");
	if (! check_clone()) return;
	restore();
	init_staff(apply_damage());

	setup();
}

string long() { return query("long") + item_long(); }
