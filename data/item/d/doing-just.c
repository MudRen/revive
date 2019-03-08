// SN:F1SHD7MSni0]7<J2
// ITEM Made by player(΢��:doing) /data/item/d/doing-just.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Wed Jan 31 16:19:57 2001
#include <ansi.h>
#include <weapon.h>

inherit SWORD;
inherit F_ITEMMAKE;

void create()
{
	set_name(HIC "ʤа��" NOR, ({ "just" }));
	set_weight(9000);
	set("item_make", 1);
	set("unit", "��");
	set("long", HIC "��������Խ��������ʦ�����Ƶ��������Ϣ������������ɰ���ݼ������\n"
                    "������һ����а���������ϵĹ�������\n" NOR);
	set("value", 1);
	set("point", 190);
	set("material", "magic stone");
	set("wield_msg", HIC "$N" HIC "����һ�ӣ����ʤа������ʱ���������⻪����Ⱥа�޲���֮����\n" NOR);
	set("unwield_msg", HIC "$N" HIC "������ʤа����ὣ�ʣ��⻪��ȥ��\n" NOR);
	if (! check_clone()) return;
	restore();

        set("weapon_prop", ([
                "attack" : 1000,
                "defense" : 1000,
        ]));

	init_sword(10000);

	setup();
}

string long() { return query("long") + item_long(); }
