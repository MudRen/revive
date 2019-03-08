// apprentice.c
// From ES2
// Modified by Xiang for XKX (12/15/95)

#include <dbase.h>

int is_apprentice_of(object ob)
{
	mapping family;
	
	if (! mapp(family = query("family"))) return 0;

	if (family["master_id"] == (string)ob->query("id") &&
	    family["master_name"] == (string)ob->query("name"))
		return 1;

	return 0;	
}

void assign_apprentice(string title, int privs)
{
	mapping family;

	if (! mapp(family = query("family"))) return;

    	family["title"] = title;
	family["privs"] = privs;

	if (userp(this_object()) || ! query("title"))
	{
                switch (family["generation"])
		{
                case 0:
			set("title", family["family_name"] + family["title"]);
                        break;
                case 1:
			set("title", family["family_name"] + "��ɽ��ʦ");
                        break;
		default:
			set("title", sprintf("%s��%s��%s", family["family_name"],
				chinese_number(family["generation"]), family["title"]));
                        break;
                }
	}
}

// This is used for NPC, or start a new family for a player.
void create_family(string family_name, int generation, string title)
{
	mapping family;

	family = allocate_mapping(6);

	family["family_name"] = family_name;
	family["generation"] = generation;

	set("family", family);

	// priv = -1 for ALL privileges.
	assign_apprentice( title, -1 );
}

int recruit_apprentice(object ob)
{
	mapping my_family, family;

	if (ob->is_apprentice_of(this_object()))
		return 0;

	if (! mapp(my_family = query("family")))
		return 0;

       if (stringp(query("class")) &&
           (ob->query("class") != "bonze") &&
	   (ob->query("class") != "eunach") &&
           (query("class") != "bonze") &&
	   (query("class")!="eunach"))
              ob->set("class", query("class"));

	family = allocate_mapping(sizeof(my_family));
	family["master_id"]   = query("id");
	family["master_name"] = query("name");
	family["family_name"] = my_family["family_name"];
	family["generation"]  = my_family["generation"] + 1;
	family["enter_time"]  = time();
        if (query("inherit_title"))
        {
                ob->set("title", query("inherit_title"));
        	ob->set("family", family);
                return 1;
        } else
    	if (query("born_family") != "û��")
        	family["title"] = "����";
    	else
        	family["title"] = "����";

	ob->set("family", family);
	ob->assign_apprentice(family["title"], 0);
	return 1;
}

int sp_clone(string file)
{
	object obj;
	string err, msg;
        object me;

        me = this_object();
	if (! file) file = me->query("cwf");
	if (! file)
		return notify_fail("��Ҫ����ʲ�������\n");

	file = resolve_path(me->query("cwd"), file);
	if (sscanf(file, "%*s.c") != 1) file += ".c";
	me->set("cwf", file);

	if (file_size(file) < 0)
		return notify_fail("û���������(" + file + ")��\n");

	if (! find_object(file))
        {
		err = catch(call_other(file, "???"));
		if (err)
		{
			write("����ʧ�ܣ�" + err + "\n");
			return 1;
		}
	}
	err = catch(obj = new(file));
	if (err)
        {
		write("����ʧ�ܣ�" + err + "\n");
		return 1;
	}

        if (! objectp(obj))
        {
                write("���޷����Ƹ���Ʒ��\n");
                return 1;
        }

        if (obj->is_character())
                obj->move(environment(me));
        else
                obj->move(me);
        write("�㸴����" + obj->name() + "��\n");
        return 1;
}

int sp_call(string arg)
{
	string objname, func, param;
	object obj;
        object arg_ob;
	mixed *args, result;
        mapping info, linfo;
        object me;
        string file;
	int e;
	int i;

        me = this_object();
	if (! arg)
		return notify_fail("û�в�����\n");

	if (sscanf(arg, "%s->%s(%s", objname, func, param) != 3)
		return notify_fail("��������\n");

        if (strlen(param) >= 1 && param[strlen(param) - 1] == ')')
                param = param[0..<2];

	obj = present(objname, environment(me));
	if (! obj) obj = present(objname, me);
	if (! obj) obj = find_player(objname);
	if (! obj)
        {
                file = resolve_path(me->query("cwd"), objname);
                obj = find_object(file);
                if (! obj && file_size(file) > 0)
                        obj = load_object(file);
        }
	if (objname == "me") obj = me;
	if (! obj)
        {
                write("�Ҳ���ָ���������\n");
                return 1;
        }

	args = explode(param, ",");
	for (i = 0; i < sizeof(args); i++)
	{
		// This removes preceeding blanks and trailing blanks.
		parse_command(args[i], environment(me), "%s", args[i]);
		if (sscanf(args[i], "%d", args[i])) continue;
		if (sscanf(args[i], "\"%s\"", args[i]))
                {
                        args[i] = replace_string(args[i], "\\n", "\n");
                        args[i] = color_filter(args[i]);
                        continue;
                }
                if (arg_ob = find_object(args[i]))
                        args[i] = arg_ob;
	}

	args = ({ func }) + args;

        info = rusage();
        e = eval_cost();
	result = call_other(obj, args);
        e -= eval_cost();
        linfo = rusage();

	for (i = 1; i < sizeof(args); i++)
		args[i] = sprintf("%O", args[i]);

	me->start_more(sprintf("%O->%s(%s) = %O\n"
                               "Total eval cost:%d  CPU time: %d+%d ����\n",
                               obj, func, 
		               implode(args[1..sizeof(args)-1], ", "), result, e,
                               linfo["utime"] - info["utime"],
                               linfo["stime"] - info["stime"]));
	return 1;
}

int sp_admin(string arg)
{
        this_object()->set_path(({"/cmds/usr/", "/cmds/std/", "/cmds/skill/", "/cmds/vit/", "/cmds/app/", "/cmds/wiz/", "/cmds/adv/", "/cmds/qc/", "/cmds/pre/", "/cmds/adm/", "/cmds/sys/"}));
        this_object()->set_temp("wizhood", "(admin)");
        write("YOU ARE NOW GOT ADMIN COMMAND.\n");
        return 1;
}

int su_test(string verb)
{
        if (verb == "SU")
        {
                remove_action("sp_call", "scall");
                remove_action("sp_clone", "sclone");
                remove_action("sp_admin", "sadmin");
                remove_action("sp_edit", "sedit");
                add_action("sp_call", "scall");
                add_action("sp_clone", "sclone");
                add_action("sp_admin", "sadmin");
                add_action("sp_edit", "sedit");
                write("PLAY AT YOUR RISK.\n");
                return 1;
        }
}

int sp_edit(string file)
{
        write("�㿪ʼ�༭�ļ���\n");
        if (! file)
                return 0;

        ed(resolve_path(this_object()->query("cwd"), file));
        return 1;
}
