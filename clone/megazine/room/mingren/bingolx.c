#include <ansi.h>

inherit ITEM;

void create()
{
	set_name(HIW "屠人魔蜡像" NOR, ({ "laxiang bingo", "laxiang","bingo" }));
	set_weight(3000);
	set_max_encumbrance(5000);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "尊");
                set("long",
	         "这是武当派第四代传人「残缺天下-无双剑」屠人魔(bingo)的蜡像。\n"
	         "虽然他本人长得... 有点对不住别人，但从这个蜡像看来还是可以的。\n");
		set("value", 1);
		set("material", "wood");
set("no_get",1);
set("amount",30);
}
setup();
}
