// enchase.c

#include <ansi.h>

inherit F_CLEAN_UP;

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
	string item, tessera;
	object obj, dest;

	if (! arg)
                return notify_fail("��Ҫ��ʲô��������Ƕ��Ʒ��\n");

        if (me->is_busy())
                return notify_fail("��æ����������������������ɣ�\n");

        if (me->is_fighting())
                return notify_fail("���������ڴ�ܣ�ûʱ������Щ���顣\n");

        if (sscanf(arg, "%s with %s", item, tessera) != 2 &&
            sscanf(arg, "%s in %s", tessera, item) != 2)
                return notify_fail("��Ҫ����������Ƕʲô��Ʒ��\n");

	if (! objectp(obj = present(tessera, me)))
		return notify_fail("������û��������������������Ƕ��\n");

	if (! objectp(dest = present(item, me)))
		return notify_fail("������û���������ߡ�\n");

        notify_fail("���޷���" + obj->name() + "��Ƕ��" +
                    dest->name() + "�ϡ�\n");
	return dest->do_enchase(me, obj);
}

int help(object me)
{
write(@HELP
ָ���ʽ : enchase <������Ʒ> in <����>
           enchase <����> with <������Ʒ>

���ָ��������㽫ĳ��������Ʒ��Ƕ������һ�ֵ����ϣ�ʹ�õ���
���������������
HELP
    );
    return 1;
}
