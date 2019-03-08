// SN:[M`Hhiemof9DL_n;
// ITEM Made by player(΢��:doing) /data/item/d/doing-hands.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Fri Mar  2 16:17:02 2001
#include <ansi.h>
#include <armor.h>

inherit HANDS;
inherit F_ITEMMAKE;

void create()
{
	set_name(HIB "�޳�����ħ��" NOR, ({ "hands" }));
	set_weight(2700);
	set("item_make", 1);
	set("unit", "˫");
	set("long", HIB "���ǵز�������ظ�����֮�������Ƶı���˵ظ����Ϸ������Ǻڰ���\n"
                    "�����Գ��������׺��»�Ұ��ʱʹ�õ�������\n" NOR);
	set("value", 1);
	set("point", 190);
	set("material", "magic stone");
	set("wear_msg", HIB "$N" HIB "����һָ�����Ź��ص�����������˫�֣����������$n" HIB "������һ���ļ¡�\n" NOR);
	set("remove_msg", HIB "$N" HIB "���ϵ�$n" HIB "��Ȼ����һ�����̣��ʹ���ʧ�����˵�ʱ������ͷ�����ʯ��أ����ɲ��١�\n" NOR);
	if (! check_clone()) return;
	restore();
	set("armor_prop/armor", 10);
	set("armor_prop/hand", 10);
	set("armor_prop/unarmed_damage", apply_damage());
	set("armor_prop/strike", 10);

	setup();
}

void init()
{
        add_action("do_pat", "pat");
}

int do_pat(string arg)
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

        if (! ob->is_ghost())
                return notify_fail("��ֻ�ܶԹ��ʩչ������\n");

        if (environment(ob) == find_object("/d/death/gate"))
                return notify_fail("�������ڵظ��Ⱥ����ء�\n");

        if (wiz_level(me) < 1 || wiz_level(ob) > wiz_level(me))
        {
                message_vision("$N������$n������ûɶ��Ӧ��\n", me, ob);
                return 1;
        }

        message_vision(HIB "$N" HIB "һ������$n" HIB "��ֻ��һ�����̹���$n"
                       HIB "��ʧ����Ӱ���١�\n" NOR, me, ob);
        ob->move("/d/death/gate");
        message("vision", "ֻ���ҽ�������" + ob->name() + "ˤ�˽�����\n",
                environment(ob), ob);
        
        return 1;
}

string long() { return query("long") + item_long(); }
