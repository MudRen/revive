inherit ITEM;
#include <ansi.h>
string qd="法国";//球队名
int peis=1,peig=0;
//比赛后UPDATE文件

void create()
{
        set_name(HIC"赌球卡A-法国"NOR, ({ "fr ka","ka", }));
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "张");
                set("long",HIY 
       "这张赌球卡上面写着:" + qd + "赢\n"
        "价值：10 cash 赔率:" + peis + "." + peig +"\n"
        "使用说明：请在明日中午12点后使用(changeka)换得兑换支票的B卡\n"
        "如果在此前换卡，将不能兑换，其后果自己负责。\n"  NOR
       );
                set("value", 1000000);
                set("material", "silk");
                set("no_sell",1);
                set("no_pawn",1);
        }
}

void init()
{
	if(this_player() == environment() )
	{
		add_action("do_changeka","changeka");	
	}
}

int do_changeka()
{
	object ob=this_object();
	object me=this_player();
	object qk;
        qk=new("/clone/megazine/obj/duka_22b");
	qk->move(me);
	message_vision(HIC "$N把赌球卡换了。\n" NOR,me);
	destruct(ob);
	return 1;
}

int query_autoload() { return 1; }
