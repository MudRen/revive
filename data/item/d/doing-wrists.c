// SN:=_?VhY;Bh`QZ8d_?
// ITEM Made by player(微尘:doing) /data/item/d/doing-wrists.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Fri Mar  2 16:05:21 2001
#include <ansi.h>
#include <armor.h>

inherit WRISTS;
inherit F_ITEMMAKE;

void create()
{
	set_name(HIY "玄黄伏羲铁镯" NOR, ({ "wrists" }));
	set_weight(3000);
	set("item_make", 1);
	set("unit", "对");
	set("long", YEL "这是伏羲以玄黄两色之灵石、按易理生死相克之法门炼制的上古神物，可\n"
                    "以辟邪魔，镇妖异。神通巧合天数，能使人陷入无比困惑之地。\n" NOR);
	set("value", 1);
	set("point", 47);
	set("material", "magic stone");
	set("wear_msg", HIY "$N" HIY "伸手一招，只见一黑一黄两只铁环化作二道光芒，缠在$N" HIY "腕上。\n" NOR);
	set("remove_msg", HIY "$N" HIY "轻轻一磕腕上双环，只听叮呤一声响，双环就此不见。\n" NOR);
	if (! check_clone()) return;
	restore();

	setup();
}

void init()
{
        add_action("do_busy", "busy");
}

int do_busy(string arg)
{
        object me;
        object ob;

        me = this_player();
        if (! query("equipped") || me != environment())
                return 0;

        if (! arg) return 0;
        if (! objectp(ob = present(arg, environment(me))) ||
            ! me->visible(ob))
                return notify_fail("你要对谁施展法力？\n");

        if (! intp(ob->query_busy()))
                return notify_fail("这人现在正忙着呢。\n");

        if (ob == me)
                return notify_fail("你有毛病啊？\n");

        if (wiz_level(me) < 1 || wiz_level(ob) > wiz_level(me))
        {
                message_vision("$N抖了抖手腕，啥事也没有发生。\n", me);
                return 1;
        }

        message_vision(HIM "$N" HIM "轻轻一抖手腕，只听" + name() +
                       HIM "叮铃铃发出阵阵异响声，就见\n" +
                       "$n" HIM "应声而走，手舞足蹈，形如梦游。\n" NOR, me, ob);
        ob->start_busy(60);
        return 1;
}

string long() { return query("long") + item_long(); }
