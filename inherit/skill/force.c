// force.c

#include <ansi.h>

inherit SKILL;

int valid_learn(object me)
{
    	if ((int)me->query_skill("force", 1) < 10)
        	return notify_fail("��Ļ����ڹ���򲻹�������ѧϰ�����ڹ���\n");

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
                                result += ([ "msg" : HIY "$N" HIY "�ܵ�$n"
                                                     HIY "�����������ƺ�һ����\n" NOR ]);
			else if (damage < 20)
                                result += ([ "msg" : YEL "$N" YEL "��$n"
                                                     YEL "���������𣬡��١���һ������������\n" NOR ]);
			else if (damage < 40)
                                result += ([ "msg" : HIC "$N" HIC "��$n"
                                                     HIC "������һ���ؿ������ܵ�һ���ش�����������������\n" NOR ]);
			else if (damage < 80)
                                result += ([ "msg" : HIR "$N" HIR "��$n"
                                                     HIR "������һ����ǰһ�ڣ��������ɳ�������\n" NOR ]);
                        else
                                result += ([ "msg" : RED "$N" RED "��$n"
                                                     RED "������һ��ֻ�����������ϣ���Ѫ�������������˹�ȥ��\n" NOR ]);
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
                write(HIY "��ֻ������Ѫ����������֮�������嵴��\n" NOR);
        else
        if (hatred < 5 * force)
                write(HIR "��ֻ����Ѫ�����ţ�����ɱ������������һʱ�̲�סֻ����������\n" NOR);
        else
        if (hatred < 6 * force)
        {
                write(HIR "����ͷһʹ����Ϣ�������Ʋ�ס��ֻ������ǰ������ð��\n" NOR);
                return 1;
        } else
        {
                write(RED "һʱ����ֻ����ɱ���󳤣��������գ��������³嵴���������������\n"
                          "��ҡҡ�λ�ǿ֧Ƭ�̣�ɤ��һ����ǰ��ʱ����һ�ڣ������ˡ�һ�µ��ڵ��ϡ�\n" NOR);
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

        me->set_temp("die_reason", "ɱ¾̫�أ��������Ķ���");
        me->die();
        me->set("total_hatred", me->query("total_hatred") / 2);
}

// can I exercise force?
int do_effect(object me)
{
        return shaolin_check(me) || hatred_check(me);
}
