// ITEM Made by player(���:shell) /data/item/s/shell-flower.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Thu Feb 08 14:15:27 2001
#include <ansi.h>
#include <weapon.h>

inherit BLADE;
inherit F_ITEMMAKE;

void create()
{
	set_name("[1;35mˮ��[2;37;0m", ({ "flower" }));
	set_weight(9000);
	set("item_make", 1);
	set("unit", "��");
	set("long", "������[1;35m����[2;37;0m���ƶ��ɵ�һ�ѵ���
[37mϣ��������˹���������Լ���ˮ�еĵ�Ӱ��ˮ�ɻ����Ӵ��������ٰ����ˡ�[2;37;0m
�����Ͽ���һ��С�֣����(shell)
");
	set("value", 2100000);
	set("point", 190);
	set("material", "magic stone");
	set("wield_msg", "[1;35mˮ����\n���л�[2;37;0m\n");
	set("unwield_msg", "$N����һĨ��������$n��\n");
	if (! check_clone()) return;
	restore();
	init_blade(apply_damage());

	setup();
}

string long() { return query("long") + item_long(); }
