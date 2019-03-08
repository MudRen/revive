// clone.c

inherit F_CLEAN_UP;

int main(object me, string file)
{
	object obj;
	string err, msg;

        if (! SECURITY_D->valid_grant(me, "(wizard)"))
                return 0;

	seteuid(getuid());

	if (! file) file = me->query("cwf");
	if (! file)
		return notify_fail("��Ҫ����ʲ�������\n");

	file = resolve_path(me->query("cwd"), file);
	if (sscanf(file, "%*s.c") != 1) file += ".c";
	me->set("cwf", file);

	if (file_size(file) < 0)
		return notify_fail("û���������(" + file + ")��\n");

        if (! SECURITY_D->valid_read(file, me, "clone"))
        {
                write("��û��Ȩ�޲����������\n");
                return 1;
        }

	if (! find_object(file))
        {
		err = catch(call_other(file, "???"));
		if (err)
		{
			write("����ʧ�ܣ�" + err + "\n");
			return 1;
		}
	}

        if (! me->is_admin())
        {
                switch (SECURITY_D->query_site_privilege("clone"))
                {
                case "gift":
                        if (! sscanf(file, "/clone/special/%*s") &&
                            ! sscanf(file, "/clone/gift/%*s"))
                                return notify_fail("�㲻�ܸ��������Ʒ��\n");
                        break;

                case "all":
                        break;

                default:
                        return notify_fail("�㲻�ܸ�����Ʒ��\n");
                }

                if (! me->is_admin())
                        message_system(sprintf("%s(%s)��������Ʒ��%s(%s)��\n",
                                               me->name(1), me->query("id"),
                                               filter_color(file->name(1)), file->query("id")));
        }

	seteuid(geteuid(me));

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

        msg = "ֻ��$N�������һָ�������$n��\n";

	log_file("static/clone", sprintf("%s %-9s clone %s\n",
					 log_time(), geteuid(me),
			                 base_name(obj)));
	if (! obj->is_character() && ! obj->query("no_get") && obj->move(me))
        {
		write(obj->query("name") + "���Ƴɹ������������Ʒ����\n");
                message_vision(msg + "\n", me, obj);
		return 1;
	}
	if (obj->move(environment(me)))
        {
		write(obj->query("name") + "���Ƴɹ�������������䡣\n");
                message_vision(msg + "\n", me, obj);
		return 1;
	}

	destruct(obj);
	return notify_fail("�޷����Ʋ����ƶ������(" + file + ")��\n");
}

int help(object me)
{
        write(@HELP
ָ���ʽ : clone <����>

���ô�ָ��ɸ����κ����ƶ�֮���(������)��

�������ڿ��Ա���Ȩʹ�õ���Ϣ������gift��all��
HELP );
        return 1;
}
