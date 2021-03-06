// SN:[M`Hhiemof9DL_n;
// ITEM Made by player(微尘:doing) /data/item/d/doing-hands.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Fri Mar  2 16:17:02 2001
#include <ansi.h>
#include <armor.h>

inherit HANDS;
inherit F_ITEMMAKE;

void create()
{
	set_name(HIB "无常勾魂魔掌" NOR, ({ "hands" }));
	set_weight(2700);
	set("item_make", 1);
	set("unit", "双");
	set("long", HIB "这是地藏王凝结地府众神之法力炼制的宝物，乃地府无上法宝。是黑白无\n"
                    "常亲自出马擒拿凶悍孤魂野鬼时使用的神器。\n" NOR);
	set("value", 1);
	set("point", 190);
	set("material", "magic stone");
	set("wear_msg", HIB "$N" HIB "伸手一指，两团诡秘的青烟笼罩了双手，渐渐凝结成$n" HIB "，令人一阵心悸。\n" NOR);
	set("remove_msg", HIB "$N" HIB "手上的$n" HIB "忽然化作一道青烟，就此消失，众人登时觉得心头犹如大石落地，轻松不少。\n" NOR);
	if (! check_clone()) return;
	restore();
	set("armor_prop/armor", 10);
	set("armor_prop/hand", 10);
	set("armor_prop/unarmed_damage", apply_damage());
	set("armor_prop/strike", 10);

	setup();
}

void init()
{
        add_action("do_pat", "pat");
}

int do_pat(string arg)
{
        object me;
        object ob;
        object mask;

        me = this_player();
        if (! query("equipped") || me != environment())
                return 0;

        if (! arg) return 0;
        if (! objectp(ob = present(arg, environment(me))) ||
            ! me->visible(ob))
                return notify_fail("你要对谁施展法力？\n");

        if (ob == me)
                return notify_fail("你有毛病啊？\n");

        if (! ob->is_ghost())
                return notify_fail("你只能对鬼魂施展法力。\n");

        if (environment(ob) == find_object("/d/death/gate"))
                return notify_fail("此人正在地府等候发落呢。\n");

        if (wiz_level(me) < 1 || wiz_level(ob) > wiz_level(me))
        {
                message_vision("$N拍了拍$n，好像没啥反应。\n", me, ob);
                return 1;
        }

        message_vision(HIB "$N" HIB "一掌拍向$n" HIB "，只见一阵青烟过后，$n"
                       HIB "消失的无影无踪。\n" NOR, me, ob);
        ob->move("/d/death/gate");
        message("vision", "只听惨叫连连，" + ob->name() + "摔了进来。\n",
                environment(ob), ob);
        
        return 1;
}

string long() { return query("long") + item_long(); }
