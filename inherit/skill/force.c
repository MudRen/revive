// force.c

#include <ansi.h>

inherit SKILL;

int valid_learn(object me)
{
    	if ((int)me->query_skill("force", 1) < 10)
        	return notify_fail("你的基本内功火候不够，不能学习特殊内功。\n");

    	return 1;
}

// hit effect called by combatd
mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
	int damage;
        int me_fac;
        int victim_fac;
        int f;
        int m_lvl;
        int v_lvl;
        string skill;
        mixed result;

        skill = victim->query_skill_mapped("force");
        if (stringp(skill))
        {
                if (result = SKILL_D(skill)->valid_damage(me, victim, damage_bonus))
                        return result;
        }

        me_fac = (int)me->query("neili");
        if (me_fac > (int)me->query("max_neili"))
                me_fac = (int)me->query("max_neili");

        victim_fac = (int)victim->query("neili");
        if (victim_fac > (int)victim->query("max_neili"))
                victim_fac = (int)victim->query("max_neili");

        if ((int)me->query("combat_exp") < (int)victim->query("combat_exp") * 20)
	        me->add("neili", -factor);

	damage = me_fac / 20 + factor - victim_fac / 24;

	if (damage < 0)
        {
                v_lvl = victim->query_skill("force");
                m_lvl = me->query_skill("force");
		if (! me->query_temp("weapon") &&
		    m_lvl + random(m_lvl / 3) < v_lvl)
                {
                        result = ([ "damage" : damage * 2 ]);
                        damage = -damage;
			me->receive_damage("qi", damage * 4, victim);
			me->receive_wound("qi", damage * 4, victim);
			if (damage < 10)
                                result += ([ "msg" : HIY "$N" HIY "受到$n"
                                                     HIY "的内力反震，闷哼一声。\n" NOR ]);
			else if (damage < 20)
                                result += ([ "msg" : YEL "$N" YEL "被$n"
                                                     YEL "以内力反震，「嘿」地一声退了两步。\n" NOR ]);
			else if (damage < 40)
                                result += ([ "msg" : HIC "$N" HIC "被$n"
                                                     HIC "以内力一震，胸口有如受到一记重锤，连退了五六步！\n" NOR ]);
			else if (damage < 80)
                                result += ([ "msg" : HIR "$N" HIR "被$n"
                                                     HIR "的内力一震，眼前一黑，身子向后飞出丈许！！\n" NOR ]);
                        else
                                result += ([ "msg" : RED "$N" RED "被$n"
                                                     RED "的内力一震，只觉浑身经脉欲断，气血倒流，几乎晕了过去。\n" NOR ]);
                        return result;
		}

		return 0;
	}

	damage -= victim->query_temp("apply/armor_vs_force");
	if (damage_bonus + damage < 0)
                return - damage_bonus;
	if ((f = random(me->query_skill("force"))) < damage)
		return f;

        return damage;
}

int shaolin_check(object me)
{
        // disable by doing
}

int hatred_check(object me)
{
        int hatred;
        int force;
        int i;

        hatred = me->query("total_hatred");
        force = me->query_skill("force");
        if (hatred < 3 * force)
                return 0;
        else
        if (hatred < 4 * force)
                write(HIY "你只觉得心血潮动，经脉之间真气冲荡。\n" NOR);
        else
        if (hatred < 5 * force)
                write(HIR "你只觉得血脉贲张，浑身杀气蠢蠢欲动，一时忍不住只想放声大呼。\n" NOR);
        else
        if (hatred < 6 * force)
        {
                write(HIR "你心头一痛，内息几欲控制不住，只觉得眼前进行乱冒。\n" NOR);
                return 1;
        } else
        {
                write(RED "一时间你只觉得杀气大长，人如狂如痴，真气四下冲荡，几欲破体而出。\n"
                          "你摇摇晃晃强支片刻，嗓眼一甜，眼前登时就是一黑，“咕咚”一下倒在地上。\n" NOR);
                me->unconcious();
                call_out("do_owner_die", 0, me);
                return 1;
        }

        return 0;
}

void do_owner_die(object me)
{
        mapping sk;
        string skill;

        if (! objectp(me))
                return;

        me->receive_damage("qi", 1);
        sk = me->query_skills();
        foreach (skill in keys(sk))
        {
                if (! SKILL_D(skill)->valid_enable("force") ||
                    skill == "force")
                        continue;
                if (sk[skill] > 50)
                        sk[skill] /= 2;
        }

        if (me->query("max_neili") > 500)
                me->set("max_neili", me->query("max_neili") / 2);

        me->set_temp("die_reason", "杀戮太重，郁气填心而死");
        me->die();
        me->set("total_hatred", me->query("total_hatred") / 2);
}

// can I exercise force?
int do_effect(object me)
{
        return shaolin_check(me) || hatred_check(me);
}
