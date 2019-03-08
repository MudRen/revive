// SN:X9^ne5fPYnD5PBU6
// ITEM Made by player(΢��:doing) /data/item/d/doing-helmet.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Fri Mar  2 16:07:00 2001
#include <ansi.h>
#include <armor.h>

inherit HEAD;
inherit F_ITEMMAKE;

void create()
{
	set_name(HIY "����嶥���" NOR, ({ "helmet" }));
	set_weight(4500);
	set("item_make", 1);
	set("unit", "��");
	set("long", HIY "̫���Ͼ���������¯ʱ��Ϊ����һ�龫ͭ�����ô�ͭ�ϵ�¯������ҩ�Ƴ�\n"
                    "�˱��������ޱ����ԣ�����ָ���Խ�������������š����﷨��ͨ��\n"
                    "�������Գ��ܣ���֮��������֮�֡�\n" NOR);
	set("value", 1);
	set("point", 50);
	set("material", "magic stone");
	set("wear_msg", HIY "$N" HIY "����$n" HIY "��ͷ���ֳ�һ���ʺ磬��âֱ����졣\n" NOR);
	set("remove_msg", HIY "$N" HIY "ȡ��$n" HIY "��ͷ���⻪��ʱ��ȥ��\n" NOR);
	if (! check_clone()) return;
	restore();
	set("armor_prop/armor", apply_armor());

	setup();
}

int wear()
{
        object owner;

        if (objectp(owner = environment()) &&
            playerp(owner))
        {
                if (wiz_level(owner) < 1)
                {
                        message_vision(HIM "$N" HIM "����$n"
                                       HIM "��ֻ����ͷ��ֱ��ǧ��֮�أ���ʱ��ѹ����ϡ�ࡣ\n" NOR,
                                       owner, this_object());
                        owner->set_temp("die_reason", "������嶥���ѹ��������");
                        owner->die();
                        return -1;
                }
        }

        return ::wear();
}

void init()
{
        add_action("do_halt", "halt");
}

int do_halt(string arg)
{
        object me;
        object ob;
        object mask;

        me = this_player();
        if (! query("equipped") || me != environment())
                return 0;

        if (wiz_level(me) < 1)
                return 0;

        if (! me->is_busy() && ! me->is_fighting())
                return 0;

        message_vision(HIM "$Nͷ��" + name() +
                       HIM "��Ȼ�ֳ�������â���漴��ɢ��\n" NOR, me);
        if (me->is_fighting())
                message_vision("�ڳ�������ͷһ�ݣ�ֹͣ�˺�$N�Ĵ򶷡�\n", me);

        me->interrupt_me(0);
        me->remove_all_enemy(1);
        return 1;
}

string long() { return query("long") + item_long(); }
