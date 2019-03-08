// score.c

#include <ansi.h>
#include <combat.h>

inherit F_CLEAN_UP;

string bar_string = "��������������������������������������������������";
string blank_string = "��������������������������������������������������";

string display_attr(int gift, int value);
string status_color(int current, int max);
string date_string(int date);
string tribar_graph(int val, int eff, int max, string color);

mapping oprank = ([
        "��ʦ"     : HIW "������",
        "�Ƿ��켫" : HIY "������",
        "��������" : HIY "�����  ",
        "��������" : HIR "�����  ",
        "¯����" : HIR "����    ",
        "���д��" : HIC "����    ",
        "��ͬ����" : HIC "���      ",
        "�������" : HIG "���      ",
        "���ֲ���" : HIG "��        ",
        "����С��" : HIM "��        ",
]);

void create() { seteuid(ROOT_UID); }

int main(object me, string arg)
{
	object ob;
	mapping my;
        mapping mci;
        int age, month;
	string line, str, skill_type;
	object weapon;
	int attack_points, dodge_points, parry_points;

	seteuid(getuid(me));

	if (! arg)
		ob = me;
	else if (wizardp(me))
        {
		ob = present(arg, environment(me));
		if (! ob || ! ob->is_character()) ob = find_player(arg);
		if (! ob || ! ob->is_character()) ob = find_living(arg);
		if (! ob || ! ob->is_character())
                        return notify_fail("��Ҫ�쿴˭��״̬��\n");
	} else
		return notify_fail("ֻ����ʦ�ܲ쿴���˵�״̬��\n");

	my = ob->query_entire_dbase();
        mci = my["combat"];
        if (! mci) mci = ([ ]);

        if (playerp(ob) && (! stringp(my["born"]) || ! my["born"]))
                return notify_fail("��û�г����ţ��쿴ʲô��\n");

        if (my["max_jing"] < 1 || my["max_qi"] < 1)
                return notify_fail("�޷��쿴" + ob->name(1) + "��״̬��\n");

	line = sprintf( BOLD "%s" NOR "%s\n\n", RANK_D->query_rank(ob), ob->short(1) );
	if (playerp(ob))
        {
                age = ob->query("age");
                month = ob->query("mud_age");
                if (age >= 60)
                {
                        month -= (age - 60) * 86400 * 4;
                        month = (month - 118 * 86400) / 7200 / 4 + 1;
                } else
                if (age >= 30)
                {
                        month -= (age - 30) * 86400 * 3;
                        month = (month - 28 * 86400) / 7200 / 3 + 1;
                } else
                if (age >= 18)
                {
                        month -= (age - 18) * 86400 * 2;
                        month = (month - 4 * 86400) / 7200 / 2 + 1;
                } else
                {
                        month -= (age - 14) * 86400;
                        month = month / 7200 + 1;
                }

                // not show invalid month
                if (month > 12 || month < 1)
                        month = 1;

        	line += sprintf(WHT " ����һ%s%s��%s���µ�%s%s��%s����\n",
        		ob->query("unit"),
        		chinese_number(age), 
        		chinese_number(month), 
        		ob->query("gender"),
        		ob->query("race"),
        		CHINESE_D->chinese_date(ob->query("birthday")));
        }
	else
	line += sprintf(WHT " ����һ%s%s���%s%s��%s����\n",
		ob->query("unit"),
		chinese_number(ob->query("age")), 
		ob->query("gender"),
		ob->query("race"),
		CHINESE_D->chinese_date(ob->query("birthday")));

	line += sprintf(
		WHT " ������[%s]  ���ԣ�[%s]  ���ǣ�[%s]  ����[%s]\n\n", 
		display_attr(my["str"], ob->query_str()) + WHT,
		display_attr(my["int"], ob->query_int()) + WHT,
		display_attr(my["con"], ob->query_con()) + WHT,
		display_attr(my["dex"], ob->query_dex()) + WHT);
	if (playerp(ob))
	{
                if (my["born_family"] && my["born_family"] != "û��")
		{
                        line += HIW " �������" + my["born_family"] +
				"������" + my["character"];
                } else
                if (stringp(my["born"]) && my["born"])
		{
                        line += HIW " ����" + my["born"] +
				"������" + my["character"];
                } else
                        line += HIW " ����δ����";

		if (mapp(my["family"])) {
			if (my["family"]["master_name"])
				line += sprintf("��ʦ����%s��\n" NOR,
					        my["family"]["master_name"]);
                        else
                                line += "����û��ʦ����\n" NOR;
		} else
                        line += "����û�а�ʦ��\n" NOR;

		if ((int)ob->query("balance") > 0)
			line += HIY " ��Ŀǰ�Ĵ�" + MONEY_D->money_str((int)ob->query("balance")) + "��\n" NOR;
		else
			line += HIY " ��Ŀǰû�д�\n" NOR;

		if (! ob->query("couple/name"))
		{
			if (ob->query("gender") == "Ů��")
				line += HIC " ����δ���䡣\n" NOR;
			else
			        line += HIC " ����δȢ�ޡ�\n" NOR;
		}
		else
			line += HIC " ��İ�����" + ob->query("couple/name") + "(" +
                                ob->query("couple/id") + ")��\n" NOR;

                if (! (int)ob->query("sex/times"))
                {
                        if (ob->query("gender") == "Ů��")
                                line += HIG " �㻹�Ǵ�Ů��\n" NOR;
                        else
                                line += HIC " �㻹��ͯ�С�\n" NOR;
                } else
                {
                        string *ks;

                        ks = keys(ob->query("sex"));
                        ks -= ({ "times", "first", "" });
                        if (sizeof(ks) >= 10)
                                line += HIW " ����������������˷�������ϵ�����"
                                        "���Լ���������˭�ˡ�\n" NOR;
                        else
                                line += HIW " ��������" + implode(ks, HIW "��") +
                                        HIW "��������ϵ��\n" NOR;
                }

                line += "\n";
	}

	line += WHT " <��>  " + tribar_graph(my["jing"], my["eff_jing"], my["max_jing"], GRN) + "\n";
	line += WHT " <��>  " + tribar_graph(my["qi"], my["eff_qi"], my["max_qi"], HIR) + "\n";

	if (objectp(weapon = ob->query_temp("weapon")))
        {
		skill_type = weapon->query("skill_type");
                attack_points = COMBAT_D->skill_power(ob, skill_type, SKILL_USAGE_ATTACK);
	} else
        {
                mapping prepare;
                string *sk;

                prepare = me->query_skill_prepare();
                if (!prepare) prepare = ([]);
                sk = keys(prepare);
        
                if ( sizeof(sk) == 0 ) skill_type = "unarmed"; else
                                       skill_type = sk[0];
                attack_points = COMBAT_D->skill_power(ob, skill_type, SKILL_USAGE_ATTACK);
                if ( sizeof(prepare) == 2 )
                {
                        int temp;
                        temp = COMBAT_D->skill_power(ob, sk[1], SKILL_USAGE_ATTACK);
                        if (attack_points < temp) attack_points = temp;
                }
        }

	parry_points = COMBAT_D->skill_power(ob, "parry", SKILL_USAGE_DEFENSE);
	dodge_points = COMBAT_D->skill_power(ob, "dodge", SKILL_USAGE_DEFENSE);

        if (wizardp(me))
        {
	        line += sprintf(WHT "\n ս�������� " HIW "%8d" NOR WHT "\t\tս�������� " HIW "%8d\n" NOR,
		        attack_points/100 + 1, (dodge_points + (weapon? parry_points: (parry_points/10)))/100 + 1,);
	        line += sprintf(WHT " ս���˺��� " HIW "%8d" NOR WHT "\t\tս�������� " HIW "%8d\n" NOR,
		        weapon ? ob->query_temp("apply/damage")
                               : ob->query_temp("apply/unarmed_damage"),
                        ob->query_temp("apply/armor"));
	}
        line += "\n";

	line += WHT " ʳ�" + tribar_graph(my["food"], ob->max_food_capacity(), ob->max_food_capacity(), YEL) + "\n";
	line += WHT " ��ˮ��" + tribar_graph(my["water"], ob->max_water_capacity(), ob->max_water_capacity(), CYN) + "\n";

        if (! ((int)mci["MKS"] + (int)mci["PKS"]))
        {
                line += HIY "\n �㵽ĿǰΪֹ��δ��ɱ�䡣\n";
        } else
        {
                line += sprintf(HIR "\n ���ܹ�ɱ��%s����", chinese_number(mci["MKS"] + mci["PKS"]));
                if ((int)mci["PKS"])
                {
                        line += "������" + chinese_number(mci["PKS"]) + "�������";
                        if ((int)mci["WPK"] >= (int)mci["PKS"])
                        {
                                mci["WPK"] = (int)mci["PKS"];
                                line += "��ȫ����������ɱ���ġ�\n";
                        } else
                        if ((int)mci["WPK"])
                        {
                                line += "��" + chinese_number(mci["WPK"]) +
                                        "����������ɱ���ġ�\n";
                        } else
                                line += "�����Ƕ���������ɱ���ġ�\n";
                }
                else
                        line += "��\n";
        }
        if ((int)mci["DPS"])
        {
                line += sprintf(HIR "\n ���ܹ�������%s�����", chinese_number(mci["DPS"]));
                if ((int)mci["DPS_GOOD"] >= (int)mci["DPS"])
                        line += "������ȫ������������ʿ";
                else
                {
                        if ((int)mci["DPS_GOOD"])
                                line += "������" + chinese_number(mci["DPS_GOOD"]) + "����������ʿ";

                        if ((int)mci["DPS_BAD"] >= (int)mci["DPS"])
                                line += "������ȫ������а����ʿ";
                        else
                        if ((int)mci["DPS_BAD"])
                                line += "��" + ((int)mci["DPS_GOOD"] ? "" : "����") +
                                        chinese_number(mci["DPS_BAD"]) + "����а����ʿ";
                }
                line += "��\n";
        }
        line += "\n" NOR;

        if ((int)mci["dietimes"])
        {
	        line += sprintf(HIR " �㵽ĿǰΪֹ�ܹ����ڰ��޳�����"
				"����%s�Ρ�\n" NOR,
				chinese_number(mci["dietimes"]));
		if (stringp(mci["last_die"]))
			line += sprintf(HIR " �����һ����%s��\n" NOR,
					mci["last_die"]);
		line += "\n";
        }

        while (playerp(ob))
        {
                string op;
                if (ultrap(ob))
                {
                        line += HIC " �������Ѿ���Ϊ��ѧ����ʦ��\n\n" NOR;
                        break;
                }

                line += WHT " ȭ�Ź���" NOR;
                if (op = ob->query("opinion/unarmed"))
                        line += oprank[op] + "        ";
                else
                        line += CYN "������            ";

                line += NOR WHT "    �������ã�" NOR;
                if (op = ob->query("opinion/weapon"))
                        line += oprank[op] + "        ";
                else
                        line += CYN "������";

                line += NOR WHT "\n �ڼҹ���" NOR;
                if (op = ob->query("opinion/force"))
                        line += oprank[op] + "        ";
                else
                        line += CYN "������            ";

                line += NOR WHT "    ������" NOR;
                if (op = ob->query("opinion/dodge"))
                        line += oprank[op] + "        ";
                else
                        line += CYN "������";

                line += "\n\n" NOR;
                break;
        }

        if (my["breakup"])
        {
                line += HIY " ���Ѿ���ͨ���ζ�����";
                if (my["animaout"])
                        line += "���޳���ԪӤ����";
                line += "�����Կ�����������ѧ���硣\n\n";
        }

	line += sprintf(WHT " ʵս���飺 " HIM "%8d\t\t" NOR, my["combat_exp"]);
	line += sprintf(WHT " ʵս��᣺ %s%8d\n" NOR,
                        my["combat_exp"] < 100000 ? HIR :
                        my["experience"] < ob->query_experience_limit() ? HIY : HIM,
                        (my["experience"] - my["learned_experience"]));
	if (playerp(ob))
        {
                line += sprintf(WHT " ���������� " HIC "%8d\t\t" NOR, my["score"]);
	        line += sprintf(WHT " ���������� " HIC "%8d\n" NOR, my["weiwang"]);
        }
	if (my["shen"] >=0)
		line += sprintf(WHT " ��    ���� " WHT "%8d\t\t" NOR, my["shen"]);
	else
		line += sprintf(WHT " а    ���� " RED "%8d\t\t" NOR, -ob->query("shen"));
	line += sprintf(HIW " ��    ���� " HIR "%8d\n" NOR, my["total_hatred"]);

	write(line);
	return 1;
}

string display_attr(int gift, int value)
{
	if( value > gift ) return sprintf( HIY "%3d" NOR, value );
	else if( value < gift ) return sprintf( CYN "%3d" NOR, value );
	else return sprintf("%3d", value);
}

string status_color(int current, int max)
{
	int percent;

	if (max) percent = current * 100 / max;
	else percent = 100;

	if (percent > 100) return HIC;
	if (percent >= 90) return HIG;
	if (percent >= 60) return HIY;
	if (percent >= 30) return YEL;
	if (percent >= 10) return HIR;
	return RED;
}

string tribar_graph(int val, int eff, int max, string color)
{
	return color + bar_string[0..(val * 25 / max) * 2 - 1]
		+ ((eff > val) ? blank_string[(val * 25 / max) * 2..(eff * 25 / max) * 2 - 1] : "") + NOR;
}

int help(object me)
{
	write(@HELP
ָ���ʽ : score
           score <��������>                   (��ʦר��)

���ָ�������ʾ��(��)��ָ������(������)�Ļ������ϡ�
�������ϵ��趨����� 'help setup'��

see also : hp
HELP );
    return 1;
}
