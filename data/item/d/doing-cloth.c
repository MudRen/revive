// SN:ZThk9XGo=Y\?Sj]9
// ITEM Made by player(΢��:doing) /data/item/d/doing-cloth.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Fri Mar  2 15:56:19 2001
#include <ansi.h>
#include <armor.h>

inherit CLOTH;
inherit F_ITEMMAKE;

void create()
{
	set_name(HIY "��ɽ��������" NOR, ({ "cloth" }));
	set_weight(1400);
	set("item_make", 1);
	set("unit", "��");
	set("long", HIY "�ݳ����������ɴ�����ֻ�ϻ���Ƥ���Ƶ����磬�������м������������\n"
                    "��ʮ��ļ�ð��ɫ����΢�����ļ����Ȿ����֮һ��Ϊ��΢�������Ӵ���\n"
                    "�����ȣ��������еĸ���ͳͳ�����⵰��\n" NOR);
	set("value", 1);
	set("point", 190);
	set("material", "silk");
	set("wear_msg", HIY "$N" HIY "������$n" HIY "��\n" NOR);
	set("remove_msg", HIY "$N" HIY "������$n" HIY "��̾��һ������\n" NOR);
	if (! check_clone()) return;
	restore();
	set("armor_prop/armor", apply_armor());

	setup();
}

string long() { return query("long") + item_long(); }
