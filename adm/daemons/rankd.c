// rankd.c
// 1996-02-15 dts ranking related to "shen"

#pragma optimize
#pragma save_binary

#include <ansi.h>

string query_rank(object ob)
{
        mapping fam;

        int shen;
        int budd;
        int tao;
        int exp;
        int age;
        int eatman;

        if (ob->is_ghost())
                return HIB "�� ��  �� ��" NOR;

        shen = ob->query("shen");
        exp  = ob->query("exp");
        age  = ob->query("age");
        budd = ob->query_skill("buddhism", 1);
        tao  = ob->query_skill("taoism", 1);
        eatman = ob->query("combat/eatman", 1);

	if (ob->query("rank_info/rank"))
		return HIY "��" + ob->query("rank_info/rank") + "��" NOR;

        switch(ob->query("gender"))
        {
        case "Ů��":
                switch (wizhood(ob))
                {
                case "(admin)":
                        return HIW "�� Ů  �� ��" NOR;
                case "(arch)":
                        return HIY "�� ��  �� ��" NOR;
                case "(wizard)":
                        return HIG "�� ��  �� ��" NOR;
                case "(apprentice)":
                        return HIC "�� С��Ů ��" NOR;
                case "(immortal)":
                        return HIC "�� С��Ů ��" NOR;
                default:
                        if (shen < 0 && eatman >= 10)
                             return RED "�����˿�ħ��" NOR;
                        else
                        if (shen < 0 && eatman >= 3)
                             return RED "��ʳ��Ůħ��" NOR;

                        switch(ob->query("class"))
                        {
                        case "bonze":
                             if (budd >= 150)
                                return HIY "�� ��  �� ��" NOR;
                             if (budd >= 120)
                                return HIY "�� ʥ  �� ��" NOR;
                             if (budd >= 90)
                                return HIY "�� ��  �� ��" NOR;
                             if (budd >= 60)
                                return HIC "�� ��  �� ��" NOR;
                             if (budd >= 30)
                                return HIG "�� ʦ  ̫ ��" NOR;
                             if (age <= 16)
                                return "�� С��� ��";
                             else
                                return "�� ��  �� ��";
                        case "taoist":
                             if (exp > 10000 || shen > 10000 || shen < -10000)
                                break;
                             if (age <= 16)
                                return CYN "�� С���� ��" NOR;
                             else if (age <= 40)
                                return CYN "�� ��  �� ��" NOR;
                             else
                                return CYN "�� �ϵ��� ��" NOR;
                        case "bandit":
                             if (exp > 10000 || shen > 10000 || shen < -10000)
                                break;
                                return HIG "�� Ů���� ��" NOR;
                        case "dancer":
                             if (exp > 10000 || shen > 10000 || shen < -10000)
                                break;
                                return "�� ��  Ů ��";
                        case "scholar":
                             if (exp > 10000 || shen > 10000 || shen < -10000)
                                break;
                             if (age <= 16)
                                return CYN "�� Ůѧͯ ��" NOR;
                             else if (age <= 20)
                                return HIM "�� ��  Ů ��" NOR;
                             else
                                return HIC "�� Ůѧʿ ��" NOR;
                        case "officer":
                             if (exp > 10000 || shen > 10000 || shen < -10000)
                                break;
                                return HIY "�� Ů  �� ��" NOR;
                        case "fighter":
                             if (exp > 10000 || shen > 10000 || shen < -10000)
                                break;
                                return MAG "�� Ů���� ��" NOR;
                        case "swordsman":
                             if (exp > 10000 || shen > 10000 || shen < -10000)
                                break;
                                return WHT "�� Ů��ʿ ��" NOR;
                        case "alchemist":
                             if (exp > 10000 || shen > 10000 || shen < -10000)
                                break;
                                return BLU "�� Ů��ʿ ��" NOR;
                        case "shaman":
                             if (exp > 10000 || shen > 10000 || shen < -10000)
                                break;
                                return HIB "�� Ů��ҽ ��" NOR;
                        case "beggar":
                             if (exp > 10000 || shen > 10000 || shen < -10000)
                                break;
                                return "�� Ů�л� ��";
                        case "prostitute":
                                return HIR "����¥Ů�ӡ�" NOR;
                        }
                        if (shen >= 200000)
                                return HIC "������Ů����" NOR;
                        if (shen >= 50000)
                                return HIW "�� Ů  �� ��" NOR;
                        if (shen >= 10000)
                                return HIM "�� Ů���� ��" NOR;
                        if (shen >= 1000)
                                return HIY "�� С��Ů ��" NOR;
                        if (shen <= -200000)
                                return HIR "������ħŮ��" NOR;
                        if (shen <= -50000)
                                return HIC "�� Ůħͷ ��" NOR;
                        if (shen <= -10000)
                                return HIY "�� ��  Ů ��" NOR;
                        if (shen <= -1000)
                                return HIG "�� С��Ů ��" NOR;

                        if (age <= 20)
                            return "�� ��  Ů ��";
                        else
                            return "�� ��  �� ��";
                }
        default:
                switch (wizhood(ob))
                {
                case "(admin)":
                        return HIW "�� ��  �� ��" NOR;
                case "(arch)":
                        return HIY "�� ��  �� ��" NOR;
                case "(wizard)":
                        return HIG "�� ��  ʦ ��" NOR;
                case "(apprentice)":
                        return HIC "�� С��ʦ ��" NOR;
                case "(immortal)":
                        return HIC "�� ��  �� ��" NOR;
                default:
                        if (shen < 0 && eatman >= 10)
                             return HIR "�����˿�ħ��" NOR;
                        else
                        if (shen < 0 && eatman >= 3)
                             return HIR "�� ʳ��ħ ��" NOR;
                        switch(ob->query("class"))
                        {
                        case "bonze":
                                if (budd >= 250)
                                        return HIY "�����ʥɮ��" NOR;
                                if (budd >= 150)
                                        return HIY "�� ʥ  ɮ ��" NOR;
                                else if (budd >= 120)
                                        return HIY "�� ��  �� ��" NOR;
                                else if (budd >= 90)
                                        return HIY "�� ��  �� ��" NOR;
                                else if (budd >= 60)
                                        return HIY "�� ��  �� ��" NOR;
                                else if (budd >= 40)
                                        return HIY "�� ��  ʦ ��" NOR;
                                else if (budd >= 30)
                                        return HIY "�� ��  �� ��" NOR;
                                else if (age <= 16)
                                        return HIY "�� С���� ��" NOR;
                                else
                                        return "�� ɮ  �� ��";
                        case "taoist":
                                if (tao > 200)
                                        return HIY "�� ��  �� ��" NOR;
                                if (shen < -200000)
                                        return HIY "�� ħ  �� ��" NOR;
                                if (shen < -10000)
                                        return HIY "�� ��  �� ��" NOR;
                                if (shen < -100)
                                        return HIY "�� а  �� ��" NOR;
                                if (age <= 16)
                                        return CYN "�� С��ʿ ��" NOR;
                                if (age <= 30)
                                        return CYN "�� ��  ʿ ��" NOR;

                                return CYN "�� ��  �� ��" NOR;
                        case "bandit":
                                return HIG "�� ��  �� ��" NOR;
                        case "scholar":
                                if (shen > 10000 || shen < -10000)
                                        break;
                                if (age <= 16)
                                        return CYN "�� ѧ  ͯ ��" NOR;
                                else if (age <= 45)
                                        return HIY "�� ��  �� ��" NOR;
                                else
                                        return YEL "�� ����� ��" NOR;
                        case "officer":
                                if (shen > 10000 || shen < -10000)
                                        break;
                                return YEL "�� ��  �� ��" NOR;
                        case "fighter":
                                if (shen > 10000 || shen < -10000)
                                        break;
                                return MAG "�� ��  �� ��" NOR;
                        case "swordsman":
                                if (shen > 10000 || shen < -10000)
                                        break;
                                return WHT "�� ��  ʿ ��" NOR;
                        case "alchemist":
                                if (shen > 10000 || shen < -10000)
                                        break;
                                return BLU "�� ��  ʿ ��" NOR;
                        case "shaman":
                                if (shen > 10000 || shen < -10000)
                                        break;
                                return HIB "�� ��  ҽ ��" NOR;
                        case "beggar":
                                if (shen > 10000 || shen < -10000)
                                        break;
                                if (age <= 16)
                                    return WHT "�� С�л� ��" NOR;
                                else
                                    return WHT "�� �л��� ��" NOR;
                        case "royal":
                                if (shen > 200000 || shen < -200000)
                                        break;
                                return HIY "�� ��  �� ��" NOR;
                        case "prostitute":
                                return HIB "�� ��  �� ��" NOR;
                        }
                        if (shen >= 200000)
                                return HIC "������������" NOR;
                        if (shen >= 50000)
                                return HIW "�� ��  �� ��" NOR;
                        if (shen >= 10000)
                                return HIM "�� ��  �� ��" NOR;
                        if (shen >= 1000)
                                return HIY "�� С  �� ��" NOR;
                        if (shen <= -200000)
                                return HIR "�� ħ  �� ��" NOR;
                        if (shen <= -50000)
                                return HIC "�� ��ħͷ ��" NOR;
                        if (shen <= -10000)
                                return HIY "�� ħ  ͷ ��" NOR;
                        if (shen <= -1000)
                                return HIG "�� С  ħ ��" NOR;

                        if (age <= 20)
                            return "�� ��  �� ��";
                        else
                            return "�� ƽ  �� ��";
                }
        }
}

string query_respect(object ob)
{
        int age;
        string str;

        if (stringp(str = ob->query("rank_info/respect")))
                return str;

        age = ob->query("age");
        switch (ob->query("gender"))
        {
        case "Ů��":
                switch(ob->query("class"))
                {
                case "bonze":
                        if (age < 18) return "Сʦ̫";
                        else return "ʦ̫";
                        break;
                case "taoist":
                        if (age < 18) return "С�ɹ�";
                        else return "�ɹ�";
                        break;
                default:
                        if (age < 18) return "С����";
                        else if (age < 30) return "����";
                        else if (age < 40) return "����";
                        else return "����";
                        break;
                }
        case "����":
        default:
                switch(ob->query("class"))
                {
                case "bonze":
                        if (age < 18) return "Сʦ��";
                        else return "��ʦ";
                        break;
                case "taoist":
                        if (age < 18) return "����";
                        else return "����";
                        break;
                case "scholar":
                        if (age < 18) return "С�๫";
                        else if (age < 50) return "�๫";
                        else return "������";
                        break;
                case "fighter":
                case "swordsman":
                        if (age < 18) return "С�ϵ�";
                        else if (age < 50) return "׳ʿ";
                        else return "��ǰ��";
                        break;
                default:
                        if (age < 20) return "С�ֵ�";
                        else if (age < 50) return "׳ʿ";
                        else return "��ү��";
                        break;
                }
        }
}

string query_rude(object ob)
{
        int age;
        string str;

        if (stringp(str = ob->query("rank_info/rude")))
                return str;

        age = ob->query("age");
        switch (ob->query("gender"))
        {
        case "Ů��":
                switch(ob->query("class"))
                {
                case "bonze":
                        if( age < 18 ) return "С����";
                        if( age < 30 ) return "����";
                        else return "������";
                        break;
                case "taoist":
                        if( age < 18 ) return "С��Ů";
                        if( age < 30 ) return "��Ů";
                        else return "������";
                        break;
                default:
                        if( age < 18 ) return "С��Ƥ";
                        if( age < 25 ) return "С����";
                        if( age < 40 ) return "������";
                        else return "����̫��";
                        break;
                }
        case "����":
        default:
                switch(ob->query("class"))
                {
                case "bonze":
                        if( age < 18 ) return "С��ͺ";
                        if( age < 50 ) return "��ͺ¿";
                        else return "��ͺ¿";
                        break;
                case "taoist":
                        if( age < 18 ) return "С��ë";
                        if( age < 30 ) return "��ţ����";
                        else return "����ë";
                        break;
                case "scholar":
                        if( age < 18 ) return "С�����";
                        else if( age < 50 ) return "�������";
                        else return "��ͯ��";
                        break;
                default:
                        if( age < 20 ) return "С���˵�";
                        if( age < 30 ) return "ֱ����";
                        if( age < 50 ) return "����";
                        if( age < 80 ) return "��ƥ��";
                        else return "�ϲ���";
                        break;
                }
        }
}

string query_self(object ob)
{
        int age;
        string str;

        if (stringp(str = ob->query("rank_info/self")))
                return str;

        age = ob->query("age");
        switch (ob->query("gender"))
        {
        case "Ů��":
                switch(ob->query("class"))
                {
                case "bonze":
                        if( age < 50 ) return "ƶ��";
                        else return "����";
                        break;
                case "taoist":
                        return "ƶ��";
                        break;
                default:
                        if( age < 20 ) return "СŮ��";
                        if( age > 50 ) return "����";
                        else return "���";
                        break;
                }
        case "����":
        default:
                switch(ob->query("class"))
                {
                case "bonze":
                        if( age < 18 ) return "С��";
                        if( age < 40 ) return "ƶɮ";
                        else return "����";
                        break;
                case "taoist":
                        if( age < 18 ) return "С��";
                        if( age < 30 ) return "ƶ��";
                        else return "�ϵ�";
                        break;
                case "scholar":
                        if( age < 30 ) return "����";
                        else return "����";
                        break;
                default:
                        if( age < 50 ) return "����";
                        else return "��ͷ��";
                        break;
                }
        }
}

string query_self_rude(object ob)
{
        int age;
        string str;

        if (stringp(str = ob->query("rank_info/self_rude")))
                return str;

        age = ob->query("age");
        switch(ob->query("gender"))
        {
        case "Ů��":
                switch(ob->query("class"))
                {
                case "bonze":
                        if( age < 50 ) return "ƶ��";
                        else return "����";
                        break;
                case "taoist":
                        return "���ɹ�";
                        break;
                default:
                        if( age < 20 ) return "������";
                        if( age < 30 ) return "��������";
                        else return "����";
                        break;
                }
        case "����":
        default:
                switch(ob->query("class"))
                {
                case "bonze":
                        if( age < 50 ) return "�������";
                        else return "�Ϻ�����";
                        break;
                case "taoist":
                        if( age < 30 ) return "��ɽ��";
                        return "�ϵ���";
                        break;
                case "scholar":
                        if( age < 50 ) return "���๫";
                        else return "�Ϸ�����";
                        break;
                default:
                        if( age < 20 ) return "����ү��";
                        if( age < 40 ) return "��ү��";
                        else return "����";
                        break;
                }
        }
}

varargs string query_close(mixed ob, int a1, int a2)
{
        if (! a1 && this_player())
                a1 = this_player()->query("age");

        if (! a2 && objectp(ob))
                a2 = ob->query("age");

        switch (objectp(ob) ? ob->query("gender") : ob)
        {
        case "Ů��":
                if (a1 >= a2)
                        return "����";
                else
                        return "���";
                break;

        default:
                if (a1 >= a2)
                        return "�ܵ�";
                else
                        return "���";
        }
}

varargs string query_self_close(mixed ob, mixed me, int a1, int a2)
{
        if (! a1 && this_player())
                a1 = this_player()->query("age");

        if (! a2 && objectp(ob))
                a2 = ob->query("age");

        switch (objectp(me) ? me->query("gender") :
                this_player() ? this_player()->query("gender") : me)
        {
        case "Ů��" :
                if (a1 >= a2)
                        return "�����";
                else
                        return "С����";
                break;

        default :
                if (a1 >= a2)
                        return "������";
                else
                        return "С����";
        }
}

