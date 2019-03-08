// suicide.c

#include <ansi.h>

inherit F_CLEAN_UP;

private int slow_suicide(object me);
private int halt_suicide(object me);

int main(object me, string arg)
{
	object *inv;
	int i;
	if (me->is_busy())
		return notify_fail("����һ��������û��ɡ�\n");

        inv = deep_inventory(me);
        for (i = 0; i < sizeof(inv); i++)
	{
                if (! userp(inv[i]) && ! playerp(inv[i])) continue;
		return notify_fail("�����ϻ��и�������أ��벻��Ҳ��ѽ��\n");
        }

	if (! arg)
	{
		write("You commit suicide.\n");
		return 1;
	}

	if (arg != "-f") 
		return notify_fail("��ɱ�����֣�����Ҫ��Զ����(-f)��������Ͷ̥��\n");

	write("��ѡ����Զ��������ɱ��ʽ�������������Ͻ���Զɾ���������\n"
	      "���������ȷ���Ļ����������Ĺ������룺");
	input_to("check_password", 1, me, 1);
	return 1;
}

private void check_password(string passwd, object me, int forever)
{
	object link_ob;
	string old_pass;

	link_ob = me->query_temp("link_ob");
	old_pass = link_ob->query("ad_password");
	if (! stringp(old_pass) || crypt(passwd, old_pass) != old_pass)
	{
		write(HIR "���������ע�⣬��ɱ��������������롣\n");
		return;
	}

	if (forever)
        {
		tell_object(me, HIR "\n�����Ҫ��ɱ�ˣ������ʮ��"
                            "���ڲ���ڣ�����������ˡ�\n\n" NOR);
		me->set_temp("suicide/time", time());
		me->set_temp("suicide/last", 0);
		me->set_temp("suicide/from", query_ip_number(me));
		me->start_busy((: slow_suicide, me :),
			       (: halt_suicide, me :));
	}
}

private int slow_suicide(object me)
{
	object link_ob;
	int t;

        if (! objectp(me))
                return 0;

        t = time() - me->query_temp("suicide/time");
        if (t < me->query_temp("suicide/last"))
        {
                me->delete_temp("suicide/");
                return 0;
        }

        if (t < 30)
	{
                if (t - me->query_temp("suicide/last") < 5)
                        return 1;

                tell_object(me, HIR "\n�㻹��" + chinese_number(30 - t) +
                            "������ϸ����(" HIC "haltֹͣ" HIR ")��\n" NOR);
                me->set_temp("suicide/last", t / 5 * 5);
		return 1;
	}

	link_ob = me->query_temp("link_ob");
	if (! link_ob || ! interactive(me)) return 0;

	log_file("static/suicide",
		 sprintf("%s %s commits a suicide from %s\n",
			log_time(), log_id(me),
			me->query_temp("suicide/from")));

	seteuid(getuid());
	write("\n�ðɣ�������:)��\n\n");

        CHANNEL_D->do_channel(this_object(), "rumor",
                sprintf("%s��ɱ�ˣ��Ժ�����Ҳ������������ˡ�",
                me->name()));

	tell_room(environment(me), me->name() +
		"�������ǰ�������̣�������ʧ��...\n", ({me}));

        UPDATE_D->remove_user(me->query("id"));
	return 0;
}

private int halt_suicide(object me)
{
	tell_object(me, HIG "�������Ѱ������ͷ��\n" NOR);
	me->delete_temp("suicide");
	return 1;
}

int help (object me)
{
        write(@HELP
ָ���ʽ: suicide [-f]
 
�����Ϊĳ��ԭ���㲻�����, �����ѡ����ɱ.
��ɱ������:
 
suicide    : ����Ͷ̥
suicide -f : ��Զ�ĳ�ȥ�������, ϵͳ��Ҫ����
             ����������ȷ�����.
 
������ѡ�� :)
 
HELP );
        return 1;
}
