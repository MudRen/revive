// shuisheng ˮ��

inherit NPC;

void greeting(object me);
int do_register(string arg);
int do_decide(string arg);

void create()
{
        set_name("ˮ��", ({ "shui sheng","shuisheng"}));
        set("long", "����ױ��Ĩ��üĿ֮�������͸¶��˼��\n");
        set("gender", "Ů��");
        set("age", 22);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("per", 25);

        setup();
        carry_object("/clone/cloth/cloth.c")->wear();
}

void init()
{
        object me;

        ::init();
        me = this_player();
        if (! objectp(me) || ! userp(me))
                return;

        add_action("do_register", "register");
        add_action("do_decide", "decide");

        remove_call_out("greeting");
        call_out("greeting", 0, me);
}

void greeting(object me)
{
        if (! objectp(me) || environment(me) != environment(this_object()))
                return;

        if (! me->query("registered"))
        {
                command("tell " + me->query("id") + " �㻹û��ע�ᣬ��ע��(register)�ɡ�");
                command("tell " + me->query("id") + " �����ע��������ܹ���ȡ�ż��ĵ�ַ"
                        "��\n�Ա����ʧ��ʱ���ܹ���ȡ���µĿ��");
                return;
        }

        if (! stringp(me->query("character")))
        {
                command("tell " + me->query("id") + " �㻹û��ѡ��Ʒ�ʣ���ȥ����ѡѡ�ɡ�");
                return;
        }

        if (! wizardp(me))
        {
                command("tell " + me->query("id") + " �ף�����ô�ܵ��������ˣ�");
                if (! stringp(me->query("born")))
                {
                        message_vision("$N�������������˳�ȥ��\n", me);
                        me->delete("born");
                        me->move("/d/register/yanluodian");
                        message_vision("ž��һ����$N���ӵ��˵��ϡ�\n", me);
                        return;
                }

                message_vision("$N�������������˳�ȥ��\b", me);
                me->move(VOID_OB);
                message_vision("ž��һ����$N���ӵ��˵��ϡ�\n", me);
                return;
        }

        command("look " + me->query("id"));
}

int do_register(string arg)
{
        object me;
        string id, address;

        if (! objectp(me = this_player()))
                return 0;

        if (me->query("registered"))
        {
                command("say �㲻���Ѿ�ע������𣿲�����ע���ˡ�");
                return 1;
        }

        if (! arg || ! stringp(arg))
        {
		command("shake " + me->query("id"));
                command("say ע���email��ַ��ø��Ұ���������register ���email��ַ");
                return 1;
        }

        if (strlen(arg) > 64 || sscanf(arg, "%s@%s", id, address) != 2)
        {
                command("say ����ôû�м�����ô�ֵ�email��ַ���㿴���������");
                return 1;
        }

        me->set_temp("email", arg);
        command("nod " + me->query("id"));
        command("tell " + me->query("id") + " �ã����email��ַ�ǣ�" + arg +
                "�����û��\n������;���(decide)�ɡ�");
        command("tell " + me->query("id") + " ��ע�⣬���ڱ�վ������mailȷ�ϣ�����
�㼴ʹע��һ�����޷����ŵĵ�ַ��ϵͳҲ����ʶ�𡣵����������
��������ַ�Ժ�������Ϊȷ������ݵ�Ψһ;�������ע�����
���ַ����Զ���ܸı�ġ����㶪ʧ����������Ժ�ϵͳ�Ĺ�����Ա
���Խ��޸ĺ�Ŀ���͵���ע��������У���������ĳ��Ŀ�Ĳ�
Ը��ע��������䣬��ô������Ա����Ϊ������븺�κ����Σ�����
ζ��������Լ����ܺ�������롣");
        return 1;
}

int do_decide(string arg)
{
        object me;
        object link_ob;

        if (! objectp(me = this_player()))
                return 0;

        if (me->query("registered"))
        {
                command("say �������ˣ����Ѿ�֪����ĵ�ַ�ˣ�������˵����\n");
                return 1;
        }

        if (! stringp(me->query_temp("email")))
        {
                command("say ��Ҫ����ʲô���Ǿ���ע����Ҫ����"
                        "��������ע�����email��ַ��");
                return 1;
        }

        command("say ���ˣ����email��ַ�Ѿ�ע���ˣ����ڿ�ȥ����ѡ���Ʒ�ʰɡ�");
        me->set("email", me->query_temp("email"));
        me->set("registered", 1);
        me->save();
        return 1;
}
