// SN:@hZRV4oKFfk?>_B_
// ITEM Made by player(΢��:doing) /data/item/d/doing-boots.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Fri Mar  2 16:01:27 2001
#include <ansi.h>
#include <armor.h>

inherit BOOTS;
inherit F_ITEMMAKE;

void create()
{
	set_name(HIR "����ɽţƤѥ" NOR, ({ "boots" }));
	set_weight(420);
	set("item_make", 1);
	set("unit", "˫");
	set("long", HIR "��ѥ�˻���ɽţͷ��֮Ƥ�Ƴɣ���ʵ�ޱȣ��������ɷ��ˣ�������񣬾�\n"
                    "�ܽ�֮һ��������Ȧ���������к����ı��\n" NOR);
	set("value", 1);
	set("point", 76);
	set("material", "silk");
	set("wear_msg", HIR "$N" HIR "�ó�һ���۵�СС��ţƤ��ӭ��չ��������$n" HIR "���漴���ϡ�\n" NOR);
	set("remove_msg", HIR "$N" HIR "������$n" HIR "������ССһ������������\n" NOR);
	if (! check_clone()) return;
	restore();
	set("armor_prop/armor", apply_armor());
	set("armor_prop/dodge", apply_armor() / 10 + 1);

	setup();
}

void init()
{
        add_action("do_kick", "kick");
}

int do_kick(string arg)
{
        object me;
        object ob;
        object mask;

        me = this_player();
        if (! query("equipped") || me != environment())
                return 0;

        if (! arg) return 0;
        if (! objectp(ob = present(arg, environment(me))) ||
            ! me->visible(ob))
                return notify_fail("��Ҫ��˭ʩչ������\n");

        if (ob == me)
                return notify_fail("����ë������\n");

        if (! playerp(ob))
                return notify_fail("��ֻ������ҡ�\n");

        if (environment(ob) == find_object("/d/city/zhujuan"))
                return notify_fail("����������Ȧ�����ء�\n");

        if (wiz_level(me) < 1 || wiz_level(ob) > wiz_level(me))
        {
                message_vision("$N����$n����һ�ţ�����ߵ����壬�໽���������\n", me, ob);
                return 1;
        }

        message_vision(HIM "$N" HIM "����һ������$n"
                       HIM "��ƨ�ɣ���$n" HIM "�ߵ�����Ȧ��\n" NOR, me, ob);
        ob->move("/d/city/zhujuan");
        message("vision", "ֻ��һ���ҽУ�" + ob->name() + "�Ǳ������Ĺ��˽�����\n",
                environment(ob), ob);
        
        return 1;
}

string long() { return query("long") + item_long(); }
