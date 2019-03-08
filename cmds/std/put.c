// put.c

#include <config.h>

inherit F_CLEAN_UP;

int do_put(object me, object obj, object dest);

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
        string target, item;
        object obj, dest, *inv, obj2;
        int i, amount;

        if (! arg) return notify_fail("��Ҫ��ʲô�����Ž����\n");

        if (sscanf(arg, "%s in %s", item, target) != 2)
                return notify_fail("��Ҫ��ʲô������\n");

        dest = present(target, me);
        if (! dest || living(dest))
                dest = present(target, environment(me));

        if (! dest || living(dest))
                return notify_fail("����û������������\n");

        if (dest->query("no_get_from"))
                return notify_fail("���ǲ�Ҫ�����˼��ˡ�\n");

        if (sscanf(item, "%d %s", amount, item) == 2)
        {
                if (! objectp(obj = present(item, me)))
                        return notify_fail("������û������������\n");

                if (! obj->query_amount())
                        return notify_fail( obj->name() + "���ܱ��ֿ���\n");

                if (amount < 1)
                        return notify_fail("����������������һ����\n");

                if (amount > obj->query_amount())
                        return notify_fail("��û����ô���" + obj->name() + "��\n");
                else
                if (amount == (int) obj->query_amount())
                        return do_put(me, obj, dest);
                else
                {
                        obj->set_amount((int) obj->query_amount() - amount);
                        obj2 = new(base_name(obj));
                        obj2->set_amount(amount);
                        return do_put(me, obj2, dest);
                }
        }

        if (item == "all")
        {
                inv = all_inventory(me);
                for(i=0; i<sizeof(inv); i++)
                        if (inv[i] != dest)
                                do_put(me, inv[i], dest);
                write("Ok.\n");
                return 1;
        }

        if (! objectp(obj = present(item, me)))
                return notify_fail("������û������������\n");
        return do_put(me, obj, dest);
}

int do_put(object me, object obj, object dest)
{
        mixed msg;

        if (! dest->is_container() && ! dest->is_character())
        {
                tell_object(me, dest->name() + "�����������㲻�ܰѶ����Ž�ȥ��\n");
                return 1;
        }

        if (dest->is_character() &&
            sizeof(filter_array(all_inventory(dest), (: ! $1->query("equipped") :))) >= MAX_ITEM_CARRIED)
        {
                tell_object(me, dest->name() + "����Ķ���ʵ��"
                            "��̫���ˣ���û���ٷŶ����ˡ�\n");
                return 1;
        } else
        if (dest->is_container() && sizeof(all_inventory(dest)) >= MAX_ITEM_CARRIED)
        {
                tell_object(me, dest->name() + "����Ķ���ʵ��"
                            "��̫���ˣ����Ⱥú����������ɡ�\n");
                return 1;
        }

        if (! undefinedp(msg = obj->query("no_put")))
        {
                if (stringp(msg))
                        tell_object(me, msg);
                else
                        tell_object(me, "���������Ҫ�ҷš�\n");
                return 1;
        }

        if (obj->is_corpse())
        {
                tell_object(me, "���޷���" + obj->name() + "����ȥ��\n");
                return 1;
        }

        if (playerp(obj))
        {
                tell_object(me, "���޷���" + obj->name() + "����ȥ��\n");
                return 1;
        }

        if (obj == dest)
        {
                tell_object(me, "��... �Լ����Լ�������뷨�Ƚ���Ȥ��\n");
                return 1;
        }

        if (obj->move(dest))
        {
                message_vision(sprintf("$N��һ%s%s�Ž�%s��\n",
                               obj->query("unit"), obj->name(),
                               dest->name()), me);
                return 1;
        }

        // �Żص��ҵ�������
        if (! environment(obj))
                // ���Ƿ������Ʒ��û�з���ɹ�
                obj->move(me, 1);

        return 0;
}

int help(object me)
{
        write(@HELP
ָ���ʽ : put <��Ʒ����> in <ĳ����>
 
���ָ��������㽫ĳ����Ʒ�Ž�һ����������Ȼ��������Ҫӵ��������Ʒ��
 
HELP );
        return 1;
}