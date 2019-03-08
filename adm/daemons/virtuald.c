// virtuald.c
// Modified by Find.
// Updated by Doing Lu

void create()
{
	seteuid(getuid());
}

// This function is called by master object to return the "virtual" object
// of <file> when dirver failed to find such a file.

object compile_object(string file)
{
        string *path;
        string name;
        int i;
        object ob;

        path = explode(file, "/");
        name = "";
        for (i = 0; i < sizeof(path); i++)
        {
                name += "/" + path[i];
                if (file_size(name) == -2)
                {
                        // ��·����������
                        continue;
                }

                // �鿴�Ƿ����� .c ��β���ļ���
                if (file_size(name + ".c"))
                {
                        // ��������ļ�������Ϣ���ݸ���Ӧ�����
                        ob = name->query_virtual_room(implode(path[i + 1..<1], "/"));
                        if (objectp(ob))
                                return ob;
                }

                // �Ҳ���ָ��·�����ļ������ļ���֧�����ָ��
                // ���������
                break;
        }

        // �޷������������
        return 0;
}
