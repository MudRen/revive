// ITEM Made by player(ĳ��:moman) /data/item/m/moman-mylove.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Tue Jan 30 16:38:47 2001
#include <ansi.h>
#include <weapon.h>

inherit SWORD;
inherit F_ITEMMAKE;

void create()
{
	set_name("[1;35m�һ�[1;34m��[2;37;0m", ({ "mylove" }));
	set_weight(9000);
	set("item_make", 1);
	set("unit", "��");
	set("long", "������[1;35m����[2;37;0m���ƶ��ɵ�һ������

[1;35m�һ�[1;33m����ǧ���ޣ�
[1;37m����[1;33m��缸�Ⱦ���

[1;37m����һ��[1;36m����
[2;37;0m
�����Ͽ���һ��С�֣�ĳ��(moman)
");
	set("value", 1);
	set("point", 181);
	set("material", "magic stone");
	set("wield_msg", "\n[1;37m$N���һָ��[1;35m�һ�[1;34m��[1;37m���ֶ����������������������磬ҫ��������\n[2;37;0m\n");
	set("unwield_msg", "\n[1;37m$N˫��һ�ϣ�������������â���ۣ�����֮�䣬[1;35m�һ�[1;34m��[1;37m��ʧ���Ρ�\n[2;37;0m\n");
	if (! check_clone()) return;
	restore();
	init_sword(apply_damage());

	setup();
}

string long() { return query("long") + item_long(); }
