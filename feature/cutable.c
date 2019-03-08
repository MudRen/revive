// cutable.c

#include <dbase.h>

// what I need ?

// mapping <parts> such as:
// ([ "head" : ({ 0, "ͷ", "ͷ­", 0, ([ "eye" : "eye", "nose" : "nose" ...]),
//                "����", "/clone/misc/head", }),
//    "left middle finger" : ({ 0, "������ָ", "��ָ", "finger", 0, 0, 0 }), ])
// the mixed array of part item is:
// 0. level of the body
// 1. unit of the part
// 2. the part name on owner,
// 3. the part name left from owner,
// 4. the part id left from owner
// 5. the association part & new id left with this part
// 6. the verb of cut
// 7. clone object of part cut
// if not clone object defined, I will clone "/clone/misc/part"
//
// <main_part_level> to show
//
// string array <been_cut> such as:
// ({ "left_hand" })
//
// mapping <no_cut> that denied to cut

#define LEVEL           0
#define UNIT            1
#define NAME            2
#define NAME_LEFT       3
#define ID_LEFT         4
#define ASS_PART        5
#define VERB            6
#define CLONE           7

#define NOT_INCLUDE_THIS_PART   0
#define INCLUDE_THIS_PART       1

int is_cutable() { return 1; }

void include_part(object ob, string id, mixed *in_part, int include_this_part);

string *query_exclude_part() { return ({ }); }

int do_cut(object me, string arg)
{
        string *exist;
        string *cut;
        mapping parts;
        mixed *part;
        string default_clone;
        string msg;
        object weapon;
        object ob;

        if (! arg)
                return notify_fail("��Ҫ����ʲô��λ��\n");

        if (! mapp(parts = query("parts")))
                return notify_fail("�������Ǹ����ʲô�����ˡ�\n");

        exist = keys(parts);
        exist -= query_exclude_part();
        cut = query("been_cut");
        if (! cut) cut = ({ });

        if (arg == "?")
        {
                int i;
                int count;
                count = 0;
                msg = this_object()->name() + "�����²�λ���Ը�������\n";
                for (i = 0; i < sizeof(exist); i++)
                {
                        if (member_array(exist[i], cut) != -1 ||
                            query("no_cut/" + exist[i]))
                                continue;
                        count++;
                        msg += sprintf("%-20s(%s)\n",
                                       parts[exist[i]][NAME], exist[i]);
                }
                if (! count)
                        msg = this_object()->name() + "�Ѿ�ûʲô�����µ��ĵط��ˡ�\n";
                write(msg);
                return 1;
        }

        part = parts[arg];
        if (! arrayp(part))
                return notify_fail("����ôҲ�Ҳ��������Ĳ�λ��\n");

        if (member_array(arg, cut) != -1)
                return notify_fail(part[NAME] + "�Ѿ��������ˡ�\n");

        if (msg = query("no_cut/" + arg))
                return notify_fail(msg ? msg : "����������������\n");

        default_clone = query("default_clone");
        if (weapon = me->query_temp("weapon"))
        {
                switch (weapon->query("skill_type"))
                {
                case "pin" :
                        return notify_fail(weapon->name() + "����ֻ����������С�ۡ�\n");
                case "hammer" :
                        return notify_fail(weapon->name() + "����ֻ���������ö�����\n");
                case "staff" :
                        return notify_fail(weapon->name() + "����ֻ���������ƨ�ɡ�\n");
                case "club" :
                        return notify_fail(weapon->name() + "����ֻ�����������Դ���\n");
                case "throwing" :
                        return notify_fail("��" + weapon->name() + "�������̫�ðɡ�\n");
                case "whip":
                        return notify_fail(weapon->name() + "�ⶫ�������ϵ���Ҳ������������㡣\n");
                }
                msg = "$N�������е�" + weapon->name() + "�������ꡱһ���Ӱ�$n��" +
                      part[NAME] + "��" + (stringp(part[VERB]) ? part[VERB] : "������") +
                      "����\n";
        } else
        if (me->query_skill("force") < 90)
        {
                message_vision("$N��������������$n��" + part[NAME] + "һ��"
                               "������ȥ���������ġ����ۡ��ֽ���������\n",
                               me, this_object());
                write("�ú������ڹ������ɣ�\n");
                return 1;
        } else
                msg = "$N����������һ���ӾͰ�$n��" + part[NAME] + "��" +
                      (stringp(part[VERB]) ? part[VERB] : "������") + "����\n";

        message_vision(msg, me, this_object());
        ob = new(stringp(part[CLONE]) ? part[CLONE] : default_clone);
        ob->set_name(stringp(part[NAME_LEFT]) ? part[NAME_LEFT] : part[NAME],
                     ({ stringp(part[ID_LEFT]) ? part[ID_LEFT] : arg }));
        ob->set("unit", part[UNIT]);
        ob->set("long", "һ" + part[UNIT] + "���˸�������" + ob->name() + "��\n");
        ob->set("default_clone", default_clone);
        ob->set("main_part_level", part[LEVEL] + 1);
        if (ob->is_cutable())
                ob->set("been_cut", ({ }));
        ob->set_from(this_object());
        ob->move(environment());

        // seperate the part cut
        cut += ({ arg });
        set("been_cut", cut);

        // seperate the association part
        include_part(ob, arg, 0, NOT_INCLUDE_THIS_PART);
        return 1;
}

string extra_desc()
{
        string msg;
        string *cut;
        mixed *part;
        int flag;
        int i;

        msg = "";
        if (! arrayp(cut = query("been_cut")))
                return msg;
        flag = 0;
        for (i = 0; i < sizeof(cut); i++)
        {
                part = query("parts/" + cut[i]);
                if (part[LEVEL] > query("main_part_level"))
                        continue;
                if (! flag)
                {
                        msg += "��������" + part[NAME];
                        flag++;
                } else
                        msg += "��" + part[NAME];
        }
        if (flag) msg += "�Ѿ������ˡ�\n";
        return msg;
}

void include_part(object ob, string id, mixed *in_part, int include_this_part)
{
        string *cut;
        string *ass;
        mixed  *srcpart;
        mixed  *part;
        string new_id;
        mapping assmap;
        int i;

        srcpart = query("parts/" + id);
        if (! arrayp(srcpart))
                return;
        part = allocate(sizeof(srcpart));
        for (i = 0; i < sizeof(srcpart); i++)
                part[i] = srcpart[i];
        part[ASS_PART] = allocate_mapping(sizeof(srcpart[ASS_PART]));
        if (include_this_part)
        {
                part[NAME] = part[NAME_LEFT];
                new_id = in_part[ASS_PART][id];
                ob->set("parts/" + new_id, part);
                if (member_array(id, cut = query("been_cut")) != -1)
                        ob->set("been_cut", ob->query("been_cut") + ({ new_id }));
                set("been_cut", cut + ({ id }));
        }

        if (mapp(assmap = srcpart[ASS_PART]))
        {
                // set the association part
                ass = keys(assmap);
                for (i = 0; i < sizeof(ass); i++)
                {
                        include_part(ob, ass[i], srcpart, INCLUDE_THIS_PART);
                        new_id = assmap[ass[i]];
                        part[ASS_PART][new_id] = new_id;
                        if (query("no_cut/" + ass[i]))
                                ob->set("no_cut/" + new_id, query("no_cut/" + ass[i]));
                }
        }
}
