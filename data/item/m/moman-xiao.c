// ITEM Made by player(ĳ��:moman) /data/item/m/moman-xiao.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Wed Jan 31 17:49:01 2001
#include <ansi.h>
#include <weapon.h>

inherit XSWORD;
inherit F_ITEMMAKE;

void create()
{
	set_name("[1;32m����[2;37;0m", ({ "xiao" }));
	set_weight(1800);
	set("item_make", 1);
	set("unit", "֧");
	set("long", "������[1;35m����[2;37;0m���ƶ��ɵ�һ֧�

[1;32mһ֧�������ɵĳ�������Ө��͸��һ����֪���˼䷲Ʒ��
[2;37;0m
����Ͽ���һ��С�֣�ĳ��(moman)
");
	set("value", 1);
	set("point", 181);
	set("material", "magic stone");
	set("wield_msg", "[1;37m$N����һƮ�������Ѷ���һ֧��Ө��͸��[2;37;0m[1;32m����[2;37;0m[1;37m��[2;37;0m\n");
	set("unwield_msg", "[1;37m$N������ת��գ�ۼ�[2;37;0m[1;32m����[2;37;0m[1;37m��Ȼ����Ӱ�١�[2;37;0m\n");
	if (! check_clone()) return;
	restore();
	init_xsword(apply_damage());

	setup();
}

string long() { return query("long") + item_long(); }
