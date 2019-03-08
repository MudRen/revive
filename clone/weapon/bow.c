// bow.c

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name("�̹�", ({ "short bow", "bow", "duan gong", "gong" }));
        set_weight(2000);
        if (clonep())
                set_default_object(__FILE__);
        else
        {
                set("unit", "��");
                set("long", "һ�Ŷ̹����������Ϊ���£����в����׼ȷ�ȡ�\n");
		set("value", 20000);
                set("power", 100000);   // ��������
                set("accuracy", 120);   // ׼ȷ��120%
        }
        setup();
}

void init()
{
        if (this_player() == environment())
                add_action("do_shot", "shot");
}

int do_shot(string arg)
{
        string target, item;
        object me, victim;
        object ob;
        object env;
        int amount;
        int my_exp, v_exp;
        int ap;
        string msg;

        me = this_player();
        if (me->query_temp("handing") != this_object())
                return notify_fail("����Ȱ�" + name() + "��(hand)�����в��С�\n");

        env = environment(me);
        if (! env || env->query("no_fight"))
                return notify_fail("���ﲻ��ս����\n");

        if (me->is_busy())
                return notify_fail("������æ���ء�\n");

        if (me->query("jing") < 80)
                return notify_fail("�����ھ��񲻹��ã��޷�ʹ��" + name() + "�������֡�\n");

        if (! arg)
                return notify_fail("���빥��˭��\n");

        if (sscanf(arg, "%s with %s", target, item) != 2)
                return notify_fail("��Ҫ��ʲô�������֣�(shot <����> with <����>)\n");

        if (! objectp(ob = present(item, me)))
                return notify_fail("������û�� " + item + " ������Ʒ���Է��䡣\n");

        if (! ob->is_arrow())
                return notify_fail("�ⲻ�Ǽ������޷����䡣\n");

        if ((amount = ob->query_amount()) < 1)
                return notify_fail("�����ϵ�" + ob->name() + "�������ˡ�\n");

        if (! objectp(victim = present(target, env)))
                return notify_fail("����û������ˡ�\n");

        if (! victim->is_character() || victim->query("not_living"))
                return notify_fail("������ˣ��ǲ��ǻ��ˣ�\n");

        if (! me->is_fighting(victim))
                return notify_fail("��ֻ�����ս���еĶ��֡�\n");

        my_exp = me->query("combat_exp");
        v_exp = victim->query("combat_exp");

        if (my_exp < 10000)
                return notify_fail("��ʵս����̫ǳ����������" + name() + "������֡�\n");

        switch (random(3))
        {
        case 0:
                msg = "$Ņ��" + name() + "�����һ" + ob->query("base_unit") +
                      ob->name() + "����ಡ���һ������$n��\n";
                break;

        case 1:
                msg = "$N����һ�����һ" + ob->query("base_unit") +
                      ob->name() + "��ֱ��$n��ȥ��\n";
                break;

        default:
                msg = "ֻ����ಡ���һ���ƿ�����$N��׼$n���һ" + ob->query("base_unit") +
                      ob->name() + "��\n";
                break;
        }

        ap = my_exp * query("accuracy") / 100;
        if (userp(victim)) ap /= 2;

        if (v_exp / 2 + random(v_exp) > query("power") || ap < v_exp)
        {
                switch (random(3))
                {
                case 0:
                        msg += "ȴ��$n����һ������$N��" + ob->name() + "���˿�ȥ��\n";
                        break;
                case 1:
                        msg += "ֻ��$n���Ų�æ������һŤ���㿪��$N��һ�С�\n";
                        break;
                default:
                        msg += "$n��������һ������$N��" + ob->name() + "���˸��ա�\n";
                        break;
                }
        } else
        {
                msg += COMBAT_D->do_damage(me, victim, ob,
                                           ob->query("weapon_prop/damage"), ob->query("wound_percent"),
                                           HIR "ֻ��$p" HIR "һ�����ܲ���������$P"
                                           HIR "��һ" + ob->name() + HIR "����ʱ��Ѫ�ɽ���\n" NOR);
        }
        ob->add_amount(-1);
        me->start_busy(2);
        me->receive_damage("jing", 10);

        message_combatd(msg, me, victim);
        return 1;
}
