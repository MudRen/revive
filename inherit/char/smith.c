// smith.c

#include <ansi.h>

inherit NPC;
inherit F_DEALER;

string ask_me();
int  do_gu(string arg);
int  do_dapi(string arg);
int  do_cuihuo(string arg);
int  do_repair(string arg);
void reward(object me);

// no create_function: inherit by other NPC

void init()
{
        add_action("do_list", "list");
        add_action("do_buy", "buy");
        add_action("do_gu", "gu");
        add_action("do_dapi", "dapi");
        add_action("do_cuihuo", "cuihuo");
        add_action("do_repair", "repair");
        add_action("do_repair", "xiuli");
}

void setup()
{
        set("inquiry/job",    (: ask_me :));
        set("inquiry/����",   (: ask_me :));
        set("inquiry/repair", "����Ҫ��(repair)��ʲô��");
        set("inquiry/����",   "����Ҫ��(repair)��ʲô��");

        ::setup();
}

string ask_me()
{
        object me = this_player();

        if (me->query("combat_exp") > 50000)
                return "�����ϸ����δ�������˰ɣ�";

        if (me->query("qi") < 50)
                return "�㻹��Ъ����ɣ�Ҫ�ǳ��������ҿɳе�����";

        if (me->query_temp("smith/gu"))
                return "����ķ��䣬����ô��ĥ��(gu)��";

        if (me->query_temp("smith/dapi"))
                return "�������������û��(dapi)��";

        if (me->query_temp("smith/cuihuo"))
                return "�ɻ���ô��͵��������Ҵ��ȥ(cuihuo)��";

        switch(random(3))
        {
        case 0:
                me->set_temp("smith/gu", 1);
                return "�ã�����ҹ�һ�������(gu)��";

        case 1:
                me->set_temp("smith/dapi", 1);
                return "�����ɣ�����Ҵ�һ������(dapi)��";

        case 2:
                me->set_temp("smith/cuihuo", 1);
                return "ȥ���Ұ���Щ�ճ�¯�Ĵ�һ�»�(cuihuo)��";
        }
}

int do_gu(string arg)
{
        object me = this_player();

        if (me->is_busy())
                return notify_fail("��������æ��\n");

        if (! me->query_temp("smith/gu"))
        {
                message_vision("$n��͵͵������ķ�������˼���硣"
                               "������$N��$n��ȵ����������Ҹ�ʲô��\n",
                               this_object(), me);
                return 1;
        }

        message_vision("$n����ķ��ƴ������������$N���˵��˵�ͷ��\n",
                       this_object(), me);
        reward(me);
        return 1;
}

int do_dapi(string arg)
{
        object me = this_player();

        if (me->is_busy())
                return notify_fail("��������æ��\n");

        if (! me->query_temp("smith/dapi"))
        {
                message_vision("$n���𼸿���������������˵ࡣ"
                               "������$N��$n��ȵ������£��Ҹ�ʲô��\n",
                               this_object(), me);
                return 1;
        }

        message_vision("$n���Ŵ��ӶԸճ�¯�Ļ��ȵ����������ô��ţ�"
                        "$N���š���һ��������ȥ��Щ���⡣\n",
                       this_object(), me);
        reward(me);
        return 1;
}

int do_cuihuo(string arg)
{
        object me = this_player();

        if (me->is_busy())
                return notify_fail("��������æ��\n");

        if (! me->query_temp("smith/cuihuo"))
        {
                message_vision("$n�ճ���һ������õ����ӣ�"
                               "������$N��$n��ȵ������£�����Ҹ㻵�ˡ�\n",
                               this_object(), me);
                return 1;
        }

        message_vision("$N����ǯ����һ��������ӣ������ˮ"
                       "�أ����ꡱ��һ��������ð��\n",
                       me);
        reward(me);
        return 1;
}

void reward(object me)
{
        object coin;

        me->delete_temp("smith/gu");
        me->delete_temp("smith/dapi");
        me->delete_temp("smith/cuihuo");

        coin = new("/clone/money/coin");
        coin->set_amount(10 + random(10));
        coin->move(this_object());
        message_vision("$N��$n�������Ǹ���Ĺ�Ǯ��\n",
                       this_object(), me);
        command("give coin to " + me->query("id"));
        if (me->query("combat_exp") < 250)
        {
                me->improve_potential(1);
                me->add("combat_exp", 1 + random(2));
        }
        me->receive_damage("qi", 30 + random(20));
        me->start_busy(3);
}

int do_repair(string arg)
{
        object me;
        object ob;
        mixed  msg;
        int consistence;
        int cost;
        mapping repair;

        if (! arg)
                return 0;

        me = this_player();
        if (! objectp(ob = present(arg, me)))
                return notify_fail("�����Ϻ���û������������\n");

        if (undefinedp(consistence = ob->query("consistence")))
                return notify_fail(ob->name() + "�ƺ�����Ҫ����������ɣ�\n");

        if (consistence >= 100)
                return notify_fail(ob->name() + "�����������������ʲô��\n");

        if (! undefinedp(msg = ob->query("no_repair")))
        {
                if (stringp(msg))
                        write(name() + "�������ҿ������ˡ�\n");
                else
                        write(name() + "����" + msg);
                return 1;
        }

        if (mapp(repair = me->query_temp("pending/repair")) &&
            repair["item"] == ob)
        {
                if (me->is_busy())
                        return notify_fail("��������æ���أ�\n");

                if (MONEY_D->player_pay(me, repair["cost"]) != 1)
                        return 0;

                message_vision("$n��" + ob->name() + "�ݸ���$N��ֻ��$N"
                               "���𹤾ߣ�������������" + ob->name() +
                               "�ú������ޡ�\n", this_object(), me);
                ob->set("consistence", 100);
                message_vision("$N���������ˣ������ְ�" + ob->name() +
                               "������$n��$n���˿���������ͳ���һЩǮ"
                               "�����ʡ�\n", this_object(), me);
                me->start_busy(1 + random(100 - consistence) / 10);
                me->delete_temp("pending/repair");
                return 1;
        }

        cost = (120 - consistence) * ob->query("value") / 480;
        if (cost >= 100000) cost = ((cost - 100000) / 2 + 100000) / 10000 * 10000; else
        if (cost >= 10000)  cost = cost / 1000 * 1000; else
        if (cost >= 1000)   cost = cost / 100 * 100; else
        if (cost >= 100)    cost = cost / 10 * 10;

        msg = "$n�ó�һ" + ob->query("unit") + ob->name() +
              "��$NƳ��һ�ۣ�������Ҫ�޺�����Ҫ" +
              MONEY_D->price_str(cost) + "���С���\n";
        if (me->query("family/family_name") == "���ϻ���" &&
            ob->item_owner() == me->query("id"))
        {
                cost /= 2;
                msg += "$n�������ϣ���������������˼��������ۣ���" +
                       MONEY_D->price_str(cost) + "�ɣ���\n";
        } else
        if (me->query_skill("higgling", 1) >= 30 && cost >= 50)
        {
                cost = cost * 500 / (me->query_skill("higgling", 1) + 500);
                switch (random(5))
                {
                case 0:
                        msg += "$n��������磬�����ҳ����չ���������ϣ����������ۿۣ���\n";
                        break;

                case 1:
                        msg += "$n���������Ǵ��ϰ�����ҵ����˰�����������...��\n";
                        break;

                case 2:
                        msg += "$n��������λ���ã������������ô��... �����ۿ���Σ���\n";
                        break;

                case 3:
                        msg += "$n������̫���ˣ���ʵ��û��ô���ˣ����˵㣬���˵�ͺá���\n";
                        break;

                case 4:
                        msg += "$n�������Ҽ��ޣ������ɣ��´���һ�����㣬��������и��ã����˵�ɡ���\n";
                        break;
                }

                if (cost >= 1000)
                        cost = cost / 100 * 100;
                else
                        cost = cost / 10 * 10;
                msg += "$N���ʼ���������ˣ����ˣ��Ǿ�" +
                       MONEY_D->price_str(cost) +
                      "���ˡ���\n";
        }

        message_vision(msg, this_object(), me);        
        tell_object(me, YEL "������ȷ�����������Ʒ����������һ���������\n" NOR);
        me->set_temp("pending/repair/item", ob);
        me->set_temp("pending/repair/cost", cost);
        return 1;
}
