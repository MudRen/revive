// SN:ZThk9XGo=Y\?Sj]9
// ITEM Made by player(微尘:doing) /data/item/d/doing-cloth.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Fri Mar  2 15:56:19 2001
#include <ansi.h>
#include <armor.h>

inherit CLOTH;
inherit F_ITEMMAKE;

void create()
{
	set_name(HIY "南山虎纹披风" NOR, ({ "cloth" }));
	set_weight(1400);
	set("item_make", 1);
	set("unit", "件");
	set("long", HIY "据称这是用武松打死那只老虎的皮缝制的披风，不过据行家曾柔分析，此\n"
                    "乃十足的假冒货色，是微尘做的几大赔本买卖之一，为此微尘决定加大搜\n"
                    "刮力度，将地狱中的富人统统变成穷光蛋。\n" NOR);
	set("value", 1);
	set("point", 190);
	set("material", "silk");
	set("wear_msg", HIY "$N" HIY "披上了$n" HIY "。\n" NOR);
	set("remove_msg", HIY "$N" HIY "脱下了$n" HIY "，叹了一口气。\n" NOR);
	if (! check_clone()) return;
	restore();
	set("armor_prop/armor", apply_armor());

	setup();
}

string long() { return query("long") + item_long(); }
