// zazhi.c
#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIG "〖地狱〗杂志第五期总目录" NOR, ({ "zazhi mulu","zazhi","mulu" }));
	set_weight(100);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "册");
		set("long",HIW 
"这是2000年第五期"HIG"〖地狱〗"HIW"杂志的目录清单，你可以(kankan mulu)
从而可以从上面了解到本期"HIG"〖地狱〗"HIW"杂志的大概内容。阅读本期杂志详
细内容请到http://www.cnnetgame.com/hell/hell.htm"HIG"〖地狱〗"HIW"杂志社总部。\n" NOR);
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
                                    "技巧和指导: 打木人时潜能满后该怎么做Trigger  自动画地图机器人  \n"
                                   " 玩家心声 ：《我的一篇文章》 《不谈政治，因为我不愿懂政治？》  \n"
                                   "【终极地狱】技术白皮书: 旷古神功--发呆神功  \n"
                                   "\n" NOR);
	}

	return 1;
}
