// gargoyle.c

#include <ansi.h>
#include <command.h>
#include <login.h>

inherit NPC;

string *death_msg = ({
	HIW "���޳�˵����ι�������ģ����ʲô���֣�\n\n" NOR,
	HIW "���޳���������۹ⶢ���㣬����Ҫ�������һ���Ƶġ�\n\n" NOR,
	HIW "���޳����ߡ���һ�����������ͳ�һ�����ʲ�Ķ�����������\n\n" NOR,
	HIW "���޳����˰��죬��Щ����\n\n" NOR,
	HIW "���޳���ϸ���˿��㣬û��˵ʲô��\n\n" NOR,
	HIW "���޳��ַ���һ����ʲᣬ�����˰��졣\n\n" NOR,
	HIW "���޳�������һ����㣬������üͷ��\n\n" NOR,
	HIW "���޳�̾��һ������\n\n" NOR,
	HIW "���޳����ϲ��ӣ�����һ�����\n\n" NOR,
        HIW "���޳�˵����������δ������Щ��֡�\n\n" NOR,
        HIW "���޳�����˵���������������䲻��ʱ�ˣ��������롣\n\n" NOR,
	HIW "���޳�ɦ��ɦͷ��̾�������˰��ˣ����߰ɡ�\n\n"
            "һ�������Ũ��ͻȻ���֣��ܿ�ذ�Χ���㡣\n\n" NOR,
});

void create()
{
	set_name("���޳�", ({ "white gargoyle", "gargoyle" }));
	set("title", "ڤ���ز�����ǰ");
	set("long",
		"���޳������㣬���׵����Ͽ������κ�ϲŭ���֡�\n");
	set("attitude", "peaceful");
	set("chat_chance", 1);
	set("chat_msg", ({
		"���޳����ĵĴ��˸���Ƿ��\n",
		"���޳��ٺټ�Ц������\n",
	}));
	set("age", 217);
	set("combat_exp", 20000);
	set("max_jing", 900);
	set("max_qi", 900);
	set_skill("dodge", 40);
	set_skill("unarmed", 40);
	setup();
}

void init()
{
	::init();
	if (! previous_object() ||
	    ! userp(previous_object()) ||
	    ! previous_object()->is_ghost() ||
	    wizardp(previous_object())) return;
	call_out("death_stage", 30, previous_object(), 0);
}

void death_stage(object ob, int stage)
{
	int i;
	object *inv, mailbox;
	if (! ob || ! present(ob)) return;

	tell_object(ob, death_msg[stage]);
	if (++stage < sizeof(death_msg))
	{
		call_out("death_stage", 10, ob, stage);
		return;
	} else
		ob->reincarnate();

        if (! wizardp(ob))
        {
    	        inv = all_inventory(ob);
    	        for (i = 0; i < sizeof(inv); i++)
    		        DROP_CMD->do_drop(ob, inv[i]);
        }
	
	ob->move(REVIVE_ROOM);
        ob->set("startroom", REVIVE_ROOM);
	message("vision",
		"���Ȼ����ǰ�����һ����Ӱ����������Ӱ�ֺ����Ѿ�������\n"
		"�ܾ��ˣ�ֻ����һֱû������\n", environment(ob), ob);
}
