// ITEM Made by player(Ľ�ݼ���:zeroz) /data/item/z/zeroz-egg.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Tue Jan 30 18:07:07 2001
#include <ansi.h>
#include <weapon.h>

inherit SWORD;
inherit F_ITEMMAKE;

void create()
{
	set_name("����[2;37;0m", ({ "egg" }));
	set_weight(9000);
	set("item_make", 1);
	set("unit", "��");
	set("long", "������[1;35m����[2;37;0m���ƶ��ɵ�һ������
Ľ�ݼ���������ʣ�µĶ���[2;37;0m
�����Ͽ���һ��С�֣�Ľ�ݼ���(zeroz)
");
	set("value", 2100000);
	set("point", 190);
	set("material", "magic stone");
	set("wield_msg", "[1;31m$N���κ�Ȼ��ù����쳣������֮��Ʈ�������������޴�׽����\n\n[1;37m$N���Ӻ�ǰ���󣬺�����ң�һ������˵�崷�ӿ����סȫ��\n\n[1;33m$N���Ӻ�ǰ���󣬺�����ң�һ������˵�崷�ӿ����סȫ��[2;37;0m\n");
	set("unwield_msg", "[1;37m$N��ɫһ�������ְ�˪�������Ȼ�����������õ����ɡ�\n\n[1;37m$N˫��ƽ�ٹ���������С���๦��ȫ�������ھ���֮�У�\n\n[1;32m$N�������˱�������ҪѨ��Ȼ���������˫Ŀһ������ʱ�������䣡[2;37;0m\n");
	if (! check_clone()) return;
	restore();
	init_sword(apply_damage());

	setup();
}

string long() { return query("long") + item_long(); }
