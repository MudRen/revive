#include <ansi.h>

inherit NPC;
inherit F_DEALER;

void create()
{
         set_name("赌球卡小姐", ({ "duqiu xiaojie","xiaojie","duqiu"}) );
       set("title",HIW "〖地狱〗杂志社" NOR);
        set("gender", "女性" );
	set("age", 21);
	set("long",
                "这是一位的美丽赌球卡小姐，赌球卡10 cash 一张。\n");
	set("combat_exp", 100);
	set("attitude", "friendly");
	set("rank_info/respect", "小姐");
       set("inquiry", ([ 
"zazhi": "这是我们提供给玩家的〖地狱〗杂志。\n",
"地狱杂志": "这是我们提供给玩家的〖地狱〗杂志。\n",
"风狐": "这个都不知道,你是不是人啊,他就是我们尊敬的社长啊!\n",
"wfoxd": "这个都不知道,你是不是人啊,他就是我们尊敬的社长啊!\n",
]) );
       set("chat_chance", 10);
       set("chat_msg", ({
"派送小姐说道：我们的〖地狱〗杂志就是好，推出就得到了大家的认可。\n"
"派送小姐对你说道：你没看过〖地狱〗杂志吗？那就太可惜了! \n",
"派送小姐把手上的〖地狱〗杂志整理了一下。\n",
}) );
	setup ();
            carry_object("clone/cloth/female5-cloth")->wear();
       
}

int accept_object(object me, object ob)
{
        object ling;
        
        command("smile");
        command("say 这位" + RANK_D->query_respect(me) + "谢谢你啦 ！");
        if( ob->query("money_id") && ob->value() >= 100 && me->query("class") != "bonze" ) 
        {
                command("say " + RANK_D->query_respect(me) + 
                "这是你的杂志。");
                ling=new("/clone/megazine/obj/zazhi2");
                ling->move(me);
                message_vision("发送小姐给$N一本"HIG"〖地狱〗杂志"NOR"。\n", me);

                command("say 此杂志两个星期出一期，请注意下一期的出版日期！"); 
                return 1;
        }

        return 1;
}
