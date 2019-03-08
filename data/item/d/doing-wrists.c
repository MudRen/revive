// SN:=_?VhY;Bh`QZ8d_?
// ITEM Made by player(΢��:doing) /data/item/d/doing-wrists.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Fri Mar  2 16:05:21 2001
#include <ansi.h>
#include <armor.h>

inherit WRISTS;
inherit F_ITEMMAKE;

void create()
{
	set_name(HIY "���Ʒ�������" NOR, ({ "wrists" }));
	set_weight(3000);
	set("item_make", 1);
	set("unit", "��");
	set("long", YEL "���Ƿ�����������ɫ֮��ʯ���������������֮�������Ƶ��Ϲ������\n"
                    "�Ա�аħ�������졣��ͨ�ɺ���������ʹ�������ޱ�����֮�ء�\n" NOR);
	set("value", 1);
	set("point", 47);
	set("material", "magic stone");
	set("wear_msg", HIY "$N" HIY "����һ�У�ֻ��һ��һ����ֻ��������������â������$N" HIY "���ϡ�\n" NOR);
	set("remove_msg", HIY "$N" HIY "����һ������˫����ֻ������һ���죬˫���ʹ˲�����\n" NOR);
	if (! check_clone()) return;
	restore();

	setup();
}

void init()
{
        add_action("do_busy", "busy");
}

int do_busy(string arg)
{
        object me;
        object ob;

        me = this_player();
        if (! query("equipped") || me != environment())
                return 0;

        if (! arg) return 0;
        if (! objectp(ob = present(arg, environment(me))) ||
            ! me->visible(ob))
                return notify_fail("��Ҫ��˭ʩչ������\n");

        if (! intp(ob->query_busy()))
                return notify_fail("����������æ���ء�\n");

        if (ob == me)
                return notify_fail("����ë������\n");

        if (wiz_level(me) < 1 || wiz_level(ob) > wiz_level(me))
        {
                message_vision("$N���˶�����ɶ��Ҳû�з�����\n", me);
                return 1;
        }

        message_vision(HIM "$N" HIM "����һ������ֻ��" + name() +
                       HIM "�����巢���������������ͼ�\n" +
                       "$n" HIM "Ӧ�����ߣ������㵸���������Ρ�\n" NOR, me, ob);
        ob->start_busy(60);
        return 1;
}

string long() { return query("long") + item_long(); }
