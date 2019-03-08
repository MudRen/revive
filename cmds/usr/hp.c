// hp cmds (Mon  09-04-95)
// Update by Doing
 
#include <ansi.h>
 
inherit F_CLEAN_UP;

string status_color(int current, int max);
 
int main(object me, string arg)
{
	object ob;
	mapping my;

        string sp;
        int craze;
        int pro;
 
	seteuid(getuid(me));
 
	if (! arg)
		ob = me;
	else
        if (wizardp(me))
        {
		ob = present(arg, environment(me));
		if (! ob || ! ob->is_character()) ob = find_player(arg);
		if (! ob || ! ob->is_character()) ob = find_living(arg);
                if (! ob || ! ob->is_character())
                        return notify_fail("你要察看谁的状态？\n");
	} else
		return notify_fail("只有巫师能察看别人的状态。\n");
 
	my = ob->query_entire_dbase();

        if (userp(ob) && (! stringp(my["born"]) || ! my["born"]))
                return notify_fail("还没有出生呐，察看什么？\n");

        if (my["max_jing"] < 1 || my["max_qi"] < 1)
                return notify_fail("无法察看" + ob->name(1) + "的状态。\n");

        sp  = sprintf(HIC"≡"HIY"──────────────────────────────"HIC"≡\n");
        sp += sprintf(HIC"【 精 气 】 %s%5d/ %5d %s(%3d%%)" HIC "    【 精 力 】 %s%5d / %5d (+%d)\n",
		status_color(my["jing"], my["eff_jing"]), my["jing"], my["eff_jing"],
		status_color(my["eff_jing"], my["max_jing"]),	my["eff_jing"] * 100 / my["max_jing"],
		status_color(my["jingli"], my["max_jingli"]),	my["jingli"], my["max_jingli"],
		my["jiajing"] );
        sp += sprintf(HIC"【 气 血 】 %s%5d/ %5d %s(%3d%%)" HIC "    【 内 力 】 %s%5d / %5d (+%d)\n",
		status_color(my["qi"], my["eff_qi"]), my["qi"], my["eff_qi"],
		status_color(my["eff_qi"], my["max_qi"]), my["eff_qi"] * 100 / my["max_qi"],
		status_color(my["neili"], my["max_neili"]), my["neili"], my["max_neili"],
		my["jiali"] );
        sp += sprintf(HIW"【 食 物 】 %s%5d/ %5d      " HIW "     【 潜 能 】  %s%d\n",
                status_color(my["food"], ob->max_food_capacity()),
                my["food"], ob->max_food_capacity(),
	        (int)ob->query("potential")>=(int)ob->query_potential_limit()?HIM:HIY,
                (int)ob->query("potential") - (int)ob->query("learned_points"));
        sp += sprintf(HIW"【 饮 水 】 %s%5d/ %5d      " HIW "     【 经 验 】  %s%d\n",
                status_color(my["water"], ob->max_water_capacity()),
                my["water"], ob->max_water_capacity(),
                HIM,
                my["combat_exp"] );

        if (craze = ob->query_craze())
        {
                if (ob->is_most_craze())
                        sp += HIR "【 愤 " BLINK "怒" NOR HIR " 】  " +
                              sprintf("%-22s", ob->query("character") == "光明磊落" ? "竖发冲冠"
                                                                                    : "怒火中烧");
                else
                        sp += sprintf(HIR "【 愤 怒 】 %5d/ %5d (+%-3d)    ",
                                      craze, ob->query_max_craze(),
                                      ob->query("jianu"));
        } else
        {
                sp += HIC "【 平 和 】  ─────────    ";
        }

        sp += sprintf(HIM "【 灵 慧 】  " HIY "%d\n", my["magic_points"] - my["magic_learned"]);

        sp += sprintf(HIC"≡"HIY"──────────────────────────────"HIC"≡\n"NOR);
        tell_object(me, sp);
	return 1;
}
 
string status_color(int current, int max)
{
	int percent;
 
	if (max>0 ) percent = current * 100 / max;
	else percent = 100;
	if (percent > 100) return HIC;
	if (percent >= 90) return HIG;
	if (percent >= 60) return HIY;
	if (percent >= 30) return YEL;
	if (percent >= 10) return HIR;
	return RED;
}
 
int help(object me)
{
	write(@HELP
指令格式 : hp
           hp <对象名称>                   (巫师专用)
 
这个指令可以显示你(你)或指定对象(含怪物)的精, 气, 神数值。
 
see also : score
HELP );
    return 1;
}
