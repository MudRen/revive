// story:dabei

#include <ansi.h>

inherit F_DBASE;

int     give_gift();
mixed   continue_story(int n);

// �ⲿ���Ե��õĺ���
void    start_fight(string result, object who);
void    stop_story(string result);

static mixed *story = ({
        "���ʼ��±����ཻ֮�����˹�����",
        "л�̿�����һ�ݣ�����ʯ���죬��������֮���Ѿ�����һ�ô���֮��",
        "������������ȥ��ֻ�������������භ���������˼й�һ�ˡ�",
        "л�̿�����һ����ԭ����Χ����ȴ�ǰ׾����������ˣ���������ȴ���ϵã�ֻ���书��ͬ������",
        "ֻ����������Ȼ���У����ϸ���������������Ѫ�ɽ�������",
        (: give_gift :),
});

void create()
{
        seteuid(getuid());
}

string prompt() { return HIR "�����ִ��š�" NOR; }

mixed query_story_message(int step)
{
        return step < sizeof(story) ? story[step] :
                                      continue_story(step - sizeof(story));
}

mixed continue_story(int n)
{
        object *obs;

        if (! arrayp(obs = query_temp("actor")) ||
            ! objectp(obs[0]) || ! objectp(obs[1]))
        {
                // story can not continue
                stop_story(0);
                return 0;
        }

        return 1;
}

void start_fight(string result, object who)
{
        string msg;

        if (query_temp("fighter"))
                return;

        switch (result)
        {
        case "dabei":
                msg = "��˵$N���ֺͳ��ְ���һ��Χ�������ˡ�";
                break;

        case "mi":
                msg = "��˵$Nͦ��������ʹ�����һͬ�������ְ��ڡ�";
                break;

        default:
                return;
        }

        msg = replace_string(msg, "$N", who->name(1) + HIM);
        set_temp("fighter", who);
        set_temp("start_fight", result);
        CHANNEL_D->do_channel(this_object(), "rumor", msg);
}

void stop_story(string result)
{
        object *obs;
        object aob;

        switch (result)
        {
        case "dabei die":
                // �����˱�����
                break;

        case "mi die":
                // ������������
                break;
        default:
                CHANNEL_D->do_channel(this_object(), "rumor",
                        "��˵���ְ��ڻ����˰׾����������ˣ�������һ������Ѫ����");
                break;
        }

        obs = query_temp("actor");
        if (arrayp(obs))
        {
                obs -= ({ 0 });
                foreach (aob in obs)
                {
                        if (! living(aob)) aob->revive();
                        message_vision("$N��״���һ�����Ͻ�ת�������ˡ�\n", aob);
                        destruct(aob);
                }
        }
}

int give_gift()
{
        object dabei, mi, dizi1, dizi2;

        dabei  = new("/d/city/npc/dabei");
        mi     = new("/d/city/npc/mi");
        dizi1  = new("/d/city/npc/cldizi");
        dizi2  = new("/d/city/npc/cidizi");

        mi->set_temp("helper", ({ dizi1, dizi2 }));
        mi->set_temp("story", this_object());
        dabei->set_temp("story", this_object());

        set_temp("actor", ({ dabei, mi, dizi1, dizi2 }));

        return 1;
}
