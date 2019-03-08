inherit ITEM;

#include <ansi.h>; 

void setup()
{}

void init()
{
        add_action("do_du", "du");
        add_action("do_du", "study");
}

void create()
{
        set_name(HIR "���������䡷" NOR, ({ "kuihua baodian", "baodian", "book", "kuihua"}));
        set_weight(600);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", HIR "��������ֵ�һ�ؼ����������䡷���ഫ��һλ����̫��������\n" NOR);
                set("value", 1);
                set("material", "paper");
                set("no_sell", 1);
        }
}

int do_du(string arg)
{
        object me = this_player();
        object where = environment(me);
        object ob;
        mapping skill;
        int plvl, con, improve;
        int neili_lost;

        if (! arg || ! id(arg))
                return 0;

        if (me->is_busy())
        {
                write("��������æ���ء�\n");
                return 1;
        }

        if (me->is_fighting())
        {
                write("���޷���ս����ר�������ж���֪��\n");
                return 1;
        }

        if (where->query("no_fight") && me->query("doing") != "scheme")
        {
                write("���޷������ﾲ�������ж����䡣\n");
                return 1;
        }

        if ((string)me->query("gender") == "Ů��")
        {
                write("�Թ�û����˵Ů�˿��Զ����������䡷�ġ�\n");
                return 1;
        }

        if ((string)me->query("gender") == "����")
        {
               write("���������䡷�ĵ�һҳд�ţ������񹦣������Թ���\n");
               return 1;
        }

        if (! me->query_skill("literate", 1))
        {
                write("���Ǹ���ä����ѧ���Ļ�(literate)�ɡ�\n");
                return 1;
        }

        if (me->query_skill("pixie-jian", 1) >= 180)
        {
                write("�Ȿ�����Ѿ��о��ò���ˣ�ûʲô�ö����ˡ�\n");
                return 1;
        }

        if ((int)me->query("combat_exp") < 200000)
        {
                        write("���ʵս���鲻�㣬����ô��Ҳû�á�\n");
                        return 1;
        }

        if ((int)me->query("max_neili") < 500)
        {
                        write("�������̫��޷������˵��񹦡�\n");
                        return 1;
        }

        switch (random(3))
        {
        case 0:
                message("vision", me->name() + "͵͵��������"
                        "һ�����ڶ���\n", environment(me), me);
                break;
        case 1:
                message("vision", me->name() + "�߶����ɧ��"
                        "Ū�ˣ�������ģ��Ů�ˡ�\n", environment(me), me);
                break;
        case 2:
                message("vision", me->name() + "�߶���߰���"
                        "��Ť��Ťȥ����Ϊ���졣\n", environment(me), me);
                break;
        }

        if ((int)me->query("jing") < 60)
        {
                write("�����ڹ���ƣ�룬�޷�ר�������ж���֪��\n");
                return 1;
        }

        plvl = me->query_skill("pixie-jian", 1);
        if (plvl > 165) neili_lost = 100; else
        if (plvl > 150) neili_lost = 60;  else
        if (plvl > 120) neili_lost = 40;  else
        if (plvl > 100) neili_lost = 30;  else
        if (plvl > 50)  neili_lost = 20;
                   else neili_lost = 10;

        con = me->query_con();

        if ((int)me->query("neili") < neili_lost)
        {
                write("�������������޷�������ô������书��\n");
                return 1;
        }

        if (! me->can_improve_skill("pixie-jian", 1))
        {
                write("���ʵս���鲻�㣬����ô��Ҳû�á�\n");
                return 1;
        }

        if ((plvl > 10) && (con / 2 + random(con) < 50) && random(100) == 1)
        {
                tell_object(me, HIR "�������ű�����ʾ��ת��Ϣ��ͻ"
                                "Ȼֻ����Ϣ�������ϣ���֫�������Ļ���\n"
                                "�٣��Һ�һ�������˹�ȥ��\n" NOR);
                message("vision", HIR + me->name() + "ͻȻ��"
                                  "��һ�������˹�ȥ��\n" NOR,
                        environment(me), ({ me }));

                if ((int)me->query("max_neili") > 10)
                {
                        me->add("max_neili", -10 - random(10));
                }

                me->unconcious();
		return 1;
        }

        me->receive_damage("jing", random(30) + 30);
        me->add("neili", -neili_lost);
        me->improve_skill("pixie-jian", 10 + random(30));
        me->start_busy(random(1) + 1);
        write("���ж����������䡷�������ĵá�\n");
        return 1;
}
