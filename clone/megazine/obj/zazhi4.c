// zazhi.c
#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIG "〖地狱〗杂志第四期总目录" NOR, ({ "zazhi mulu","zazhi","mulu" }));
	set_weight(100);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "册");
		set("long",HIW 
"这是2000年第四期"HIG"〖地狱〗"HIW"杂志的目录清单，你可以(kankan mulu)
从而可以从上面了解到本期"HIG"〖地狱〗"HIW"杂志的大概内容。阅读本期杂志详
细内容请到http://ultrahell.yeah.net"HIG"〖地狱〗"HIW"杂志社总部。\n" NOR);
		set("value", 1);
		set("material", "paper");
              set("no_sell", 1);		              
	}
   setup ();
}

void init()
{
	if( this_player() == environment() )
	{
		add_action("do_kankan", "kankan");
	}
}

int do_kankan(string arg)
{
	object me, magazine;
	
	if ( !arg )
	{
		return notify_fail("什么？\n");
	}

	me = this_player();

	if ( arg == "mulu" )
	{
		tell_object(me,HIW "本期〖地狱〗杂志目录：\n"
                                    "【地狱文曲星】评选活动说明 \n"
                                    "从即日起，凡向〖地狱〗杂志社投稿的作者都有资格成为【地狱文曲星】的后选人。 \n"
                                    "【地狱文曲星】的评选由玩家自己投票选出，〖地狱〗杂志社负责这期间的安排工作。  \n"
                                   "【地狱文曲星】的评选将每两个月进行一次，被评为【地狱文曲星】者可获得【地狱文曲星】的头衔一个，以及200GOLD的奖励。 \n"
                                    "本活动解释权属〖地狱〗杂志社所有。  \n"
                                   "长篇连载：sasamei的文章继续连载，想知道sasamei和kidd后来发生的事请看: \n"
                                   "              《柳长街和沙沙美的故事》（下） \n"
                                   "玩家心声：倾城一剑告别大家的回忆性文章，里面记录了不少地狱以前的事情，新玩家们可不能错过。  \n"
                                   "                   《仗剑走江湖》  \n" NOR);
	}

	return 1;
}
