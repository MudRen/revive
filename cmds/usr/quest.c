// quest.c

#include <ansi.h>
 
inherit F_CLEAN_UP;

int main(object me, string arg)
{
        object ob;
        mapping q;
        string master;

        while (arg)
        {
                if (arg == "cancel")
                {
                        if (! stringp(master = me->query("quest/master_id")))
                                return notify_fail("有人向你下任务了吗？\n");

                        if (! objectp(ob = present(master, environment(me))))
                                return notify_fail("给你下任务的那个人现在不在这里吧？\n");
                } else
                if (! objectp(ob = present(arg, environment(me))))
                        return notify_fail("这里没有这个人，你怎么领任务？\n");

                if (! living(ob))
                        return notify_fail("你还是等" + ob->name() +
                                           "醒了再说吧！\n");

                if (me->is_fighting())
                        return notify_fail("专心打你的架！\n");

                if (me->is_busy())
                        return notify_fail("你还是有空了再和" + ob->name() +
                                           "谈这些问题吧！\n");

                if (ob->is_fighting())
                        return notify_fail("你还是等" + ob->name() +
                                           "打完架再说吧！\n");

                if (ob->is_busy())
                        return notify_fail(ob->name() +
                                           "正忙着呢，没功夫理你。\n");

                notify_fail(ob->name() + "望着你呵呵的傻笑。\n");
                return (arg == "cancel" ? ob->cancel_quest(me)
                                        : ob->ask_quest(me));
        }

        if (me->query("quest_count"))
                write(sprintf("师长交给你的任务，你已经连续完成了 %d 个。\n",
                              me->query("quest_count")));
 
        if (! mapp(q =  me->query("quest")))
        {
                write("你现在没有领任何任务！\n");
                return 1;
        }

        switch (q["type"])
        {
        case "kill":
                write(q["master_name"] + "吩咐你在" + CHINESE_D->chinese_monthday(q["limit"]) +
                      "之前割下" HIR + q["name"] + NOR "的人头，回" + q["family"] + "交差。\n" +
                      "据说此人前不久曾经在" + q["place"] + "出没。\n");
                return 1;
        case "letter":
                write(q["master_name"] + "吩咐你在" + CHINESE_D->chinese_monthday(q["limit"]) +
                      "之前把信件送到" HIC + q["name"] + NOR "手中，取回执交差。\n" +
                      "据闻不久前此人曾经在" + q["place"] + "。\n");
                return 1;
        }

        write("你现在没有领任何任务！\n");
        return 1;
}

int help(object me)
{
        write(@HELP
指令格式 : quest  这个指令可以用来向你的门派的掌门或世家长辈
领取任务，如果不加任何参数则显示出你当前的任务。
HELP );
        return 1;
}
